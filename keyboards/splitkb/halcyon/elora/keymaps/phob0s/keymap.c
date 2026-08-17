// Keymap: QWERTY + CAGS HRM, mac-first, splitkb Halcyon Elora rev2
// Repo: qmk_userspace (splitkb halcyon branch) overlay na qmk_firmware master
// Build (jedna kompilacja na moduł, kazda połowa dostaje własny .uf2):
//   qmk compile -kb splitkb/halcyon/elora/rev2 -km phob0s -e HLC_TFT_DISPLAY=1     -e TARGET=splitkb_halcyon_elora_rev2_phob0s_display
//   qmk compile -kb splitkb/halcyon/elora/rev2 -km phob0s -e HLC_CIRQUE_TRACKPAD=1 -e TARGET=splitkb_halcyon_elora_rev2_phob0s_trackpad

#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _NAV,
    _SYM,
    _NUM,
    _WM,
    _FUN,
    _MEDIA,
};

// --- Home row mods: CAGS (⌃ ⌥ ⌘ ⇧ od małego palca) ---
#define HM_A LCTL_T(KC_A)
#define HM_S LALT_T(KC_S)
#define HM_D LGUI_T(KC_D)
#define HM_F LSFT_T(KC_F)
#define HM_J RSFT_T(KC_J)
#define HM_K RGUI_T(KC_K)
#define HM_L LALT_T(KC_L)   // LALT po obu stronach: RALT zostaje semantycznie AltGr-em (istotne po CG⇄ na Linuksie)
#define HM_QUO RCTL_T(KC_QUOT) // ' na home pinky; ; zostaje tylko na warstwie SYM (tak jak było w Colemaku)

// --- Kciuki ---
#define TH_ESC LT(_MEDIA, KC_ESC)
#define TH_SPC LT(_NAV,   KC_SPC)
#define TH_TAB LT(_WM,    KC_TAB)
#define TH_ENT LT(_SYM,   KC_ENT)
#define TH_BSP LT(_NUM,   KC_BSPC)
#define TH_DEL LT(_FUN,   KC_DEL)
#define OS_HYP OSM(MOD_HYPR)
#define OS_RALT OSM(MOD_RALT)   // polskie znaki: tap -> nast. litera z ⌥; trzymany działa jak zwykły ⌥ (serie ąćę)

// --- Sticky mody na warstwach (przeciwna dłoń, pozycje CAGS) ---
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_RSFT OSM(MOD_RSFT)

// --- Nav: macowe idiomy ---
#define NAV_BCK G(KC_LBRC)      // ⌘[  wstecz (kod/przeglądarka)
#define NAV_FWD G(KC_RBRC)      // ⌘]  dalej
#define WRD_L   A(KC_LEFT)      // ⌥←  słowo
#define WRD_R   A(KC_RGHT)
#define LIN_L   G(KC_LEFT)      // ⌘←  początek linii
#define LIN_R   G(KC_RGHT)
#define TAB_L   LSG(KC_LBRC)    // ⌘⇧[ poprzednia karta
#define TAB_R   LSG(KC_RBRC)

// --- Media: zrzuty ekranu ---
#define SCR_3 LSG(KC_3)
#define SCR_4 LSG(KC_4)
#define SCR_5 LSG(KC_5)

// --- WM: natywny kafelkowy macOS (Sequoia+). Chordy ✦+litera trzeba raz podpiąć w
// System Settings -> Keyboard -> Keyboard Shortcuts -> App Shortcuts -> All Applications,
// pod pozycje menu "Window->Move & Resize->..." (pełna ścieżka, tytuły w języku systemu).
#define SPC_L  C(KC_LEFT)          // Spaces natywnie przez ⌃←/⌃→
#define SPC_R  C(KC_RGHT)
#define WM_FULL  C(G(KC_F))        // ⌃⌘F - natywny fullscreen, bez konfiguracji
#define WM_HLF_L HYPR(KC_H)        // Window->Move & Resize->Left
#define WM_HLF_R HYPR(KC_L)        // ...->Right
#define WM_TOP   HYPR(KC_T)        // ...->Top
#define WM_BOT   HYPR(KC_B)        // ...->Bottom
#define WM_FILL  HYPR(KC_F)        // ...->Fill
#define WM_CTR   HYPR(KC_C)        // ...->Center
#define WM_RET   HYPR(KC_R)        // ...->Return to Previous Size
#define APP_LST  G(KC_TAB)         // tap = przeskok do poprzedniej aplikacji

