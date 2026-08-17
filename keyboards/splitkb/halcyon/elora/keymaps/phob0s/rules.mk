# Userspace splitkb z obsługą modułów Halcyon (pliki w users/halcyon_modules)
USER_NAME := halcyon_modules

CAPS_WORD_ENABLE  = yes
COMBO_ENABLE      = yes
REPEAT_KEY_ENABLE = yes
WPM_ENABLE        = yes

# Heatmapa: zliczanie w obu połowach (master śledzi, wysyła do slave'a)
SRC += heatmap.c

# Rysowanie tylko w firmware z wyświetlaczem
ifdef HLC_TFT_DISPLAY
    SRC += display.c \
           graphics/apple.qgf.c \
           graphics/wpm_font.qff.c \
           graphics/thintel15.qff.c
endif
