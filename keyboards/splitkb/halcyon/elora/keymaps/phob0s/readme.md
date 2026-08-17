# phob0s — Halcyon Elora rev2

Colemak-DH, mac-first, CAGS home row mods (Ctrl-Alt-Gui-Shift from pinky: A R S T / N E I O), Chordal Hold + Flow Tap ("timeless HRM"), Caps Word, Repeat Key, one-shot mods on layers, operator combos. `'` sits on the top-row pinky (where standard Colemak puts `;`); `;` lives on `_SYM` only.

Uses the current `users/halcyon_modules` integration (standard `LAYOUT` macro, no legacy matrix overrides).

## Layers

| # | Layer | Access | Contents |
|---|-------|--------|----------|
| 0 | `_BASE` | default | Colemak-DH, HRM; outer cols: `` ` ``/CapsWord/⇧/⌘ · PgUp/PgDn/⇧/lock(⌃⌘Q); near thumbs: ⌘Z ⌘⇧Z · LMB RMB; thumbs: Rep/Hyper/Esc/Spc/Tab · Ent/Bspc/Del/⌥R/⌘⇥ |
| 1 | `_NAV` | hold Space | arrows on home, word/line jumps (⌥/⌘), tabs, Mission Control |
| 2 | `_SYM` | hold Enter | bracket pairs in columns on left hand |
| 3 | `_NUM` | hold Backspace | numpad on left hand, `. 0 -` on left thumbs |
| 4 | `_WM` | hold Tab | native macOS window tiling (✦-letter chords via App Shortcuts), Spaces, one-key app swapper on `J`/`'` |
| 5 | `_FUN` | hold Del | F1–F12 on left hand |
| 6 | `_MEDIA` | hold Esc | right: screenshots, media, brightness, `CG_TOGG`; left: RGB underglow (W/F/P/B columns = hue/sat/val/speed ±, Q = toggle, Z = next animation), `4`/`5` = TFT backlight |

Combos (left hand): `F+S → ":= "`, `P+T → "->"`, `B+G → "=>"`, `D+V → "!= nil"`.

## macOS setup (vanilla, no Raycast)

Window tiling uses ✦ (Hyper) + letter chords bound once in System Settings → Keyboard → Keyboard Shortcuts → App Shortcuts → All Applications, targeting the native menu items by full path (titles follow the system language): `Window->Move & Resize->Left` = ✦H, `Right` = ✦L, `Top` = ✦T, `Bottom` = ✦B, `Fill` = ✦F, `Center` = ✦C, `Return to Previous Size` = ✦R. Fullscreen is native `⌃⌘F`. App switching: right outer thumb taps `⌘Tab` (last-app toggle); on `_WM`, `J`/`'` are a Callum-style swapper (⌘ held by firmware, released when the layer is released).

## Modules

Left half: TFT display. Right half: Cirque trackpad (tap-to-click, scroll and glide gestures enabled by the module config). The `left/right_halcyon_buttons` arrays only matter if an encoder module is ever attached.

## Display

The stock status screen is replaced (`display.c`) with a custom vertical layout:

1. **Apple logo** — white, static, drawn once (`graphics/apple.qgf`).
2. **Typing heatmap** — mini Elora rendered from the real layout geometry (`heatmap_layout.h`, generated from `keyboard.json`); keys glow blue → red with use and cool off over ~7 s. Heat is tracked on the USB master and synced to the other half (`heatmap.c`, custom split RPC), so it works whichever side has the cable.
3. **WPM** — large number, right-aligned; tint follows the same blue → red scale (white when idle). Built-in QMK WPM counter with `SPLIT_WPM_ENABLE`.

Everything redraws only changed cells/digits, so the display never affects typing latency. Regenerate the layout table or assets with the QMK painter CLI if the layout or artwork changes.

## Build

One firmware per module — flash each half with its own file:

```bash
qmk compile -kb splitkb/halcyon/elora/rev2 -km phob0s -e HLC_TFT_DISPLAY=1     -e TARGET=splitkb_halcyon_elora_rev2_phob0s_display
qmk compile -kb splitkb/halcyon/elora/rev2 -km phob0s -e HLC_CIRQUE_TRACKPAD=1 -e TARGET=splitkb_halcyon_elora_rev2_phob0s_trackpad
```

Flash: double-tap reset on a half → it mounts as a USB drive → drag the matching `.uf2` onto it (display file to the left half, trackpad file to the right half).
