# wanja727 — Keychron 통합 커스텀 (K7 / K11 / K15 / V8 Max)

4개 Keychron 키보드의 키맵을 하나로 통일한 설정. 공통 로직은 `users/wanja727`, 보드별 레이아웃은
각 `keyboards/keychron/<board>/.../keymaps/wanja727/keymap.c`. (VIA 지원)

설계 목표: **양손을 홈로우에 둔 채 NAV/MOUSE 를 쓰는 것.** MOUSE 는 toggle 이 아니라
**명시적 ON / OFF**(진입키=항상 ON, 해제키=항상 OFF) 구조.

---

## 1. 레이어 구조

| 레이어 | 진입 | 설명 |
|--------|------|------|
| **BASE** | 기본 | 타이핑. 숫자열 tap=숫자/hold=F1~F12. 좌Shift tap=한/영. Caps tap=MOUSE ON. |
| **FN1** (media) | Fn 키 hold | 기존 Keychron 미디어/RGB/BT/밝기/볼륨/BT_HST/NKRO (원본 유지). |
| **NAV** | **CapsLock hold** | 방향/편집/브라우저/창/모니터/휠. |
| **MOUSE** | **Caps tap = ON** / **Space·Esc = OFF** | 마우스 이동/버튼/휠/브라우저. Shift=빠른 이동. |

- **MOUSE 는 toggle 이 아님.** Caps 를 **탭**하면 항상 ON(`layer_on`), 이미 켜져 있어도 꺼지지 않음.
  끄는 건 MOUSE 안의 **Space** 또는 **Esc**(항상 OFF, `layer_off`).
- Fn 키 = 미디어. (K7/K11/V8 오른쪽 두 Fn 모두 미디어, K15 는 Fn = 미디어 / 오른쪽 Ctrl 은 Right Ctrl)

---

## 2. CapsLock (tap = MOUSE ON, hold = NAV)

- **Caps 탭 = MOUSE 레이어 ON**
- **Caps 홀드(또는 다른 키와 조합) = NAV 레이어**
- **Win + Caps = 기존 CapsLock**

> 다른 키와 함께 눌리면 즉시 NAV(홀드)로 확정, 아무 키 없이 짧게 떼면 MOUSE ON. (`TAPPING_TERM` 200ms)

### NAV 매핑 (Caps + …)

| 키 | 동작 | 키 | 동작 |
|---|---|---|---|
| `W` | 이전 탭 (Ctrl+Shift+Tab) | `E` | 다음 탭 (Ctrl+Tab) |
| `R` | 탭 닫기 (Ctrl+W) | `T` | 창 닫기 (Alt+F4) |
| `S` / `G` | 마우스 뒤로 / 앞으로 (BTN4 / BTN5) | `D` / `F` | 활성 창 왼쪽/오른쪽 모니터 이동 (Win+Shift+←/→) |
| `I`/`J`/`K`/`L` | ↑ / ← / ↓ / → | `U` / `O` | Home / End |
| `N` / `M` | Backspace / Delete | `H` / `;` / `Y` / `P` | 휠 업/다운/좌/우 |

---

## 3. MOUSE 레이어 (Caps tap = ON / Space·Esc = OFF)

- 진입: **Caps 탭** (항상 ON)
- 해제: MOUSE 안에서 **Space** 또는 **Esc** (항상 OFF). Space 는 실제 입력이 아니라 MOUSE OFF 동작.
  (MOUSE 꺼진 일반 상태에서는 Space = 정상 Space)

| 키 | 동작 | 키 | 동작 |
|---|---|---|---|
| `I`/`J`/`K`/`L` | 마우스 ↑ / ← / ↓ / → | `D` / `F` | 왼쪽 / 오른쪽 클릭 (BTN1 / BTN2) |
| `H` / `;` / `Y` / `P` | 휠 업/다운/좌/우 | **`Shift` (hold)** | **고정 속도 이동 (MS_ACL0)** |
| `Space` / `Esc` | MOUSE OFF | **`Caps` + …** | NAV 사용 (뒤로/앞으로·브라우저·모니터) |

> - MOUSE 에서 Shift 는 일반 Shift 가 아니라 **고정 속도(MS_ACL0)** 전용입니다(Shift 입력 안 나감).
> - **MOUSE 사용 중 Caps 를 누르고 있으면 NAV 전체가 덮어쓴다.** 즉 `Caps+ijkl`=방향키,
>   `Caps+D/F`=모니터 이동, `Caps+W/E/R/T`=브라우저, `Caps+S/G`=뒤로/앞으로 등 NAV 기능을
>   그대로 사용. Caps 를 떼면 다시 MOUSE. (이를 위해 **레이어 순서를 NAV > MOUSE** 로 둠 — ijkl·d/f
>   처럼 MOUSE 에도 매핑된 키까지 NAV 가 덮어쓰려면 NAV 가 위에 있어야 함.)

---

## 4. FN1 = 기존 Keychron 미디어 레이어

Fn 키를 누르면 기존과 똑같이 밝기/볼륨/미디어/블루투스(BT_HST1~3, P2P4G)/RGB/NKRO/배터리 등을
사용. (보드별 원본 배치 그대로, 레이어명만 FN1)

---

## 5. 한/영 전환 = 좌 Shift 탭

