// ReSharper disable CppDFANullDereference
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mads/data_structures/list.h>


// This function, `mads_list_create`, creates a new list, setting all initial values and
// assigning the function pointers that are passed as parameters. It returns the created list struct.
mads_list_t *mads_list_create(const mads_list_compare_fn cmp, const mads_list_print_fn print, const mads_list_destroy_fn destroy)
{
    // Declare a pointer to a `mads_list_t` and initialize it to `NULL`.
    mads_list_t *list = NULL;

    // Assert that `cmp` and `print` function pointers are not `NULL`. This is necessary because
    // these functions are essential for the operations on the list.
    assert(cmp!=NULL && print!=NULL);

    // Allocate memory to hold the `mads_list_t` struct. The parameter of `sizeof` is a
    // dereferenced `list` to get the size of what `list` points to, i.e., a `mads_list_t`.
    list = (mads_list_t *)malloc(sizeof(*list));

    // Assert that the memory was successfully allocated
    assert(list!=NULL);

    // Initialize the fields of the list
    list->size = 0; // Give the initial size of the list as 0
    list->head = list->foot = NULL; // Set the head and foot of the list to NULL
    list->cmp = cmp; // Assign the `cmp` function pointer to the list's `cmp` member
    list->print = print; // Assign the `print` function pointer to the list's `print` member
    list->destroy = destroy; // Assign the passed in `destroy` function pointer to the list's `destroy` member

    // Return a pointer to the new list
    return list;
}


// Implementing the mads_list_push function
// This function pushes a new node onto the list.
void mads_list_push(mads_list_t *list, void *data)
{
    // Create a new node
    mads_llnode_t *new_node = NULL;

    // Make sure the list is not NULL
    assert(list!=NULL);

    // Allocate memory for the new node
    new_node = (mads_llnode_t *)malloc(sizeof(*new_node));

    // Make sure the memory was successfully allocated
    assert(new_node!=NULL);

    // Set the data of the new node to the passed data
    new_node->data = data;

    // As the node will be inserted at the beginning, there will be no previous node
    // and the next node will be the current head of the list
    new_node->previous = new_node->next = NULL;

    // Check if the list is empty
    if (list->head == NULL)
    {
        // In case of an empty list, the new node is both the head and the foot
        list->head = new_node;
        list->foot = new_node;
    }
    else
    {
        // If the list is not empty, the new node becomes the new head
        // and its next node will be the old head
        list->head->previous = new_node;
        new_node->next = list->head;
        list->head = new_node;
    }

    // Increment the size of the list because we've added a new node
    list->size++;
}


// This function appends a new element to the end of the given list.
void mads_list_append(mads_list_t *list, void *data)
{
    // Initialize a new node
    mads_llnode_t *new_node = NULL;

    // Assert that the provided list is not NULL
    assert(list!=NULL);

    // Allocate memory for the new node
    new_node = (mads_llnode_t *)malloc(sizeof(*new_node));

    // Assert that the memory allocation was successful
    assert(new_node!=NULL);

    // Set the data of the new node
    new_node->data = data;

    // Since this is the last node, there will not be a next node
    new_node->next = new_node->previous = NULL;

    // Check if the list is empty
    if (list->foot == NULL)
    {
        // In case of an empty list, the new node is both the head and the foot
        list->foot = new_node;
        list->head = new_node;
    }
    else
    {
        // If the list is not empty, the new node becomes the new foot
        // and its previous node will be the old foot
        list->foot->next = new_node;
        new_node->previous = list->foot;
        list->foot = new_node;
    }

    // Increment the size of the list as we've added a new node
    list->size++;
}


// This function inserts a new node at a specific position in the list.
void mads_list_insert_at(mads_list_t *list, void *data, const unsigned long long int position)
{
    // Declare nodes needed for operation
    mads_llnode_t *next_node = NULL, *new_node = NULL;

    // Asserts that list is not NULL and the position is within the list's size
    assert(list!=NULL && position<list->size);

    // If the position is 0, insert the node at the head of the list using mads_list_push
    if (position == 0)
    {
        mads_list_push(list, data);
    }
    // If the position is the last index, append the node to the list using mads_list_append
    else if (position == list->size - 1)
    {
        mads_list_append(list, data);
    }
    else
    {
        // Initialize step counter
        unsigned long long int step = 0;

        // Allocate memory for the new node
        new_node = (mads_llnode_t *)malloc(sizeof(*new_node));

        // Assert that memory allocation was successful
        assert(new_node!=NULL);

        // Assign data to the new node. new_node is not connected to any other nodes yet
        new_node->data = data;
        new_node->next = new_node->previous = NULL;

        // Point next_node to the head of the list to start traversal
        next_node = list->head;

        // Traverse until the position or the end of the list is reached
        while (next_node != NULL && step < position)
        {
            next_node = next_node->next;
            step++;
        }

        // Rearrange linkages to insert the new node at the correct position
        next_node->previous->next = new_node;
        new_node->previous = next_node->previous;
        next_node->previous = new_node;
        new_node->next = next_node;

        // Increment the size of the list
        list->size++;
    }
}


