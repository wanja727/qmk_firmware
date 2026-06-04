/* Copyright 2025 @ wanja727
 *
 * Shared config for all keyboards. See readme.md.
 */

#pragma once

// ---------------------------------------------------------------------------
// Mouse keys: constant speed (no QMK acceleration). Holding Shift while moving
// switches to MS_ACL0 (slow) -- see wanja727.c.
//
// NOTE: Windows' own "Enhance pointer precision" still applies on top of this.
// Turn it off in Windows mouse settings for fully linear movement.
// ---------------------------------------------------------------------------
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL

// Unmodified (default) cursor speed.
#define MK_C_OFFSET_UNMOD 12
#define MK_C_INTERVAL_UNMOD 16
// MS_ACL0 = slow (used when Shift is held while moving).
#define MK_C_OFFSET_0 4
#define MK_C_INTERVAL_0 16
// Wheel speed.
#define MK_W_OFFSET_UNMOD 1
#define MK_W_INTERVAL_UNMOD 50
#define MK_W_OFFSET_0 1
#define MK_W_INTERVAL_0 100

// ---------------------------------------------------------------------------
// Absolute cursor jump targets (Digitizer), in 0.0~1.0 of the virtual desktop.
// 좌우 동일 해상도 + 좌우 배치 기준의 기본값. 모니터 해상도/배치/주모니터 위치에
// 따라 값을 조정한다. (readme.md 참고)
// ---------------------------------------------------------------------------
#define CURSOR_LEFT_X 0.25f
#define CURSOR_LEFT_Y 0.50f
#define CURSOR_RIGHT_X 0.75f
#define CURSOR_RIGHT_Y 0.50f
