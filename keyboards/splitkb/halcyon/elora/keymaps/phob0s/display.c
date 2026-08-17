// Własny ekran: logo Apple / heatmapa klawiatury / WPM jako liczba.
// Zastępuje fabryczny ekran statusu (warstwy, capslock itd.) - hook zwraca false.
// Rysujemy tylko małe fragmenty (dirty cells / zmieniona liczba), więc zero wpływu na pisanie.
#include QMK_KEYBOARD_H
#include "hlc_tft_display/hlc_tft_display.h"
#include <stdio.h>

#include "heatmap.h"
#include "heatmap_layout.h"
#include "graphics/apple.qgf.h"
#include "graphics/wpm_font.qff.h"
#include "graphics/thintel15.qff.h"

// Układ pionowy ekranu 135x240
#define APPLE_Y 12
#define HM_TOP 104
#define HM_LEFT ((LCD_WIDTH - HM_BLOCK_W) / 2)
#define WPM_Y 168
#define WPM_NUM_RIGHT 127
#define WPM_CLEAR_X0 36
#define LABEL_X 8

static painter_image_handle_t apple_logo;
static painter_font_handle_t wpm_font;
static painter_font_handle_t thintel;

static uint8_t hm_shown[MATRIX_ROWS][HM_MATRIX_COLS];

bool module_post_init_user(void) {
    apple_logo = qp_load_image_mem(gfx_apple);
    wpm_font   = qp_load_font_mem(font_wpm_font);
    thintel    = qp_load_font_mem(font_thintel15);
    return true;
}

// Zimny klawisz = ledwo widoczny granatowy; rosnące ciepło = niebieski -> czerwony, coraz jaśniej.
static void hm_cell_color(uint8_t h, uint8_t *hue, uint8_t *sat, uint8_t *val) {
    if (h == 0) {
        *hue = 170; *sat = 220; *val = 34;
        return;
    }
    *hue = 170 - ((uint16_t)h * 170) / 255;
    *sat = 255;
    *val = 90 + ((uint16_t)h * 165) / 255;
}

static void draw_heatmap(void) {
    for (uint8_t i = 0; i < HM_KEY_COUNT; i++) {
        uint8_t r = hm_keys[i].row;
        uint8_t c = hm_keys[i].col;
        uint8_t q = hm_heat[r][c] & 0xF8; // 32 poziomy - mniej przerysowań
        if (q != hm_shown[r][c]) {
            uint8_t hue, sat, val;
            hm_cell_color(q, &hue, &sat, &val);
            uint16_t x = HM_LEFT + hm_keys[i].x;
            uint16_t y = HM_TOP + hm_keys[i].y;
            qp_rect(lcd_surface, x, y, x + HM_CELL - 1, y + HM_CELL - 1, hue, sat, val, true);
            hm_shown[r][c] = q;
        }
    }
}

static void draw_wpm(void) {
    static uint8_t last_shown = 255;
    uint8_t wpm = get_current_wpm();
    if (wpm == last_shown) {
        return;
    }
    last_shown = wpm;

    char buf[4];
    snprintf(buf, sizeof(buf), "%u", wpm);
    int16_t width = qp_textwidth(wpm_font, buf);

    // Kolor liczby spójny z heatmapą: bezbarwna przy 0, niebieski -> czerwony do 100+ wpm
    uint8_t wc  = wpm > 100 ? 100 : wpm;
    uint8_t hue = 170 - ((uint16_t)wc * 170) / 100;
    uint8_t sat = ((uint16_t)wc * 255) / 100;

    qp_rect(lcd_surface, WPM_CLEAR_X0, WPM_Y, LCD_WIDTH - 1, WPM_Y + wpm_font->line_height, 0, 0, 0, true);
    qp_drawtext_recolor(lcd_surface, WPM_NUM_RIGHT - width, WPM_Y, wpm_font, buf, hue, sat, 255, 0, 0, 0);
}

bool display_module_housekeeping_task_user(bool second_display) {
    if (second_display) {
        return true; // nie występuje przy zestawie display+trackpad; zostawiamy fabryczne Game of Life
    }

    static bool ui_initialized = false;
    if (!ui_initialized) {
        // Tło jest już czarne po inicie modułu; logo i podpis rysujemy raz
        qp_drawimage_recolor(lcd_surface, (LCD_WIDTH - apple_logo->width) / 2, APPLE_Y, apple_logo, 0, 0, 255, 0, 0, 0);
        qp_drawtext_recolor(lcd_surface, LABEL_X, WPM_Y + wpm_font->line_height - thintel->line_height - 4, thintel, "wpm", 0, 0, 110, 0, 0, 0);
        memset(hm_shown, 1, sizeof(hm_shown)); // 1 nie jest wielokrotnością 8 -> wymusza pierwsze rysowanie wszystkich klawiszy
        ui_initialized = true;
    }

    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) >= 100) {
        last_draw = timer_read32();
        draw_heatmap();
        draw_wpm();
    }

    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
    qp_flush(lcd);

    return false; // pomija fabryczny ekran statusu
}
