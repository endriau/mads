// Include necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mads/data_structures/pair.h>


// Function to create a cue (key) with provided comparison, printing, and destroying functions.
mads_cue_t *mads_cue_create(void *cue, const mads_cue_comparator_fn comparator, const mads_cue_printer_fn printer, const mads_cue_destructor_fn destructor)
{
    // Declare new cue
    mads_cue_t *new_cue = NULL;

    // Check to ensure that necessary function pointers are not null
    assert(comparator != NULL && printer != NULL);

    // Allocate memory for new cue
    new_cue = (mads_cue_t *)malloc(sizeof(mads_cue_t));

    // Check to ensure that memory allocation was successful
    assert(new_cue!=NULL);

    // Assign provided arguments to corresponding fields
    new_cue->cue = cue;
    new_cue->comparator = comparator;
    new_cue->printer = printer;
    new_cue->destructor = destructor;

    // Return the new cue
    return new_cue;
}

// Function to retrieve the cue from a provided mads_cue_t object
void *mads_cue_get(const mads_cue_t *k)
{
    // Check to ensure that the object is not null
    assert(k != NULL);

    // Return the cue
    return k->cue;
}

// Function to compare the value in a given cue with provided data
int mads_cue_compare_to(const mads_cue_t *k, const void *data)
{
    // Check to ensure that the object is not null
    assert(k != NULL);

    // Perform the comparison
    const int result = k->comparator(k->cue, data);

    // Return the result
    return result;
}

// Function to print the cue in a given mads_cue_t object
void mads_cue_print(const mads_cue_t *k)
{
    // Check to ensure that the object is not null
    assert(k != NULL);

    // Run the print function
    k->printer(k->cue);
}

// Function to free the memory associated with a mads_cue_t object
void mads_cue_free(mads_cue_t *k)
{
    // Check to ensure that the object is not null
    assert(k != NULL);

    // Run the destroy function if it exists
    if (k->destructor != NULL) { k->destructor(k->cue); }

    // Clear function pointers and free memory
    k->comparator = NULL;
    k->printer = NULL;
    k->destructor = NULL;
    free(k);
    k = NULL;
}


// Function to create a value object with provided comparison, printing, and destroying functions
mads_value_t *mads_value_create(void *value, const mads_value_comparator_fn comparator, const mads_value_printer_fn printer, const mads_value_destructor_fn destructor)
{
    // Declare variable for the new value object
    mads_value_t *new_value = NULL;

    // Check to ensure that necessary function pointers are not null
    assert(comparator != NULL && printer != NULL);

    // Allocate memory for the new value object
    new_value = (mads_value_t *)malloc(sizeof(mads_value_t));

    // Check to ensure that memory allocation was successful
    assert(new_value!=NULL);

    // Assign provided arguments to the corresponding fields of the value object
    new_value->value = value;
    new_value->comparator = comparator;
    new_value->printer = printer;
    new_value->destructor = destructor;

    // Return the new value object
    return new_value;
}



// Function to get the value from a mads_value_t object
void *mads_value_get(const mads_value_t *v)
{
    // Ensure that the mads_value_t object is not null
    assert(v != NULL);

    // Return the value stored in the object
    return v->value;
}

// Function to compare the value in mads_value_t with provided data
int mads_value_compare_to(const mads_value_t *v, const void *data)
{
    // Ensure that the mads_value_t object is not null
    assert(v != NULL);

    // Perform the comparison using the comparison function defined in mads_value_t
    const int result = v->comparator(v->value, data);

    // Return the result of the comparison
    return result;
}

// Function to print the value stored in mads_value_t
void mads_value_print(const mads_value_t *v)
{
    // Ensure that the mads_value_t object is not null
    assert(v != NULL);

    // Use the printing function defined in mads_value_t to print the value
    v->printer(v->value);
}

// Function to free the memory occupied by mads_value_t and its value
void mads_value_free(mads_value_t *v)
{
    // Ensure that the mads_value_t object is not null
    assert(v != NULL);

    // Invoke the destroy function in mads_value_t when such function exists
    if (v->destructor != NULL) { v->destructor(v->value); }

    // Clear all function pointers
    v->comparator = NULL;
    v->printer = NULL;
    v->destructor = NULL;

    // Free the memory occupied by the mads_value_t object itself
    free(v);

    // Nullify the pointer
    v = NULL;
}


// Function to create a key-value pair
mads_pair_t *mads_pair_create(mads_cue_t *k, mads_value_t *v)
{
    // Declare new pair variable
    mads_pair_t *new_pair = NULL;

    // Assert that key and value pointers are not NULL
    assert(k != NULL && v != NULL);

    // Allocate memory for the new pair
    new_pair = (mads_pair_t *)malloc(sizeof(mads_pair_t));

    // Assert that memory allocation was successful
    assert(new_pair != NULL);

    // Point to the key and value
    new_pair->k = k;
    new_pair->v = v;

    // Return the new key-value pair
    return new_pair;
}


// Gets the key (cue) from a provided key-value pair
mads_cue_t *mads_pair_get_cue(const mads_pair_t *p)
{
    // Ensure that the key-value pair is not null
    assert(p != NULL);

    // Return the key from the pair
    return p->k;
}

// Function to retrieve the value from a key-value pair
mads_value_t *mads_pair_get_value(const mads_pair_t *p)
{
    // Ensure that the pair is not null
    assert(p != NULL);

    // Return the value from the pair
    return p->v;
}

// Function to change the key in a key-value pair
void mads_pair_change_cue(mads_pair_t *p, mads_cue_t *new_k)
{
    // Pointer to keep track of the old key before changing it
    mads_cue_t *old_cue = NULL;

    // Ensure that the pair and the new key are not null
    assert(p != NULL && new_k != NULL);

    // Get the old key from the pair
    old_cue = mads_pair_get_cue(p);

    // Free the memory associated with the old key
    mads_cue_free(old_cue);

    // Replace the old key with the new key in the pair
    p->k = new_k;
}

// Function for changing the value in a key-value pair
void mads_pair_change_value(mads_pair_t *p, mads_value_t *new_v)
{
    // Pointer to keep track of the old value before changing it
    mads_value_t *old_value = NULL;

    // Ensure that the pair and the new value are not null
    assert(p != NULL && new_v != NULL);

    // Get the old value from the pair
    old_value = mads_pair_get_value(p);

    // Free the memory associated with the old value
    mads_value_free(old_value);

    // Replace the old value with the new value in the pair
    p->v = new_v;
}

// Function for printing a key-value pair
void mads_pair_print(const mads_pair_t *p)
{
    // Ensure the pair is not null
    assert(p != NULL);

    // Temporary pointers to retrieve the key and value components of the pair
    const mads_cue_t *temp_cue = NULL;
    const mads_value_t *temp_value = NULL;

    // Retrieve the key and value from the pair
    temp_cue = mads_pair_get_cue(p);
    temp_value = mads_pair_get_value(p);

    // Print the key and value in a user-friendly format
    printf("{ ");
    mads_cue_print(temp_cue);
    printf(" : ");
    mads_value_print(temp_value);
    printf(" }");
}

// Function for freeing the memory associated with a key-value pair
void mads_pair_free(mads_pair_t *p)
{
    // Ensure that the pair is not null
    assert(p != NULL);

    // Free the memory associated with the value component of the pair
    mads_value_free(mads_pair_get_value(p));

    // Free the memory associated with the key component of the pair
    mads_cue_free(mads_pair_get_cue(p));

    // Free the memory for the pair itself
    free(p);

    // Zero out the pointer for safety
    p = NULL;
}