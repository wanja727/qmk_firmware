# wanja727 — unified Keychron customization

Shared customization for **K7 Max / K11 Max / K15 Max / V8 Max** (all ANSI RGB).
Common logic lives here in `users/wanja727`; each board only carries its own layout in
`keyboards/keychron/<board>/.../keymaps/wanja727/keymap.c`.

These keymaps are **compiled firmware** (VIA disabled) — everything is baked in, so the same
behavior is reproduced on every board regardless of VIA's saved config.

## Number row — tap vs hold
- **Tap** = number / symbol (`1 2 3 … - =`)
- **Hold (>200 ms)** = `F1`–`F12`, fired immediately at the threshold (no need to keep holding).

## CapsLock = NAV modifier (hold)
Hold CapsLock and use:

| Key | Action | Key | Action |
|-----|--------|-----|--------|
| `i j k l` | ↑ ← ↓ → | `u` / `o` | Home / End |
| `y` / `h` | PgUp / PgDn | `n` / `m` | Backspace / Delete |
| `tab` | prev browser tab (`Ctrl+Shift+Tab`) | `q` | next browser tab (`Ctrl+Tab`) |
| `e` | close tab (`Ctrl+W`) | `r` | close window (`Alt+F4`) |
| `a` / `s` | mouse Back / Forward (btn4 / btn5) | | |

- **Hold `tab`** (while CapsLock held) = move window to **left** monitor (`Win+Shift+←`)
- **Hold `q`** (while CapsLock held) = move window to **right** monitor (`Win+Shift+→`)
- **`Win` + CapsLock** = the original Caps Lock toggle.

## Fn = mouse + media (hold)
The Keychron media/RGB/Bluetooth layer keeps all its functions, plus:

| Key | Action |
|-----|--------|
| `i j k l` | mouse move ↑ ← ↓ → |
| `u` / `o` | left / right click |
| hold **Space** then `i j k l` | mouse wheel up / left / down / right |
| **Shift** while moving | slow cursor |

Mouse uses constant speed (no QMK acceleration). See `config.h`.

> Windows' own **"Enhance pointer precision"** still applies on top of this — turn it off in
> Windows mouse settings for fully linear movement.

## Building locally
```bash
qmk compile -kb keychron/k7_max/ansi/rgb        -km wanja727
qmk compile -kb keychron/k11_max/ansi_encoder/rgb -km wanja727
qmk compile -kb keychron/k15_max/ansi_encoder/rgb -km wanja727
qmk compile -kb keychron/v8_max/ansi_encoder    -km wanja727
```

## Building in the cloud (GitHub Actions)
Push any change under `users/wanja727/` or a `keymaps/wanja727/` folder. The
`Build wanja727 Keychron firmware` workflow compiles all four boards and uploads the
`.bin`/`.hex` files as artifacts — download them from the workflow run and flash with
Keychron Launcher / QMK Toolbox. You can also trigger it manually from the **Actions** tab.

## Custom keycodes (not editable in VIA)
`NUM_F1..NUM_F12`, `WIN_TAB_PREV`, `WIN_TAB_NEXT`, `MO_NAV` — defined in `wanja727.h`,
starting at `NEW_SAFE_RANGE` to avoid colliding with Keychron's own keycodes.
