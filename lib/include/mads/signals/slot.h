#ifndef MADS_SIGNALS_SLOT_H
#define MADS_SIGNALS_SLOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mads_export.h>

typedef void (*mads_slot_fn)(void *context, void *data);

typedef struct
{
    void *context;
    mads_slot_fn function;
} mads_slot_t;


MADS_EXPORT mads_slot_t *mads_slot_create(void *context, mads_slot_fn function);
MADS_EXPORT void mads_slot_free(mads_slot_t **slot);

#ifdef __cplusplus
}
#endif

#endif //MADS_SIGNALS_SLOT_H
