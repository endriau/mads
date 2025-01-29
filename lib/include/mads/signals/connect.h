#ifndef MADS_SIGNALS_CONNECT_H
#define MADS_SIGNALS_CONNECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mads_export.h>

#include <mads/signals/slot.h>
#include <mads/signals/signal.h>

MADS_EXPORT void mads_connect(void *context, mads_signal_t *signal, mads_slot_fn function);
MADS_EXPORT void mads_disconnect(const void *context, mads_signal_t *signal, mads_slot_fn function);
MADS_EXPORT void mads_emit(mads_signal_t *signal, void *data);

#ifdef __cplusplus
}
#endif

#endif //MADS_SIGNALS_CONNECT_H
