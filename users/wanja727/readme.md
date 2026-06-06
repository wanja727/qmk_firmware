# wanja727 — Keychron 통합 커스텀 (K7 / K11 / K15 / V8 Max)

4개 Keychron 키보드(K7 Max ANSI RGB, K11 Max ANSI RGB, K15 Max ANSI RGB, V8 Max ANSI)의
키맵을 하나로 통일한 설정입니다. 공통 로직은 `users/wanja727`에, 보드별 레이아웃 배열은 각
`keyboards/keychron/<board>/.../keymaps/wanja727/keymap.c`에 있습니다. (VIA 지원)

---

## 1. 레이어 구조

| 레이어 | 진입 | 설명 |
|--------|------|------|
| **BASE** (MAC/WIN) | 기본 | 일반 타이핑. 숫자열은 tap=숫자 / hold=F1~F12. |
| **FN1** (media) | **Fn 키 hold** | 기존 Keychron 미디어/RGB/BT/밝기/볼륨/BT_HST/NKRO 레이어 (원본 유지). |
| **NAV** | **CapsLock hold** (tap=한/영) | 방향/편집/브라우저/창/멀티모니터. |
| **MOUSE** | **Caps + A 토글** (해제 = Esc) | 마우스 이동/버튼/휠/브라우저 (Caps hold=빠른 이동). |

- **Fn 키 = 미디어(FN1)** 입니다. (K7/K11/V8 은 오른쪽 두 Fn 키 모두 미디어, K15 는 Fn = 미디어)
- **MOUSE 는 토글** 입니다: `Caps + A` 로 켜고, `Esc` 로 끕니다. (홀드가 아니라 토글이라
  손을 떼도 유지됨. Space 는 일반 Space 로 되돌렸습니다.)
- K15 의 **오른쪽 Ctrl 은 원래대로 Right Ctrl** 입니다.

MAC/WIN BASE 는 물리 OS 스위치로 전환되며 기존과 동일합니다.

---

## 2. CapsLock (tap=한/영, hold=NAV)

CapsLock 은 **tap-hold** 입니다:
- **Caps 탭 = 한/영 전환** (단일키)
- **Caps 홀드(또는 다른 키와 조합) = NAV 레이어**
- **Win + Caps = 기존 CapsLock**
- **MOUSE 레이어 중 Caps 홀드 = 빠른 커서 이동** (아래 8번 참고)

> 다른 키와 함께 눌리면 즉시 NAV(홀드)로 확정, 아무 키 없이 짧게 떼면 한/영. 판정은 `TAPPING_TERM`(200ms).

### NAV 매핑 (Caps + …)

| 키 | 동작 | 키 | 동작 |
|---|---|---|---|
| `Tab` | 브라우저 이전 탭 (Ctrl+Shift+Tab) | `Q` | 브라우저 다음 탭 (Ctrl+Tab) |
| `W` | 탭 닫기 (Ctrl+W) | `E` | 창 닫기 (Alt+F4) |
| `I` / `J` / `K` / `L` | ↑ / ← / ↓ / → | `U` / `O` | Home / End |
| `N` / `M` | Backspace / Delete | `A` | **MOUSE 레이어 토글** |
| `,` / `.` | 활성 창 **왼쪽/오른쪽 모니터** 이동 (Win+Shift+←/→) | | |

---

## 3. MOUSE 레이어 (Caps+A 토글 / Esc 해제)

`Caps + A` 로 MOUSE 레이어를 켜고(토글), `Esc` 로 끕니다. 홀드가 아니라 토글이라 손을 떼도
유지됩니다. (MOUSE 가 켜지면 Caps 는 NAV 가 아니라 "빠른 이동" 모디파이어가 되므로, 해제는
Caps+A 가 아니라 **Esc** 입니다.)

| 키 | 동작 | 키 | 동작 |
|---|---|---|---|
| `I` / `J` / `K` / `L` | 마우스 ↑ / ← / ↓ / → | `S` / `D` | 왼쪽 / 오른쪽 클릭 (BTN1 / BTN2) |
| `A` / `F` | 뒤로 / 앞으로 (BTN4 / BTN5) | `;` / `H` | 휠 위 / 휠 아래 |
| `U` / `O` | 휠 왼쪽 / 휠 오른쪽 | `Tab`/`Q`/`W`/`E` | 이전탭/다음탭/탭닫기/창닫기 |
| **`Caps` (hold)** | **빠른 커서 이동** | `Esc` | MOUSE 레이어 해제 |

---

## 4. FN1 = 기존 Keychron 미디어 레이어

Fn 키를 누르면 기존과 똑같이 밝기/볼륨/미디어 재생/블루투스 페어링(BT_HST1~3, P2P4G)/
RGB 제어/NKRO 토글/배터리 표시 등을 사용할 수 있습니다. (보드별 원본 배치 그대로, 레이어명만 FN1)

---

## 5. 한/영 전환 (KC_LNG1 / KC_RALT)

**Caps 키를 짧게 탭** 하면 한/영 전환입니다. 1순위로 **`KC_LNG1`** 을 사용합니다.
Windows IME 에서 동작하지 않으면 `users/wanja727/wanja727.h` 의 한 줄만 바꿉니다.

```c
#define HANGEUL_KEYCODE KC_LNG1   // 기본
// #define HANGEUL_KEYCODE KC_RALT // 한/영 키를 우측 Alt로 쓰는 환경
```

---

## 6. 브라우저/창 제어