// --- Rogi i klawisze przy kciukach: praca jedną ręką gdy prawa jest na trackpadzie ---
// (Chordal Hold blokuje jednoreczne chordy przez HRM, wiec prawdziwy ⌘ w lewym rogu)
#define UNDO    G(KC_Z)
#define REDO    LSG(KC_Z)
#define MAC_LCK C(G(KC_Q))         // blokada ekranu — rzadko, ale świadomie

// --- Swapper: jednoprzyciskowe ⌘Tab (styl Calluma). Trzymaj Tab (warstwa WM),
// stukaj SW_FWD/SW_REV zeby krazyc po aplikacjach; puszczenie warstwy zatwierdza wybor.
enum custom_keycodes {
    SW_FWD = SAFE_RANGE,
    SW_REV,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Base: QWERTY. Skrajne kolumny: lewa ~ / CapsWord / ⇧ / ⌘ (jednoręczne ⌘ZXCV przy
// trackpadzie), prawa PgUp / PgDn / ⇧ / blokada ekranu. Tab, Bksp i Enter tylko na kciukach.
// Przy kciukach: ⌘Z ⌘⇧Z (lewa) i fizyczne kliknięcia myszy przy trackpadzie (prawa).
// ' na home pinky (z ⌃), ; tylko na warstwie SYM.
    [_BASE] = LAYOUT(
     KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_PGUP,
     CW_TOGG, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_PGDN,
     KC_LSFT, HM_A   , HM_S   , HM_D   , HM_F   , KC_G   ,                                     KC_H   , HM_J   , HM_K   , HM_L   , HM_QUO , KC_RSFT,
     KC_LGUI, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , UNDO   , REDO   , MS_BTN1, MS_BTN2, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, MAC_LCK,
                                QK_REP , OS_HYP , TH_ESC , TH_SPC , TH_TAB , TH_ENT , TH_BSP , TH_DEL , OS_RALT, APP_LST
    ),

// Nav (hold Spc): strzałki na home, piętro wyżej = słowo (⌥), niżej = linia (⌘); lewa dłoń = sticky mody.
    [_NAV] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                                     NAV_BCK, WRD_L  , KC_PGUP, WRD_R  , NAV_FWD, _______,
     _______, OS_LCTL, OS_LALT, OS_LGUI, OS_LSFT, _______,                                     KC_MCTL, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TAB_L  , LIN_L  , KC_PGDN, LIN_R  , TAB_R  , _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

// Sym (hold Ent): pary [] () {} w kolumnach; ~ + " < > przez Shift z bazy; := -> => "!= nil" jako komba.
    [_SYM] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
     _______, KC_EXLM, KC_LBRC, KC_RBRC, KC_AMPR, KC_PIPE,                                     _______, _______, _______, _______, _______, _______,
     _______, KC_UNDS, KC_LPRN, KC_RPRN, KC_EQL , KC_COLN,                                     _______, OS_RSFT, OS_RGUI, OS_LALT, OS_RCTL, _______,
     _______, KC_SCLN, KC_LCBR, KC_RCBR, KC_BSLS, KC_GRV , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

// Num (hold Bspc): numpad na lewej; @#$%^ = Shift+cyfra stąd; kciuki lewe: . 0 -
    [_NUM] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
     _______, KC_SLSH, KC_7   , KC_8   , KC_9   , KC_ASTR,                                     _______, _______, _______, _______, _______, _______,
     _______, KC_MINS, KC_4   , KC_5   , KC_6   , KC_PLUS,                                     _______, OS_RSFT, OS_RGUI, OS_LALT, OS_RCTL, _______,
     _______, XXXXXXX, KC_1   , KC_2   , KC_3   , KC_EQL , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, KC_DOT , KC_0   , KC_MINS, _______, _______, _______, _______, _______
    ),

// WM (hold Tab): natywne kafelkowanie okien (✦+litera przez App Shortcuts), fullscreen ⌃⌘F,
// Spaces ⌃←/⌃→; J/' = swapper aplikacji (⌘Tab trzymane az do puszczenia warstwy).
    [_WM] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                                     SW_FWD , SPC_L  , WM_FULL, SPC_R  , SW_REV , _______,
     _______, OS_LCTL, OS_LALT, OS_LGUI, OS_LSFT, _______,                                     WM_RET , WM_HLF_L, WM_FILL, WM_HLF_R, XXXXXXX, _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, WM_TOP , WM_BOT , WM_CTR , XXXXXXX, XXXXXXX, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

// Fun (hold Del): F-klawisze na lewej.
    [_FUN] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
     _______, KC_F12 , KC_F7  , KC_F8  , KC_F9  , XXXXXXX,                                     _______, _______, _______, _______, _______, _______,
     _______, KC_F11 , KC_F4  , KC_F5  , KC_F6  , XXXXXXX,                                     _______, OS_RSFT, OS_RGUI, OS_LALT, OS_RCTL, _______,
     _______, KC_F10 , KC_F1  , KC_F2  , KC_F3  , XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

// Media (hold Esc): prawa dłoń = zrzuty/media/jasność; CG⇄ = swap Ctrl/Cmd pod Linuksa.
// Lewa dłoń = podświetlenie RGB: kolumny W/F/P/B to hue/sat/val/speed (górny rząd +, dolny -),
// Q = on/off, Z = następna animacja; 4/5 w rzędzie numerycznym = jasność wyświetlacza TFT.
    [_MEDIA] = LAYOUT(
     _______, _______, _______, _______, BL_DOWN, BL_UP  ,                                     _______, _______, _______, _______, _______, _______,
     _______, RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU,                                     SCR_3  , SCR_4  , SCR_5  , KC_LPAD, CG_TOGG,_______,
     _______, OS_LCTL, OS_LALT, OS_LGUI, OS_LSFT, _______,                                     KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU, _______,
     _______, RM_NEXT, RM_HUED, RM_SATD, RM_VALD, RM_SPDD, _______, _______, _______, _______, KC_MUTE, XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};

// Chordal Hold: jawna mapa rąk ('*' = kciuki neutralne).
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
    'L','L','L','L','L','L',                 'R','R','R','R','R','R',
    'L','L','L','L','L','L',                 'R','R','R','R','R','R',
    'L','L','L','L','L','L',                 'R','R','R','R','R','R',
    'L','L','L','L','L','L','L','L','R','R','R','R','R','R','R','R',
                '*','*','*','*','*','*','*','*','*','*'
);
// clang-format on

