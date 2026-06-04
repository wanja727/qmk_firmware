/* Copyright 2025 @ wanja727
 *
 * Shared config for all keyboards. See readme.md.
 */

#pragma once

// ---------------------------------------------------------------------------
// Mouse keys: Kinetic(부드러운 가속) 모드.
//   - 천천히 시작(INITIAL_SPEED)해서 부드럽게 가속(BASE_SPEED 까지)
//   - MOUSE 레이어에서 CapsLock 홀드 = ACL0 = DECELERATED_SPEED(느린 정밀 이동)
//
// 속도는 px/초 개념. 값을 키우면 빠르고, 줄이면 느리다.
//   INITIAL_SPEED      : 키 누른 직후 시작 속도 (낮을수록 초기 느림)
//   BASE_SPEED         : 계속 눌렀을 때 도달하는 최고 속도
//   DECELERATED_SPEED  : Caps 홀드 시 정밀(느린) 속도  <-- 정밀 이동이 빠르면 이 값을 낮춘다
//   ACCELERATED_SPEED  : ACL2(미사용) 빠른 속도
//
// NOTE: Windows 의 포인터 속도 슬라이더와 "포인터 정밀도 향상"(OS 가속)이 위 출력에 곱해진다.
//   - 여전히 빠르거나 들쭉날쭉하면 *Windows 설정 > 마우스 > 추가 마우스 설정 > 포인터 옵션* 에서
//     "포인터 정밀도 향상"을 끄고(선형화), 포인터 속도 슬라이더를 중간으로 두는 것을 권장.
// ---------------------------------------------------------------------------
#define MK_KINETIC_SPEED

#define MOUSEKEY_DELAY 0
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MOVE_DELTA 16

#define MOUSEKEY_INITIAL_SPEED 25      // 초기 속도 (느리게 시작)
#define MOUSEKEY_BASE_SPEED 3000       // 최고 속도
#define MOUSEKEY_DECELERATED_SPEED 100 // Caps 홀드 = 정밀(느린) 속도
#define MOUSEKEY_ACCELERATED_SPEED 4000

// 휠 (kinetic)
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 16
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 32
#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 48
#define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS 8
