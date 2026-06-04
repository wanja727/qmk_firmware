# wanja727 — Keychron 통합 커스텀 (K7 / K11 / K15 / V8 Max)

4개 Keychron 키보드(K7 Max ANSI RGB, K11 Max ANSI RGB, K15 Max ANSI RGB, V8 Max ANSI)의
키맵과 동작을 하나로 통일한 설정입니다. 공통 로직은 `users/wanja727`에 모여 있고, 각 보드는
자기 레이아웃 배열만 `keyboards/keychron/<board>/.../keymaps/wanja727/keymap.c`에 가집니다.

---

## 1. 레이어 구조

| 레이어 | 진입 방법 | 설명 |
|--------|-----------|------|
| **BASE** (MAC/WIN) | 기본 | 기존 타이핑 레이어 그대로 유지. 숫자열은 tap=숫자 / hold=F1~F12. |
| **FN2** (MAC/WIN) | FN2 키 hold | **기존 Keychron FN1(미디어/RGB/BT) 레이어를 이름만 FN2로 바꾼 것.** 밝기/볼륨/미디어/블루투스(BT_HST)/RGB/NKRO 등 원래 기능을 그대로 보존. |
| **NAV** | CapsLock hold | 방향/편집/브라우저/창/멀티모니터/한영 전환. |
| **MOUSE** | FN1 키 hold | 마우스 이동/버튼/휠/브라우저/절대좌표 커서 이동. |

> **중요(FN1/FN2 재배치):** 기존 FN1(미디어) 레이어는 **FN2로 이름이 바뀌었고**, 그 레이어로
> 들어가는 키를 "FN2 키"라고 부릅니다. 새로 생긴 "FN1 키"는 **MOUSE 레이어 진입 전용**입니다.
>
> 보드별 물리 키 매핑:
> - **K7 / K11 / V8 Max** : 오른쪽 두 개의 Fn/모디파이어 키 중 **주 Fn 키 = FN1(MOUSE)**, **두 번째 키 = FN2(미디어)**.
> - **K15 Max** : Fn 키가 1개뿐이라 **Fn = FN1(MOUSE)**, **오른쪽 Ctrl = FN2(미디어)** 로 매핑.

MAC/WIN BASE는 물리 OS 스위치로 전환되며 기존과 동일하게 동작합니다. (레이어 인덱스 보존)

---

## 2. CapsLock / NAV 레이어

CapsLock을 **누르고 있는 동안** NAV 레이어가 활성화됩니다.
기존 CapsLock(대문자 고정) 기능은 **Win + CapsLock** 으로 사용합니다. (custom 처리)

| 키 (Caps + …) | 동작 | 키 (Caps + …) | 동작 |
|---|---|---|---|
| `I` / `J` / `K` / `L` | ↑ / ← / ↓ / → | `U` / `O` | Home / End |
| `N` / `M` | Backspace / Delete | `Space` | **한/영 전환** |
| `Q` | 브라우저 이전 탭 (Ctrl+Shift+Tab) | `W` | 브라우저 다음 탭 (Ctrl+Tab) |
| `E` | 탭 닫기 (Ctrl+W) | `R` | 창 닫기 (Alt+F4) |
| `Tab` | **작업 전환 (Alt+Tab)** | `Shift`+`Tab` | 역방향 작업 전환 (Alt+Shift+Tab) |
| `A` | 활성 창을 **왼쪽 모니터**로 (Win+Shift+←) | `S` | 활성 창을 **오른쪽 모니터**로 (Win+Shift+→) |

---

## 3. FN1 / MOUSE 레이어

FN1 키를 **누르고 있는 동안** MOUSE 레이어가 활성화됩니다.

| 키 (FN1 + …) | 동작 | 키 (FN1 + …) | 동작 |
|---|---|---|---|
| `I` / `J` / `K` / `L` | 마우스 ↑ / ← / ↓ / → | `D` / `F` | 왼쪽 클릭 / 오른쪽 클릭 (BTN1 / BTN2) |
| `A` / `S` | 뒤로 / 앞으로 (BTN4 / BTN5) | `;` / `H` | 휠 위 / 휠 아래 |
| `Y` / `P` | 휠 왼쪽 / 휠 오른쪽 | `Shift` | **느린 커서 이동** |
| `Q` / `W` / `E` / `R` | NAV와 동일 (이전탭/다음탭/탭닫기/창닫기) | `U` / `O` | **왼쪽/오른쪽 화면 중앙으로 커서 이동** |

