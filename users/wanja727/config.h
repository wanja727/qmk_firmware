/* Copyright 2025 @ wanja727
 *
 * Shared config for all keyboards. See readme.md.
 */

#pragma once

// Space = LT(NAV, KC_SPC) 안정화
//  - 탭 직후 다시 눌러 홀드해도 "탭 반복"이 아니라 정상 홀드(NAV)로 처리
#define QUICK_TAP_TERM 0

// ---------------------------------------------------------------------------
// Mouse keys: Kinetic(부드러운 가속) 모드.
//   - 천천히 시작(INITIAL_SPEED)해서 부드럽게 가속(BASE_SPEED 까지)
//   - MS_ACL0(고정 저속) 매핑은 제거됨. MOUSE 레이어 Shift 는 이제 MS_OFF_SFT(=MOUSE OFF / 일반 Shift).
//     DECELERATED_SPEED 값은 kinetic 알고리즘용으로 남겨두지만 더 이상 키에 바인딩하지 않는다.
//
// 아래 값은 모두 **QMK kinetic 기본값**(원작자 의도 기준점). 여기서부터 조정한다.
//
// 튜닝 방향:
//   INITIAL_SPEED      ↓ 초기 더 느리게(정밀) / ↑ 처음부터 빠르게
//   BASE_SPEED         ↑ 최고 속도 빠르게(넓은 화면) / ↓ 느리게
//   INTERVAL           ↓ 더 부드럽고 빠릿(리포트 간격↓). 무선에선 '이동 중에만' 트래픽↑
//   DELAY              ↓ 키 누른 직후 반응 빠르게(0=즉시)
//
// 무선 배터리: INTERVAL/DELAY 는 '마우스 이동 중'에만 영향(idle 무관). 배터리 주영향은
//   RGB/연결유지이므로 반응속도는 빠릿하게 둬도 손해가 거의 없다.
//
// NOTE: QMK 출력에 Windows 포인터 속도/"포인터 정밀도 향상"(OS 가속)이 곱해진다.
//   일정/정밀하게 쓰려면 Windows 마우스 설정에서 "포인터 정밀도 향상"을 끄는 것을 권장.
// ---------------------------------------------------------------------------
#define MK_KINETIC_SPEED

#define MOUSEKEY_DELAY 0               // 0 = 누른 즉시 반응 (QMK 기본 5)
#define MOUSEKEY_INTERVAL 10           // QMK 기본 10 (≈100 reports/s)
#define MOUSEKEY_MOVE_DELTA 16         // QMK 기본 16

#define MOUSEKEY_INITIAL_SPEED 100     // 초기 속도 (QMK 기본 100)
#define MOUSEKEY_BASE_SPEED 1000       // 가속 시 도달하는 최고 속도
#define MOUSEKEY_DECELERATED_SPEED 100 // ACL0 (현재 키에 미바인딩)
#define MOUSEKEY_ACCELERATED_SPEED 3000// ACL2 (현재 미바인딩)

// 휠 (kinetic) — 모두 QMK 기본값
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 16
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 32
#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 48
#define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS 8
