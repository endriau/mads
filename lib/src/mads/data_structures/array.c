// ReSharper disable CppDFANullDereference



// Including the necessary libraries.
// Stdio.h is included for input/output operations.
// Stdlib.h is included for dynamic memory allocation.
// Assert.h is included to provide a macro called assert() which can be used to verify assumptions made by the program
// and print a diagnostic message if this assumption is false.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Including the header file for mads_array_t.
#include <mads/data_structures/array.h>

// The function for creating a new mads array. It takes three function pointers as parameters.
// Comparator function is used to compare 2 data elements. It should return 0 if both elements are equal,
// negative number if element-1 is smaller and positive number if element-1 is larger.
// Printer function is used to print a data element.
// Destructor function is used to deallocate memory for a data element.
mads_array_t *mads_array_create(const mads_array_comparator_fn comparator, const mads_array_printer_fn printer, const mads_array_destructor_fn destructor)
{
    // Initialize a pointer to the new array as NULL.
    mads_array_t *new_array = NULL;

    // Set the initial size for the array.
    const long long int initial_msize = 16;

    // Check that both comparator and printer functions are provided. If not, throw an assertion error.
    assert(comparator != NULL && printer != NULL);

    // Allocate memory for the mads array. If memory allocation fails, an assertion error is thrown.
    new_array = (mads_array_t *)malloc(sizeof(*new_array));
    assert(new_array != NULL);

    // Allocate memory for the array blocks. If memory allocation fails, an assertion error is thrown.
    new_array->mblocks = (void **)malloc(initial_msize * sizeof(void *));
    assert(new_array->mblocks != NULL);

    // Set the array size as the initial size.
    new_array->msize = initial_msize;

    // Set the initial index for the array as -1 (empty).
    new_array->index = -1;

    // Attach the comparator, printer and destructor functions to the array object.
    new_array->comparator = comparator;
    new_array->printer = printer;
    new_array->destructor = destructor;

    // Return the newly created array.
    return new_array;
}

// Function to return the memory blocks of the array.
void **mads_array_data(const mads_array_t *array)
{
    // Check if the array is not NULL. If it is, throw an assertion error.
    assert(array != NULL);

    // Return the memory blocks of the array.
    return array->mblocks;
}


// The function that appends data to the array.
void mads_array_append(mads_array_t *array, void *data)
{
    // Check if the array is not NULL. If it is, throw an assertion error.
    assert(array != NULL);

    // Insert the data at the end of the array.
    mads_array_insert_at(array, array->index + 1, data);
}

// The function that prepends data to the array.
void mads_array_prepend(mads_array_t *array, void *data)
{
    // Check if the array is not NULL. If it is, throw an assertion error.
    assert(array != NULL);

    // Insert the data at the beginning of the array.
    mads_array_insert_at(array, 0, data);
}

// The function that inserts data at a specific location in the array.
void mads_array_insert_at(mads_array_t *array, const long long int index, void *data)
{
    // Check if the array is not NULL. If it is, throw an assertion error.
    assert(array != NULL);

    // Check if the index is within the correct range. If it is not, throw an assertion error.
    assert(index >= 0 && index <= array->index + 1);

    // Check if the array has reached its maximum capacity. If it has, double the size.
    if (array->index + 1 == array->msize)
    {
        const long long int double_msize = 2 * array->msize;
        array->mblocks = (void **)realloc(array->mblocks, double_msize * sizeof(void *)); // NOLINT(*-suspicious-realloc-usage)
        assert(array->mblocks != NULL);
        array->msize = double_msize;
    }

    // Index increase for the new element.
    array->index++;

    // Shift all elements to the right of the index one place to the right.
    for (long long int i = array->index; i > index; i--) { array->mblocks[i] = array->mblocks[i - 1]; }

    // Insert the new element at the correct position.
    array->mblocks[index] = data;
}

// The function that removes the data at a specific position in the array.
void mads_array_remove_at(mads_array_t *array, const long long int index)
{
    // Check if the array is not NULL. If it is, throw an assertion error.
    assert(array != NULL);

    // Check if the index is within the correct range. If it is not, throw an assertion error.
    assert(index >= 0 && index <= array->index);

    // If the destructor function is available, call it.
    if (array->destructor != NULL)
    {
        array->destructor(array->mblocks[index]);
        array->mblocks[index] = NULL;
    }

    // Shift all elements to the right of the index one place to the left.
    for (long long int i = index; i < array->index; i++) { array->mblocks[i] = array->mblocks[i + 1]; }

    // Index decrease after the deletion.
    array->index--;
}

