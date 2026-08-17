#pragma once

// --- Tap-hold: QMK-owy odpowiednik "timeless HRM" ---
#define TAPPING_TERM 250
#define PERMISSIVE_HOLD
#define CHORDAL_HOLD          // mod tylko przy chordzie na przeciwne ręce
#define FLOW_TAP_TERM 150     // szybkie rolki = zawsze tap; zejdź do ~100 jeśli zjada skróty tuż po literze

// --- Caps Word ---
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 3000

// --- Komba ---
#define COMBO_TERM 25         // podnieś, jeśli komba nie łapią; obniż przy misfire'ach na rolkach

// --- One-shot ---
#define ONESHOT_TIMEOUT 2000  // wiszący ⌥R/Hyper gaśnie po 2 s (wskaźnik i tak masz na wyświetlaczu)

// --- RGB underglow (74 LED): przywrócone klasy efektów + nowości z QMK master ---
#define RGB_MATRIX_KEYPRESSES          // odblokowuje reaktywne efekty z keyboard.json (solid_reactive*, splash)
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS // typing_heatmap, digital_rain
#define ENABLE_RGB_MATRIX_STARLIGHT
#define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE
#define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT
#define ENABLE_RGB_MATRIX_STARLIGHT_SMOOTH   // nowość z 2025
#define ENABLE_RGB_MATRIX_RIVERFLOW
#define ENABLE_RGB_MATRIX_FLOWER_BLOOMING

// --- Wyświetlacz: WPM + heatmapa przez split (działa niezależnie od strony USB) ---
#define SPLIT_WPM_ENABLE
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_HEATMAP
#define RPC_M2S_BUFFER_SIZE 80  // domyślne 32 to za mało na 70-bajtowy snapshot heatmapy