// This function retrieves the data stored at a particular position in the given list.
// The list and the position are passed as parameters.
// The function returns a pointer to the data found at the specified position.
//
// `list` is a pointer to the list where we are searching for data.
// `position` is the index of the item we are looking for in the list.
void *mads_list_get_at(const mads_list_t *list, const unsigned long long int position)
{
    // Declare a local constant pointer to struct mads_llnode_t that will traverse the list
    const mads_llnode_t *next_node = NULL;

    // Assert that the list is not NULL and the requested position is within the bounds of the list size
    assert(list!=NULL && position<list->size);

    // If the requested position is the head of the list, return the head
    if (position == 0)
    {
        return mads_list_get_head(list);
    }

    // If the requested position is the foot of the list, return the foot
    if (position == list->size - 1)
    {
        return mads_list_get_foot(list);
    }

    // Declare an unsigned long long int variable to keep track of the current position while traversing
    unsigned long long int step = 0;

    // Start traversing from the head of the list
    next_node = list->head;

    // Loop until the end of the list, or until the requested position is reached
    while (next_node != NULL && step <= position)
    {
        // Move to the next node
        next_node = next_node->next;

        // Increment the step
        step++;
    }

    // When the loop ends, next_node will be pointing to the node at the requested position
    // return the data stored in this node
    return next_node->data;
}

// This function retrieves the head of the list.
void *mads_list_get_head(const mads_list_t *list)
{
    assert(list!=NULL);
    return list->head->data;
}

// This function retrieves the foot of the list.
void *mads_list_get_foot(const mads_list_t *list)
{
    assert(list!=NULL);
    return list->foot->data;
}


// Implementing the mads_list_remove_head function
// This function removes the head (the first node) of the list
void mads_list_remove_head(mads_list_t *list)
{
    // Declare a pointer to a node that will temporarily hold the current head of the list
    mads_llnode_t *old_node = NULL;

    // Make sure the list is not NULL
    assert(list!=NULL);

    // If the list is empty, there is nothing to remove, so return from the function
    if (mads_list_is_empty(list)) { return; }

    // If the list has more than one node
    if (list->head != list->foot)
    {
        // The next node after the head will become the new head
        // So, set its previous node to NULL
        list->head->next->previous = NULL;

        // Temporarily store the current head in the old_node
        old_node = list->head;

        // Move the head pointer to the next node, which is now the new head
        list->head = list->head->next;

        // Disconnect the old head node from any other nodes
        old_node->next = old_node->previous = NULL;
    }
    else
    {
        // If the list has only one node, the head and the foot are the same
        // Temporarily store this node in the old_node
        old_node = list->head;

        // Remove the head and the foot of the list by setting them to NULL
        list->head = list->foot = NULL;
    }

    // If a destroy function was provided
    if (list->destroy != NULL)
    {
        // Use the destroy function to remove the data in the old head node
        list->destroy(old_node->data);
        // Then set the data pointer in the old_node to NULL
        old_node->data = NULL;
    }

    // Free the memory of the old head node
    free(old_node);

    // Just to be on the safe side, set the old_node pointer to NULL after freeing the memory it pointed to
    old_node = NULL;

    // As we removed a node, we need to decrement the list size
    list->size--;
}


// The function 'mads_list_remove_foot' is used to remove the last node (foot) from a list
void mads_list_remove_foot(mads_list_t *list)
{
    // Pointer to store the old foot node of the list
    mads_llnode_t *old_node = NULL;

    // Assert that the provided list pointer is not NULL
    assert(list!=NULL);

    // If the list is empty, there is nothing to remove, so we return
    if (mads_list_is_empty(list)) { return; }

    // If list's head is different from its foot, it means there are multiple nodes in the list
    if (list->foot != list->head)
    {
        // Make the node previous to the current foot node as the new foot of the list
        list->foot->previous->next = NULL;
        old_node = list->foot;

        // Update the foot pointer of the list to the previous node (the node which is now the new foot)
        list->foot = list->foot->previous;

        // Disconnect the old foot node's pointers
        old_node->next = old_node->previous = NULL;
    }
    else
    {
        // Situation where there is only one node in the list (i.e., head and foot are same)
        old_node = list->foot;

        // Empty the list by setting both the head and the foot to NULL
        list->foot = list->head = NULL;
    }

    // If there is a 'destroy' function specified in the list struct
    if (list->destroy != NULL)
    {
        // Use this function to clean up the data held by the old node
        list->destroy(old_node->data);
        old_node->data = NULL;
    }

    // Clean up the memory held by the old foot node
    free(old_node);
    old_node = NULL;

    // Finally, decrement the size of the list as we've removed a node
    list->size--;
}