NAV(Caps) 와 MOUSE(Space) 모두 동일하게:
- `Tab` = 이전 탭 (Ctrl+Shift+Tab), `Q` = 다음 탭 (Ctrl+Tab), `W` = 탭 닫기 (Ctrl+W), `E` = 창 닫기 (Alt+F4)

> 이전 버전의 Alt+Tab 작업 전환(custom ALT_TAB)은 제거했습니다. (Alt+Tab 은 기존처럼 직접 사용)

---

## 7. 멀티 모니터 활성 창 이동 (NAV)

- `Caps + ,` = `Win + Shift + ←` (왼쪽 모니터로), `Caps + .` = `Win + Shift + →` (오른쪽 모니터로)
  (`,` `.` 가 `<` `>` 모양이라 좌/우 mnemonic. 예전 Caps+A/S 자리는 A 가 MOUSE 토글로 바뀌어 이동)

---

## 8. 마우스 속도 (Kinetic 가속) + Caps 빠른 이동

- 기본 마우스 이동은 **Kinetic(부드러운 가속) 모드** 입니다. 천천히 시작(`MOUSEKEY_INITIAL_SPEED`)
  해서 부드럽게 최고 속도(`MOUSEKEY_BASE_SPEED`)까지 가속합니다. 살짝 누르면 한 스텝만 가서 정밀
  이동이 되고, 계속 누르면 빨라집니다.
- **MOUSE 레이어에서 CapsLock 을 홀드** 하면 `MS_ACL2` = `MOUSEKEY_ACCELERATED_SPEED`(빠른 속도)로
  전환됩니다. 넓은 화면을 한 번에 건너뛸 때 사용. 더 빠르게/느리게는 `config.h` 에서 조절.
- **OS 가속과의 구분:** QMK 출력에 Windows 의 포인터 속도/"포인터 정밀도 향상"이 곱해집니다.
  일정/정밀하게 쓰려면 *Windows 설정 > 마우스 > 포인터 옵션* 에서 "포인터 정밀도 향상"을 끄는 것을 권장.

---

## 9. 숫자열 tap/hold

- **탭 = 숫자/기호**, **길게(>200ms) = F1~F12** (임계값에서 즉시 발사).

---

## 10. MOUSE 레이어 진입/해제 (토글)

- 진입: **`Caps + A`** (`TG(MOUSE)`), 해제: **`Esc`**.
- 토글이라 손을 떼도 유지됩니다. Space 는 일반 Space 입니다(예전 Space-hold 진입은 폐지).
- 다시 hold 방식이 좋으면 각 보드 keymap 의 Space 를 `LT(MOUSE, KC_SPC)` 로 바꾸면 됩니다.

---

## 11. VIA 사용 시 주의

`VIA_ENABLE = yes` 로 빌드되어 VIA / Keychron Launcher 에서 인식됩니다. 레이어 수가 늘어
각 보드 `info.json` 의 `dynamic_keymap.layer_count` 를 **6** 으로 설정했습니다.

**custom keycode 한계:** `NUM_F1~12`, `MO_NAV`(Caps) 는 펌웨어 내부 custom keycode 라서 **VIA UI
에는 raw 코드로 보이고 직접 편집이 어렵습니다.** 동작은 펌웨어에 고정되어 있으니 그대로 두세요.
Launcher 가 내장 정의를 쓰면 NAV/MOUSE 레이어가 UI 에 안 보일 수 있으나 펌웨어 동작은 정상입니다.

---

## 참고: 코어 패치 (quantum/mousekey.c)

kinetic 모드 버그 하나를 코어에서 고쳤습니다: 마우스 **버튼을 오래 누른 뒤 IJKL 로 이동하면
커서가 최고 속도로 튀는** 문제. 원인은 `mousekey_on()` 이 버튼/ACL 키에서도 kinetic 타이머
(`mouse_timer`)를 시작시켜, 버튼을 쥔 시간이 가속 경과시간으로 잡히던 것. 타이머를 **이동/휠
키에서만 시작**하도록 수정했습니다.

> 이 변경은 `users/`/`keymaps/` 밖의 파일이라, `git merge upstream/2025q3` 시 충돌이 날 수
> 있습니다. 충돌 나면 `mousekey_on()` 의 해당 블록만 다시 적용하세요.

## 빌드

```bash
qmk compile -kb keychron/k7_max/ansi/rgb          -km wanja727
qmk compile -kb keychron/k11_max/ansi_encoder/rgb -km wanja727
qmk compile -kb keychron/k15_max/ansi_encoder/rgb -km wanja727
qmk compile -kb keychron/v8_max/ansi_encoder      -km wanja727
```

GitHub Actions(`.github/workflows/build-wanja727.yml`)에 push 하면 4개 보드를 자동 빌드해
`.bin`/`.hex` 를 artifact 로 올립니다.

---

## 검증 체크리스트

- [ ] 4개 보드 컴파일 / VIA 인식 / BASE 타이핑 정상
- [ ] Fn 키 = 기존 미디어/RGB/BT 동작
- [ ] Caps 탭 = 한/영, Caps 홀드 = NAV, Win+Caps = CapsLock
- [ ] Caps + I/J/K/L 방향, U/O Home·End, N/M Bksp·Del
- [ ] Caps + Tab/Q/W/E 브라우저, Caps + ,/. 모니터 간 창 이동
- [ ] Caps + A = MOUSE 토글 ON, Esc = MOUSE 토글 OFF
- [ ] MOUSE: I/J/K/L 이동, S/D 클릭, A/F 뒤로·앞으로, ;/H/U/O 휠, Tab/Q/W/E 브라우저
- [ ] MOUSE + Caps 홀드 = 빠른 이동
