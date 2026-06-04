/* Copyright 2025 @ wanja727
 *
 * Shared config for all keyboards. See readme.md.
 */

#pragma once

// ---------------------------------------------------------------------------
// Mouse keys: 가속 모드(QMK 기본).
//   - 짧게 누르면 한 스텝만 -> 정밀 위치 조정
//   - 계속 누르면 점점 빨라져 -> 넓은 화면을 빠르게 이동
// MOUSE 레이어에서 CapsLock 을 홀드하면 MS_ACL0(느린 고정 속도)로 전환되어
// 더 정밀하게 움직일 수 있다 (wanja727.c 참고).
//
// 대안: 더 부드러운 곡선을 원하면 위 블록 대신 MK_KINETIC_SPEED 를 정의하고
// MOUSEKEY_INITIAL_SPEED / BASE_SPEED / DECELERATED_SPEED / ACCELERATED_SPEED 를 쓴다.
//
// NOTE: Windows 의 "포인터 정밀도 향상"(OS 가속)은 펌웨어가 못 끈다.
// 완전 선형/예측 가능하게 쓰려면 Windows 마우스 설정에서 직접 꺼야 한다.
// ---------------------------------------------------------------------------
#define MOUSEKEY_DELAY 0          // 키를 누른 뒤 이동 시작까지 지연(ms)
#define MOUSEKEY_INTERVAL 16      // 이동 갱신 간격(ms). 낮을수록 부드럽다(≈60fps)
#define MOUSEKEY_MOVE_DELTA 8     // 가속 스텝(클수록 빨리 빨라짐)
#define MOUSEKEY_MAX_SPEED 9      // 최고 속도(클수록 최대 이동량 큼)
#define MOUSEKEY_TIME_TO_MAX 40   // 최고 속도 도달까지 걸리는 간격 수(클수록 완만한 가속)

// 휠도 가속 적용
#define MOUSEKEY_WHEEL_DELAY 0
#define MOUSEKEY_WHEEL_INTERVAL 50
#define MOUSEKEY_WHEEL_MAX_SPEED 6
#define MOUSEKEY_WHEEL_TIME_TO_MAX 30
