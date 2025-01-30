// ReSharper disable CppParameterMayBeConstPtrOrRef
// ReSharper disable CppRedundantCastExpression


#include <assert.h>
#include <stdlib.h>
#include <mads/signals/slot.h>

mads_slot_t *mads_slot_create(void *context, const mads_slot_fn function)
{
    assert(context != NULL && function != NULL);
    mads_slot_t *slot = (mads_slot_t *)malloc(sizeof(mads_slot_t));
    assert(slot != NULL);
    slot->blocked = 0;
    slot->context = context;
    slot->function = function;
    return slot;
}

void mads_slot_free(mads_slot_t **slot)
{
    assert(*slot != NULL);
    (*slot)->context = NULL;
    (*slot)->function = NULL;
    free(*slot);
    *slot = NULL;
}
