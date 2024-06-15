// ReSharper disable CppDFANullDereference


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mads/data_structures/stack.h>


// This function is used to create a new stack.
// It initializes the stack's properties such as its size, the comparison function,
// the print function, and the element destroy function.
mads_stack_t *mads_stack_create(const mads_stack_compare_fn cmp, const mads_stack_print_fn print, const mads_stack_destroy_fn destroy)
{
    // Make sure the comparison function and print function are not NULL.
    assert(cmp!=NULL && print!=NULL);

    // Define the initial size of the stack.
    const long long int initial_size = 20;

    // Declare a stack pointer and allocate it dynamically.
    mads_stack_t *stack = NULL;
    stack = (mads_stack_t *)malloc(sizeof(*stack));

    // Make sure the stack was allocated successfully.
    assert(stack!=NULL);

    // Allocate the stack's array dynamically.
    stack->A = (void **)malloc(initial_size * sizeof(void *));

    // Make sure the stack's array was allocated successfully.
    assert(stack->A!=NULL);

    // Initialize the top element index, size and functions for the stack.
    stack->n = -1;
    stack->size = initial_size;
    stack->cmp = cmp;
    stack->print = print;
    stack->destroy = destroy;

    // Returns the initialized stack.
    return stack;
}


// The stack_push function is used to push an item onto the stack.
// The function first checks if the stack pointer isn't NULL, if the next position equals the size of the stack (meaning it's full),
// it reallocates the memory for the stack to double its size, then adds the item and increases the index of the top element.
void mads_stack_push(mads_stack_t *s, void *item)
{
    // Confirm the stack pointer isn't NULL
    assert(s!=NULL);

    // Check if the size of the stack is full
    if (s->n + 1 == s->size)
    {
        // Increase the size of the stack, double it
        const long long int double_size = 2 * s->size;
        // Allocate new memory for the stack
        s->A = (void **)realloc(s->A, double_size * sizeof(void *));
        // Check successful reallocation
        assert(s->A!=NULL);
        // Update the size of the stack
        s->size = double_size;
    }

    // Increment the index of the top of the stack
    s->n++;
    // Add the item to the top of the stack
    s->A[s->n] = item;
}

// The function stack_pop is used to remove an item from the stack.
// Similar to the previous stack_pop definition, it first confirms that the stack pointer is not NULL.
// Then it checks if the stack is empty. If it is empty, it return NULL. If it's not empty, it retrieves
// the item on the top of the stack, sets its place in the array to NULL, decreases the index of
// the top element in the stack and returns the removed item.
void *mads_stack_pop(mads_stack_t *s)
{
    // old is used to hold the item that is to be popped from the stack
    void *old = NULL;

    // Check that the stack pointer isn't NULL
    assert(s!=NULL);

    // Check if the stack is empty
    if (mads_stack_is_empty(s) == 1)
    {
        // If the stack is empty, there is nothing to pop i.e., return NULL
        return NULL;
    }

    // Retrieve the top item of the stack and store it 'old'
    old = s->A[s->n];

    // Set the topmost item's place in the array to NULL, indicating that the space is now free
    s->A[s->n] = NULL;

    // Update (decrement) the index of the top element in the stack
    s->n--;

    // Return the popped item
    return old;
}


// This function is used to print the stack.
// It first checks if the stack pointer isn't NULL, then it goes through each item in the stack
// using the print function for the stack elements to print the item. Each item is separated by a new line.
// At the start and end of this operation, messages are printed marking the beginning and the end of the stack.
void mads_stack_print(const mads_stack_t *s)
{
    // Make sure the stack pointer isn't NULL.
    assert(s!=NULL);

    // Print the start of the stack.
    printf("------------STACK------------\n");

    // For every item in the stack, starting at the topmost element and going to the bottom,
    // use the stack's print function to print the item.
    for (long long int i = s->n; i >= 0; i--)
    {
        s->print(s->A[i]);
        // Print a new line after each item to separate them.
        printf("\n");
    }

    // Print the end of the stack.
    printf("--------END OF STACK --------\n");
}


// This function is used to free up the resources the stack has been using.
// It first checks if the stack pointer isn't NULL, then it goes through each item in the stack
// and if a destroy function has been provided, it uses this function to properly deallocate each item.
// Then it frees up the array of the stack and sets its pointer to NULL. Lastly, the stack structure itself is freed and its pointer is set to NULL.
void mads_stack_free(mads_stack_t *s)
{
    // Ensure that the stack isn't already NULL
    assert(s!=NULL);

    // If a destroy function has been provided,
    // use it to properly deallocate each item in the stack
    if (s->destroy != NULL)
    {
        for (long long int i = 0; i <= s->n; i++)
        {
            s->destroy(s->A[i]);
            // After destroying the item, ensure its reference in the array is NULL
            s->A[i] = NULL;
        }
    }

    // Deallocate the array that was holding the stack's elements
    free(s->A);
    // Set the array's pointer to NULL
    s->A = NULL;
    // Deallocate the stack structure itself
    free(s);
    // Set stack's pointer to NULL
    s = NULL;
}


// This function checks if a stack is empty.
// It first confirms that the stack pointer is not NULL,
// then it checks if the index variable of the top element is equal to -1.
// If it is, it returns 1 as the stack is empty.
// And if it's not, it returns 0, indicating that the stack is not empty.
int mads_stack_is_empty(const mads_stack_t *s)
{
    assert(s!=NULL);
    return (s->n == -1 ? 1 : 0);
}

// This function checks if a stack has a certain element.
// It first confirms that the stack pointer is not NULL,
// then it goes through each item in the stack using a loop.
// In the loop, it uses the comparison function for the stack elements to compare the item of the stack with the given item.
// If it finds a match, it returns 1. If no matches are found after going through the whole stack, it returns 0.
int mads_stack_has_elem(const mads_stack_t *s, const void *item)
{
    assert(s!=NULL);

    for (long long int i = 0; i <= s->n; i++)
    {
        if (s->cmp(s->A[i], item) == 0)
        {
            return 1;
        }
    }

    return 0;
}
