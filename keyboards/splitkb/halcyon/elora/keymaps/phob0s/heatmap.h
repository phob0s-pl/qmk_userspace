#pragma once

#include <stdint.h>

// Physical key columns per matrix row; higher columns are halcyon module buttons.
#define HM_MATRIX_COLS 7

extern uint8_t hm_heat[MATRIX_ROWS][HM_MATRIX_COLS];

void hm_record(keyrecord_t *record);