- **왼쪽 Shift 탭 = 한/영 전환**, **왼쪽 Shift 홀드 = 일반 Shift** (`LSFT_T(HANGEUL_KEYCODE)`).
- Shift 를 누른 채 다른 키를 누르면 즉시 Shift(hold)로 확정되어, Shift+키 입력이 한/영으로
  오판되지 않습니다 (`get_hold_on_other_key_press`).
- 한/영 keycode 는 1순위 `KC_LNG1`. 안 되면 `users/wanja727/wanja727.h` 에서 변경:

```c
#define HANGEUL_KEYCODE KC_LNG1   // 기본
// #define HANGEUL_KEYCODE KC_RALT // 우측 Alt 를 한/영으로 쓰는 환경
```

---

## 6. 브라우저 / 뒤로앞으로 / 모니터 / 휠 (NAV 기준)

- 브라우저: `Caps + W/E/R/T` = 이전탭/다음탭/탭닫기/창닫기
- 마우스 뒤로/앞으로: `Caps + S` / `Caps + G` (BTN4 / BTN5)
- 모니터 창 이동: `Caps + D` = 왼쪽, `Caps + F` = 오른쪽
- 휠: `H`=업, `;`=다운, `Y`=왼쪽, `P`=오른쪽 (NAV·MOUSE 동일 위치)

> MOUSE 레이어에서도 **Caps 를 누르면** 위 NAV 기능을 그대로 쓸 수 있습니다(폴스루). 그래서
> 알파벳/홈로우 위치를 유지한 채 작업할 수 있습니다.

---

## 7. 마우스 속도 (Kinetic 가속)

- **Kinetic(부드러운 가속) 모드.** 살짝 누르면 한 스텝(정밀), 계속 누르면 가속(최고 `BASE_SPEED`).
- MOUSE 에서 **Shift 홀드 = `MS_ACL0` 고정 속도**(`DECELERATED_SPEED`). base 보다 느린 일정 속도라
  정밀/안정 이동에 사용. (base 보다 낮은 값이므로 가속이 아니라 감속 의미 → ACL0 사용)
- `users/wanja727/config.h` 현재값: `BASE_SPEED 2000`, `DECELERATED_SPEED 800`(Shift 고정속도).
- **OS 가속 구분:** Windows 포인터 속도/"포인터 정밀도 향상"이 곱해집니다. 일정/정밀하게 쓰려면
  *Windows 설정 > 마우스 > 포인터 옵션* 에서 "포인터 정밀도 향상"을 끄는 것을 권장.

---

## 8. 숫자열 tap/hold

- **탭 = 숫자/기호**, **길게(>200ms) = F1~F12** (임계값에서 즉시 발사).

---

## 9. 커스텀 키코드 / 코어 패치

- custom keycode: `NUM_F1~12`(숫자/F열), `MO_NAV`(Caps), `MS_OFF`(MOUSE 끄기). VIA UI 에는 raw 로
  보이며 직접 편집은 제한적 — 동작은 펌웨어에 고정.
- **코어 패치** `quantum/mousekey.c`: kinetic `mouse_timer` 를 이동/휠 키에서만 시작하도록 수정
  (마우스 버튼을 오래 누른 뒤 이동 시 커서가 튀는 버그 수정). `upstream` 머지 시 충돌 나면 재적용.

---

## 10. VIA

`VIA_ENABLE = yes`. 레이어 6개를 위해 각 보드 `info.json` `dynamic_keymap.layer_count = 6`.
Launcher 가 내장 정의(레이어 적은)를 쓰면 NAV/MOUSE 가 UI 에 안 보일 수 있으나 펌웨어 동작은 정상.

---

## 빌드

```bash
qmk compile -kb keychron/k7_max/ansi/rgb          -km wanja727
qmk compile -kb keychron/k11_max/ansi_encoder/rgb -km wanja727
qmk compile -kb keychron/k15_max/ansi_encoder/rgb -km wanja727
qmk compile -kb keychron/v8_max/ansi_encoder      -km wanja727
```

push 하면 GitHub Actions 가 4개 보드를 빌드해 `.bin`/`.hex` artifact 로 올립니다.

---

## 검증 체크리스트

- [ ] 4개 보드 컴파일 / VIA 인식 / BASE 타이핑 정상
- [ ] 좌Shift 탭 = 한/영, 좌Shift+키 = 일반 Shift
- [ ] Caps 탭 = MOUSE ON (이미 켜져 있어도 유지), Caps 홀드 = NAV, Win+Caps = CapsLock
- [ ] MOUSE 에서 Space / Esc = MOUSE OFF, 일반 상태 Space = 정상 Space
- [ ] Caps + I/J/K/L 방향, U/O Home·End, N/M Bksp·Del
- [ ] Caps + W/E/R/T 브라우저, S/G 뒤로·앞으로, D/F 모니터 이동
- [ ] NAV·MOUSE 휠 H/;/Y/P (업/다운/좌/우)
- [ ] MOUSE I/J/K/L 이동, D/F 클릭, Shift 홀드 = 고정 속도(800)
- [ ] MOUSE 중 Alt+Tab 정상 동작 (Tab 제거 후), MOUSE 중 Caps+W 등 NAV 폴스루
- [ ] Fn 키 = 기존 미디어/RGB/BT
