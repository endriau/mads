// ReSharper disable CppRedundantCastExpression


#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <mads/signals/signal.h>
#include <mads/signals/slot.h>


static int slots_array_compare_fn(const void *x, const void *y)
{
    return (int)((uintptr_t)x - (uintptr_t)y);
}


static void slots_array_print_fn(const void *s)
{
    const mads_slot_t *slot = s;
    printf("%p", slot);
}

static void slots_array_destroy_fn(void *s)
{
    mads_slot_t *slot = s;
    mads_slot_free(&slot);
}

mads_signal_t *mads_signal_create()
{
    mads_signal_t *signal = (mads_signal_t *)malloc(sizeof(mads_signal_t));
    assert(signal != NULL);

    signal->connections = mads_array_create(
        slots_array_compare_fn,
        slots_array_print_fn,
        slots_array_destroy_fn);

    mtx_init(&signal->mutex, mtx_plain);
    return signal;
}

void mads_signal_clear(const mads_signal_t *signal)
{
    assert(signal != NULL);
    mads_array_clear(signal->connections);
}

void mads_signal_free(mads_signal_t **signal)
{
    assert(*signal != NULL);
    mads_array_free(&(*signal)->connections);
    mtx_destroy(&(*signal)->mutex);
    free(*signal);
    *signal = NULL;
}