---

## 4. FN2 = 기존 FN1(미디어) 레이어

기존 Keychron의 FN(미디어/RGB/BT) 기능은 사라진 게 아니라 **FN2 레이어로 이름만 바뀌었습니다.**
FN2 키를 누르면 기존과 똑같이 밝기, 볼륨, 미디어 재생, 블루투스 페어링(BT_HST1~3, P2P4G),
RGB 제어, NKRO 토글, 배터리 표시 등을 사용할 수 있습니다. (보드별 원본 배치 그대로)

---

## 5. 한/영 전환 (KC_LNG1 / KC_RALT)

`Caps + Space` = 한/영 전환. 1순위로 **`KC_LNG1`** 을 사용합니다.

Windows 한글 입력 환경에 따라 `KC_LNG1`이 동작하지 않을 수 있습니다. 그럴 때는
`users/wanja727/wanja727.h`의 아래 한 줄만 바꾸고 다시 빌드하면 됩니다.

```c
#define HANGEUL_KEYCODE KC_LNG1   // 기본
// #define HANGEUL_KEYCODE KC_RALT // 한/영 키를 우측 Alt로 쓰는 환경
```

> 실제 한글 IME 환경에서 동작 확인이 필요합니다. (최신 Windows 한국어 IME는 보통 KC_LNG1 인식,
> 일부 구형/서드파티 IME는 우측 Alt를 사용)

---

## 6. Alt+Tab 작업 전환 (ALT_TAB) 구현과 한계

`Caps + Tab` 은 단순 `LALT(KC_TAB)` 이 아니라 **Alt를 누른 상태로 유지하는 custom `ALT_TAB`** 으로
구현했습니다. 그래서 작업 전환 UI가 떠 있는 상태에서 Tab을 연타하며 창을 넘길 수 있습니다.

- 동작: 첫 입력에서 `Alt`를 누른 채로 `Tab`을 보냄 → 일정 시간(`ALT_TAB_TIMEOUT`, 기본 600ms)
  동안 추가 입력이 없으면 자동으로 `Alt`를 뗌.
- `Caps + Shift + Tab` 은 Shift가 함께 눌린 상태로 `Tab`이 가므로 **역방향(Alt+Shift+Tab)** 으로 동작.
- **한계:** Alt가 떨어지는 기준이 "마지막 입력 후 타임아웃"입니다. 매우 천천히 넘기면 타임아웃으로
  창 선택이 확정될 수 있습니다. 타임아웃은 `wanja727.c`의 `ALT_TAB_TIMEOUT`으로 조정 가능합니다.

---

## 7. 멀티 모니터 활성 창 이동

- `Caps + A` = `Win + Shift + ←` (현재 활성 창을 왼쪽 모니터로 이동)
- `Caps + S` = `Win + Shift + →` (현재 활성 창을 오른쪽 모니터로 이동)

Tab은 작업 전환에 쓰고, 창 이동은 A/S로 분리했습니다.

---

## 8. 절대 좌표 커서 이동 (Digitizer) — 한계

`FN1 + U` / `FN1 + O` 로 커서를 **왼쪽/오른쪽 화면 중앙**으로 순간 이동합니다.
QMK **Digitizer**(절대 좌표 HID) 기능을 사용합니다. 좌표는 `users/wanja727/config.h`에서 조정합니다.

```c
#define CURSOR_LEFT_X  0.25f   // 왼쪽 화면 중앙 X (전체 가상 데스크톱 기준 0.0~1.0)
#define CURSOR_LEFT_Y  0.50f
#define CURSOR_RIGHT_X 0.75f   // 오른쪽 화면 중앙 X
#define CURSOR_RIGHT_Y 0.50f
```

**한계 / 주의:**
- 기본값은 **좌우 동일 해상도 + 좌우로 나란히 배치 + 두 화면을 합친 가상 데스크톱** 기준입니다.
  모니터 해상도/배치/주 모니터 위치/세로 배치 등에서는 값을 바꿔야 정확히 중앙으로 갑니다.
