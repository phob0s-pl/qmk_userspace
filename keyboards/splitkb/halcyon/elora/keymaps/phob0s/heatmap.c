// Śledzenie "ciepła" klawiszy dla heatmapy na wyświetlaczu.
// Kompilowane w OBU połowach: master zlicza i wygasza ciepło (process_record
// działa tylko na masterze), a snapshot wysyła RPC do drugiej połowy, więc
// heatmapa działa niezależnie od tego, w którą połowę wpięto USB.
#include QMK_KEYBOARD_H
#include "transactions.h"
#include "heatmap.h"

#define HM_HEAT_PER_PRESS 70
#define HM_DECAY_MS 360 // pełne wystygnięcie klawisza ~20 s (heatmapa pokazuje dłuższe okno pisania)
#define HM_SYNC_MS 150

uint8_t hm_heat[MATRIX_ROWS][HM_MATRIX_COLS];

static bool hm_needs_sync = false;

// Wolane z process_record_user w keymap.c
void hm_record(keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t r = record->event.key.row;
        uint8_t c = record->event.key.col;
        if (r < MATRIX_ROWS && c < HM_MATRIX_COLS) {
            uint16_t h = hm_heat[r][c] + HM_HEAT_PER_PRESS;
            hm_heat[r][c] = h > 255 ? 255 : h;
            hm_needs_sync = true;
        }
    }
}

static void hm_sync_slave_handler(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(hm_heat)) {
        memcpy(hm_heat, initiator2target_buffer, sizeof(hm_heat));
    }
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_HEATMAP, hm_sync_slave_handler);
}

#ifdef POINTING_DEVICE_ENABLE
// QMK #25315 (2025-06) trwale wyłącza pointing task po nieudanym probe czujnika.
// Przy POINTING_DEVICE_COMBINED (halcyon) połowa z wyświetlaczem nie ma trackpada,
// więc jej probe zawsze pada — i blokuje odczyt raportu z drugiej połowy na masterze.
// Ponawiamy init (wolno startujący Pinnacle), a po 6 próbach wymuszamy SUCCESS,
// czyli zachowanie sprzed #25315.
static void pd_status_watchdog(void) {
    static uint8_t  tries = 0;
    static uint32_t last  = 0;
    if (pointing_device_get_status() == POINTING_DEVICE_STATUS_SUCCESS) return;
    if (timer_elapsed32(last) < 500) return;
    last = timer_read32();
    if (tries < 6) {
        tries++;
        pointing_device_init();
    } else {
        pointing_device_set_status(POINTING_DEVICE_STATUS_SUCCESS);
    }
}
#endif

void housekeeping_task_user(void) {
#ifdef POINTING_DEVICE_ENABLE
    pd_status_watchdog(); // na obu połowach, także na slave
#endif

    if (!is_keyboard_master()) {
        return;
    }

    static uint32_t last_decay = 0;
    if (timer_elapsed32(last_decay) >= HM_DECAY_MS) {
        last_decay = timer_read32();
        for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
            for (uint8_t c = 0; c < HM_MATRIX_COLS; c++) {
                uint8_t h = hm_heat[r][c];
                if (h) {
                    uint8_t step = (h >> 4) + 1;
                    hm_heat[r][c] = step >= h ? 0 : h - step;
                    hm_needs_sync = true;
                }
            }
        }
    }

    static uint32_t last_sync = 0;
    if (hm_needs_sync && timer_elapsed32(last_sync) >= HM_SYNC_MS) {
        if (transaction_rpc_send(USER_SYNC_HEATMAP, sizeof(hm_heat), hm_heat)) {
            last_sync = timer_read32();
            hm_needs_sync = false;
        }
    }
}
