#ifndef MADS_SIGNALS_SIGNAL_H
#define MADS_SIGNALS_SIGNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <threads.h>
#include <mads_export.h>
#include <mads/data_structures/array.h>

typedef struct
{
    mtx_t mutex;
    mads_array_t *connections;
} mads_signal_t;


MADS_EXPORT mads_signal_t *mads_signal_create();
MADS_EXPORT void mads_signal_clear(const mads_signal_t *signal);
MADS_EXPORT void mads_signal_free(mads_signal_t **signal);

#ifdef __cplusplus
}
#endif


#endif //MADS_SIGNALS_SIGNAL_H