// The function that updates the data at a specific position in the array.
void mads_array_set_at(const mads_array_t *array, const long long int index, void *data)
{
    // Check if the array is not NULL. If it is, throw an assertion error.
    assert(array != NULL);

    // Check if the index is within the correct range. If it is not, throw an assertion error.
    assert(index >= 0 && index <= array->index);

    // If the destructor function is available, free the old data
    if (array->destructor != NULL) { array->destructor(array->mblocks[index]); }

    // Set the new data at the correct position.
    array->mblocks[index] = data;
}

// The function that retrieves data from a specific position in the array.
void *mads_array_get_at(const mads_array_t *array, const long long int index)
{
    // Check if the array is not NULL. If it is, throw an assertion error.
    assert(array != NULL);

    // Check if the index is within the correct range. If it is not, throw an assertion error.
    assert(index >= 0 && index <= array->index);

    // Return the data at the requested index.
    return array->mblocks[index];
}

// The function that searches for an item in the array and returns the index it was found at. If not found, it returns -1.
long long int mads_array_has_element(const mads_array_t *array, const void *item)
{
    // Check if the array is not NULL. If it is, throw an assertion error.
    assert(array != NULL);

    // Iterate over the array and use the comparator function to check if the item is in the array.
    for (long long int i = 0; i <= array->index; i++)
    {
        const int result = array->comparator(array->mblocks[i], item);
        if (result == 0) { return i; }
    }

    // If the item was not found, return -1.
    return -1;
}

// The function that returns the current size of the array.
long long int mads_array_size(const mads_array_t *array)
{
    // Check if the array is not NULL. If it is, throw an assertion error.
    assert(array != NULL);

    // Return the current size of the array.
    return (array->index + 1);
}

// The function that checks if the array is empty.
int mads_array_is_empty(const mads_array_t *array)
{
    // Check if the array is not NULL. If it is, throw an assertion error.
    assert(array != NULL);

    // Check if the index is -1. If it is, return 1 indicating the array is empty. Otherwise, return 0.
    return (array->index == -1 ? 1 : 0);
}

// The function that clears the array by removing all elements.
void mads_array_clear(mads_array_t *array)
{
    // Check if the array is not NULL. If it is, throw an assertion error.
    assert(array != NULL);

    // If the destructor function is available, iterate over the array and free all elements using the destructor.
    if (array->destructor != NULL)
    {
        for (long long int i = 0; i <= array->index; i++)
        {
            array->destructor(array->mblocks[i]);
            array->mblocks[i] = NULL;
        }
    }

    // Set the array's index to -1 (empty).
    array->index = -1;
}

// The function that prints all items in the array.
void mads_array_print(const mads_array_t *array)
{
    // Check if the array is not NULL. If it is, throw an assertion error.
    assert(array != NULL);

    // If the array is empty, print an empty bracket pair and return.
    if (mads_array_is_empty(array))
    {
        printf("[ ]\n");
        return;
    }

    // Print the items in the array using the printer function.
    printf("[ ");
    for (long long int i = 0; i <= array->index; i++)
    {
        array->printer(array->mblocks[i]);
        printf(", ");
    }
    printf("\b\b ]\n");
}

// The function that frees the mads array by removing all elements and then freeing the array itself.
void mads_array_free(mads_array_t **array)
{
    // Check if the array is not NULL. If it is, throw an assertion error.
    assert((*array) != NULL);

    // If the destructor function is available, iterate over the array and free all elements using the destructor.
    if ((*array)->destructor != NULL)
    {
        for (long long int i = 0; i <= (*array)->index; i++)
        {
            (*array)->destructor((*array)->mblocks[i]);
            (*array)->mblocks[i] = NULL;
        }
    }

    // Free the array blocks and set the pointer to NULL.
    free((*array)->mblocks);
    (*array)->mblocks = NULL;

    // Set the function pointers to NULL.
    (*array)->comparator = NULL;
    (*array)->printer = NULL;
    (*array)->destructor = NULL;

    // Free the mads array and set the pointer to NULL.
    free(*array); *array = NULL;
}