// The below function `mads_list_remove_at` is used to remove a node at a specific position from the list.
void mads_list_remove_at(mads_list_t *list, const unsigned long long int position)
{
    // Pointers to hold the node that is going to be removed
    mads_llnode_t *old_node = NULL, *next_node = NULL;

    // Confirm the provided list is not NULL and the given position is within the list's size
    assert(list!=NULL && position<list->size);

    // If the list has no nodes then there is nothing to remove, so return
    if (mads_list_is_empty(list)) { return; }

    // If the position is at the head of the list
    if (position == 0)
    {
        // Remove the head of the list using existing function
        mads_list_remove_head(list);
    }
    // If the position is at the foot of the list
    else if (position == list->size - 1)
    {
        // Remove the foot of the list using existing function
        mads_list_remove_foot(list);
    }
    else
    {
        // For removing a node at a position other than head or foot
        unsigned long long int step = 0;
        next_node = list->head;

        // Traverse the list till the exact position is found
        while (next_node != NULL && step <= position)
        {
            next_node = next_node->next;
            step++;
        }

        // Set the previous node's next to the next node
        next_node->next->previous = next_node->previous;

        // Set the next node's previous to the previous node
        next_node->previous->next = next_node->next;

        // Store the removed node in old_node
        old_node = next_node;

        // Set previous and next of old_node to NULL as it is removed from the list
        old_node->previous = old_node->next = NULL;

        // if a destroy function was provided use it to properly free the data held by the node
        if (list->destroy != NULL)
        {
            list->destroy(old_node->data);
            old_node->data = NULL;
        }

        // Free the memory held by the node
        free(old_node);

        // Set old_node to NULL as a good practice after freeing memory
        old_node = NULL;

        // As we removed a node, decrement the list size
        list->size--;
    }
}


// The below function, `mads_list_print`, is used to print the elements of the `mads_list_t`
// `list` is the list whose element we want to print
void mads_list_print(const mads_list_t *list)
{
    // Declare a pointer to a list node, which will be used to traverse the list
    const mads_llnode_t *current_node = NULL;

    // Assert to ensure the list is not NULL
    assert(list!=NULL);

    // Start traversal from the head of the list
    current_node = list->head;

    // If the list is empty, print an empty set of brackets and return
    if (mads_list_is_empty(list) == 1)
    {
        printf("[]\n");
        return;
    }

    // If the list is not empty, begin the output with an opening bracket
    printf("[ ");

    // Traverse the list by following `next` pointers, until we reach a NULL pointer indicating the end of the list
    while (current_node != NULL)
    {
        // Print the data of the current node using the print function provided in `list`
        list->print(current_node->data);

        // After printing the data, print a comma and a space to separate elements
        printf(", ");

        // Move to the next node in the list
        current_node = current_node->next;
    }

    // After printing all elements, print two backspaces (to remove the
    // last comma and space) and a closing bracket followed by a newline
    printf("\b\b ]\n");
}


// The function `mads_list_free` is used to deallocate memory and cleanup
// the data if a cleanup function is provided
void mads_list_free(mads_list_t *list)
{
    // Declare pointers to nodes for traversal and cleanup
    mads_llnode_t *old_node = NULL, *next_node = NULL;

    // Assert that the given list is not NULL
    assert(list!=NULL);

    // Start traversing from head of the list
    next_node = list->head;

    // Traverse the list as long as there are elements
    while (next_node != NULL)
    {
        // If a destroy function is provided in the list structure
        if (list->destroy != NULL)
        {
            // Use it to cleanup the data of the node
            list->destroy(next_node->data);

            // After cleaning, ensure that we set it to NULL
            next_node->data = NULL;
        }

        // Remember the node to be cleaned in old_node
        old_node = next_node;

        // Move to the next node
        next_node = next_node->next;

        // Free the memory of the old node
        free(old_node);

        // Set our reference to old node to NULL for safety
        old_node = NULL;
    }

    // Getting here means we have cleaned up all nodes, so clean up the list itself
    old_node = NULL; // for safety although not much effect as old_node will go out of scope
    free(list);

    // For safety set list pointer to NULL to prevent it from being a dangling pointer
    list = NULL;
}


// The function returns the size of the list.
unsigned long long int mads_list_size(const mads_list_t *list)
{
    assert(list!=NULL);
    return (list->size);
}


// Function to check whether a given list is empty or not.
// It does so by checking whether the size of the list is 0 or not.
// If the size of the list is 0, then it means there are no elements in the list.
// The function then returns 1 if the list is empty, or 0 if it is not.
// Assert is used here to ensure that the list pointer provided is not NULL.
int mads_list_is_empty(const mads_list_t *list)
{
    assert(list!=NULL);
    return (list->size == 0 ? 1 : 0);
}

// Function to check whether a specified element exists in the list.
int mads_list_has_elem(const mads_list_t *list, const void *item)
{
    unsigned long long int step = 0;
    const mads_llnode_t *next_node = NULL;
    assert(list!=NULL);
    next_node = list->head;

    // The function goes through each node in the list by following the `next` links.
    while (next_node != NULL)
    {
        // For each node, it uses the `cmp` function pointer of the list
        // structure to check if the `data` of the node matches the `item`.
        const int result = list->cmp(next_node->data, item);

        if (result == 0)
        {
            // If a match is found, the function returns the index of the node in the list.
            return step;
        }

        step++;
        next_node = next_node->next;
    }

    // If no match is found after traversing the entire list,
    // it returns -1 to indicate that the `item` does not exist in the list.
    next_node = NULL;
    return -1; // Returning -1 indicates that the element was not found in the list
}
