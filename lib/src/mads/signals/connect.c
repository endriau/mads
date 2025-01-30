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


void mads_disconnect(const void *context, mads_signal_t *signal, const mads_slot_fn function)
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

void mads_block_all(const void *context, mads_signal_t *signal)
{
    assert(context != NULL && signal != NULL);

    mtx_lock(&signal->mutex);

    for (size_t i = 0; i < mads_array_size(signal->connections); i++)
    {
        mads_slot_t *slot = mads_array_get_at(signal->connections, i);

        if (slot->context == context)
        {
            slot->blocked = 1;
        }
    }

    mtx_unlock(&signal->mutex);
}

void mads_unblock_all(const void *context, mads_signal_t *signal)
{
    assert(context != NULL && signal != NULL);
    mtx_lock(&signal->mutex);
    for (size_t i = 0; i < mads_array_size(signal->connections); i++)
    {
        mads_slot_t *slot = mads_array_get_at(signal->connections, i);

        if (slot->context == context)
        {
            slot->blocked = 0;
        }
    }

    mtx_unlock(&signal->mutex);
}

void mads_block(const void *context, mads_signal_t *signal, const mads_slot_fn function)
{
    assert(context != NULL && signal != NULL && function != NULL);

    mtx_lock(&signal->mutex);

    for (size_t i = 0; i < mads_array_size(signal->connections); i++)
    {
        mads_slot_t *slot = mads_array_get_at(signal->connections, i);

        if (slot->context == context && slot->function == function)
        {
            slot->blocked = 1;
            break;
        }
    }

    mtx_unlock(&signal->mutex);
}

void mads_unblock(const void *context, mads_signal_t *signal, const mads_slot_fn function)
{
    assert(context != NULL && signal != NULL && function != NULL);
    mtx_lock(&signal->mutex);

    for (size_t i = 0; i < mads_array_size(signal->connections); i++)
    {
        mads_slot_t *slot = mads_array_get_at(signal->connections, i);

        if (slot->context == context && slot->function == function)
        {
            slot->blocked = 0;
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

        if (!current_slot->blocked)
        {
            current_slot->function(data, current_slot->context);
        }
    }

    mtx_unlock(&signal->mutex);
}
