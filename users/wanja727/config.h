/* Copyright 2025 @ wanja727
 *
 * Shared config for all keyboards. See readme.md.
 */

#pragma once

// ---------------------------------------------------------------------------
// Mouse keys: constant speed (no QMK acceleration). Holding Shift while moving
// switches to MS_ACL0 (느린 정밀 이동) -- see wanja727.c.
//
// NOTE: Windows' own "Enhance pointer precision" still applies on top of this.
// Turn it off in Windows mouse settings for fully linear movement.
// ---------------------------------------------------------------------------
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL

// Unmodified (default) cursor speed.
#define MK_C_OFFSET_UNMOD 12
#define MK_C_INTERVAL_UNMOD 16
// MS_ACL0 = 느린 속도 (Shift 동시押). 코드 라인/글자 사이 정밀 이동용으로 아주 느리게.
#define MK_C_OFFSET_0 1
#define MK_C_INTERVAL_0 16
// Wheel speed.
#define MK_W_OFFSET_UNMOD 1
#define MK_W_INTERVAL_UNMOD 50
#define MK_W_OFFSET_0 1
#define MK_W_INTERVAL_0 100
