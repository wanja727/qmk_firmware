/* Copyright 2025 @ wanja727
 *
 * Mouse key tuning shared by all keyboards.
 * Constant-speed mode (no QMK acceleration). Holding Shift while moving switches to
 * KC_ACL0 (slow) -- see wanja727.c.
 *
 * NOTE: Windows' own "Enhance pointer precision" still applies on top of this. Turn it
 * off in Windows mouse settings if you want fully linear movement.
 */

#pragma once

// Constant speed, no acceleration curve.
#define MK_3_SPEED
// ACL0/1/2 act only while held, then revert to the unmodified speed.
#define MK_MOMENTARY_ACCEL

// Unmodified (default) cursor speed.
#define MK_C_OFFSET_UNMOD 12
#define MK_C_INTERVAL_UNMOD 16

// KC_ACL0 = slow (used when Shift is held while moving).
#define MK_C_OFFSET_0 4
#define MK_C_INTERVAL_0 16

// Wheel speed.
#define MK_W_OFFSET_UNMOD 1
#define MK_W_INTERVAL_UNMOD 50
#define MK_W_OFFSET_0 1
#define MK_W_INTERVAL_0 100