// --- Komba operatorowe (te same pozycje fizyczne co w Colemaku, litery QWERTY) ---
enum combo_events {
    CMB_WALRUS,   // E + D  ->  ":= "
    CMB_ARROW,    // R + F  ->  "->"
    CMB_FATARR,   // T + G  ->  "=>"
    CMB_NENIL,    // V + B  ->  "!= nil"
};

const uint16_t PROGMEM cmb_walrus[] = {KC_E, HM_D, COMBO_END};
const uint16_t PROGMEM cmb_arrow[]  = {KC_R, HM_F, COMBO_END};
const uint16_t PROGMEM cmb_fatarr[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM cmb_nenil[]  = {KC_V, KC_B, COMBO_END};

combo_t key_combos[] = {
    [CMB_WALRUS] = COMBO_ACTION(cmb_walrus),
    [CMB_ARROW]  = COMBO_ACTION(cmb_arrow),
    [CMB_FATARR] = COMBO_ACTION(cmb_fatarr),
    [CMB_NENIL]  = COMBO_ACTION(cmb_nenil),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) return;
    switch (combo_index) {
        case CMB_WALRUS: SEND_STRING(":= ");    break;
        case CMB_ARROW:  SEND_STRING("->");     break;
        case CMB_FATARR: SEND_STRING("=>");     break;
        case CMB_NENIL:  SEND_STRING("!= nil"); break;
    }
}

// --- Swapper: ⌘ trzymane w firmware, Tab stukany; puszczenie warstwy WM zatwierdza ---
#include "heatmap.h"

static bool swapper_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    hm_record(record); // zliczanie do heatmapy na wyswietlaczu

    switch (keycode) {
        case SW_FWD:
        case SW_REV:
            if (record->event.pressed) {
                if (!swapper_active) {
                    swapper_active = true;
                    register_code(KC_LGUI);
                }
                register_code16(keycode == SW_REV ? S(KC_TAB) : KC_TAB);
            } else {
                unregister_code16(keycode == SW_REV ? S(KC_TAB) : KC_TAB);
            }
            return false;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (swapper_active && get_highest_layer(state) != _WM) {
        unregister_code(KC_LGUI);
        swapper_active = false;
    }
    return state;
}

// --- Przyciski modułów Halcyon (używane tylko przez moduł enkodera; display/trackpad je ignorują) ---
#if defined(HALCYON_ENABLE)

const uint16_t left_halcyon_buttons[10][5] = {
    [_BASE] = { KC_MUTE, _______, _______, _______, _______ },
};

const uint16_t right_halcyon_buttons[10][5] = {
    [_BASE] = { KC_MUTE, _______, _______, _______, _______ },
};

#endif
