#include <assert.h>
#include <threads.h>
#include <mads/signals/connect.h>
#include <mads/data_structures/array.h>


void mads_connect(void *context, mads_signal_t *signal, const mads_slot_fn function)
{
    assert(context != NULL && signal != NULL && function != NULL);

    mtx_lock(&signal->mutex);

    mads_slot_t *slot = mads_slot_create(context, function);
    mads_array_append(signal->connections, slot);

    mtx_unlock(&signal->mutex);
}


void mads_disconnect(const void *context, mads_signal_t *signal, mads_slot_fn function)
{
    assert(context != NULL && signal != NULL && function != NULL);

    mtx_lock(&signal->mutex);

    for (size_t i = 0; i < mads_array_size(signal->connections); i++)
    {
        const mads_slot_t *slot = mads_array_get_at(signal->connections, i);
        if (slot->context == context && slot->function == function)
        {
            mads_array_remove_at(signal->connections, i);
            break;
        }
    }

    mtx_unlock(&signal->mutex);
}

void mads_emit(mads_signal_t *signal, void *data)
{
    assert(signal != NULL && data != NULL);

    mtx_lock(&signal->mutex);

    for (size_t i = 0; i < mads_array_size(signal->connections); i++)
    {
        const mads_slot_t *current_slot = (mads_slot_t *)mads_array_get_at(signal->connections, i);
        current_slot->function(current_slot->context, data);
    }

    mtx_unlock(&signal->mutex);
}