- Windows는 Digitizer를 **펜/터치처럼** 인식합니다. 절대 위치로 포인터가 "순간 이동"하며, 이후
  일반 상대 마우스 입력과 섞일 때 약간 어색할 수 있습니다.
- **무선(BT/2.4GHz) 연결에서는 Digitizer 리포트가 전달되지 않을 수 있습니다. USB 유선 연결에서
  먼저 확인하세요.** 환경상 동작하지 않으면, 같은 위치로 보내는 마우스 매크로나 OS 단축키(예:
  PowerToys, 창 스냅) 등 대체 수단을 고려하세요.

---

## 9. 마우스 가속 제거 / 느린 이동

`users/wanja727/config.h`에서 QMK 자체 가속을 끄고 상수 속도로 설정했습니다.

```c
#define MK_3_SPEED          // 가속 없는 상수 속도 모드
#define MK_MOMENTARY_ACCEL  // 속도 키는 누르는 동안만 적용
```

- `FN1 + Shift` 를 누르면 `MS_ACL0`(느린 속도)로 전환되어 정밀 이동이 됩니다.
- **OS 가속과의 구분:** 위 설정은 **QMK 펌웨어 자체 가속**만 제거합니다. Windows의
  **"포인터 정밀도 향상"** 은 OS 레벨이라 펌웨어가 끄지 못합니다. 완전히 선형으로 쓰려면
  *Windows 설정 > 마우스 > 추가 마우스 설정 > 포인터 옵션* 에서 직접 꺼야 합니다.

---

## 10. VIA 사용 시 주의 (custom keycode 표시 제한)

이 keymap은 `VIA_ENABLE = yes` 로 빌드되어 VIA / Keychron Launcher에서 인식·수정할 수 있습니다.
레이어 수가 늘어나서 각 보드의 `info.json` `dynamic_keymap.layer_count` 를 **6** 으로 올렸습니다
(EEPROM `logical_size` 내에 들어감).

**custom keycode 한계:**
- `NUM_F1~12`, `MO_NAV`, `HANGEUL`, `ALT_TAB`, `CUR_LSCR`, `CUR_RSCR` 는 펌웨어 내부 custom
  keycode 입니다. **VIA UI에는 이름 없이 raw 코드(또는 "Any")로 보일 수 있고, 직접 선택/편집이
  어렵습니다.** 이 키들의 동작은 펌웨어에 고정되어 있으니 VIA에서 바꾸지 말고 그대로 두세요.
- Keychron Launcher가 내장 정의(기존 레이어 수 기준)를 쓰는 경우, 추가된 NAV/MOUSE 레이어가
  UI에 안 보일 수 있습니다. 이때도 펌웨어 기본 동작은 정상입니다.
- 일반 키(알파벳/숫자/미디어 등)는 VIA에서 자유롭게 재매핑 가능합니다.

---

## 빌드

```bash
qmk compile -kb keychron/k7_max/ansi/rgb         -km wanja727
qmk compile -kb keychron/k11_max/ansi_encoder/rgb -km wanja727
qmk compile -kb keychron/k15_max/ansi_encoder/rgb -km wanja727
qmk compile -kb keychron/v8_max/ansi_encoder     -km wanja727
```

GitHub Actions(`.github/workflows/build-wanja727.yml`)에 push하면 4개 보드를 자동 빌드해
`.bin`/`.hex` 를 artifact로 올립니다.

---

## 검증 체크리스트

- [ ] 4개 보드 컴파일 성공
- [ ] VIA / Keychron Launcher 인식
- [ ] BASE 기존 키맵 유지 (타이핑 정상)
- [ ] FN2 키로 기존 미디어/RGB/BT 기능 동작
- [ ] Caps + I/J/K/L 방향키
- [ ] Caps + Space 한/영 전환
- [ ] Caps + Q/W/E/R 브라우저 제어
- [ ] Caps + Tab 작업 전환 / Caps + Shift + Tab 역방향
- [ ] Caps + A/S 모니터 간 활성 창 이동
- [ ] FN1 + I/J/K/L 마우스 이동, D/F 클릭, A/S 뒤로/앞으로
- [ ] FN1 + ;/H/Y/P 휠
- [ ] FN1 + Shift 느린 이동
- [ ] FN1 + U/O 화면 중앙 커서 이동 (USB 연결에서 우선 확인)
