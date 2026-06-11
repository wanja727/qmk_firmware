# wanja727 — Keychron 통합 커스텀 (K7 / K11 / K15 / V8 Max)

4개 Keychron 키보드의 키맵을 하나로 통일한 설정. 공통 로직은 `users/wanja727`, 보드별 레이아웃은
각 `keyboards/keychron/<board>/.../keymaps/wanja727/keymap.c`. (VIA 지원)

설계 목표: **양손을 홈로우에 둔 채 NAV/MOUSE 를 쓰는 것.** MOUSE 는 toggle 이 아니라
**명시적 ON / OFF**(진입키=항상 ON, 해제키=항상 OFF) 구조.

---

## 1. 레이어 구조

| 레이어 | 진입 | 설명 |
|--------|------|------|
| **BASE** | 기본 | 타이핑. 숫자열 tap=숫자/hold=F1~F12. 좌Shift=일반 Shift. Caps tap=MOUSE ON. |
| **FN1** (media) | Fn 키 hold | 기존 Keychron 미디어/RGB/BT/밝기/볼륨/BT_HST/NKRO (원본 유지). |
| **NAV** | **CapsLock hold** 또는 **Space hold** | 방향/편집/브라우저/창/모니터/휠. |
| **MOUSE** | **Caps tap = ON** / **Shift tap = OFF** | 마우스 이동/버튼/휠. 문자 입력 키 누르면 자동 OFF. |

- **NAV 진입은 Caps 홀드 또는 Space 홀드** 둘 다 가능. (Space = `LT(NAV, KC_SPC)`: 탭=Space,
  홀드=NAV. Caps 가 한 칸 왼쪽이라 손이 치우치는 걸 보완하려고 엄지 Space 도 NAV mod 로 추가.)
- **MOUSE 는 toggle 이 아님.** Caps 를 **탭**하면 항상 ON(`layer_on`). 끄는 건 **Shift 탭 = MOUSE OFF**
  (항상 OFF), 또는 **문자 입력 키를 누르면 그 키 입력 후 자동 OFF**(BASE 복귀).
- 우측 Alt 한/영은 OS 단에서 이미 동작 → 펌웨어에서 따로 매핑하지 않음(기존 동작 유지).
- Fn 키 = 미디어. (K7/K11/V8 오른쪽 두 Fn 모두 미디어, K15 는 Fn = 미디어 / 오른쪽 Ctrl 은 Right Ctrl)

---

## 2. NAV 레이어 (Caps hold 또는 Space hold)

진입: **CapsLock 홀드** 또는 **Space 홀드**.
- **CapsLock**: 홀드/조합 = NAV, **탭 = MOUSE ON**, **Win+Caps = 기존 CapsLock**.
- **Space**: 홀드 = NAV, 탭 = 일반 Space (`LT(NAV, KC_SPC)`).

> Caps/Space 모두 다른 키와 함께 눌리면 NAV(홀드)로 동작, 짧게 떼면 각각 MOUSE ON / Space.

### NAV 매핑 (Caps 또는 Space + …)

| 키 | 동작 | 키 | 동작 |
|---|---|---|---|
| `Q` | 이전 탭 (Ctrl+Shift+Tab) | `W` | 다음 탭 (Ctrl+Tab) |
| `E` | 탭 닫기 (Ctrl+W) | `R` | 창 닫기 (Alt+F4) |
| `T` | 새 탭 (Ctrl+T) | `A` / `S` | 마우스 뒤로 / 앞으로 (BTN4 / BTN5) |
| `D` / `F` | 활성 창 왼쪽/오른쪽 모니터 이동 (Win+Shift+←/→) | `U` / `O` | Home / End |
| `I`/`J`/`K`/`L` | ↑ / ← / ↓ / → | `N` / `M` | Backspace / Delete |
| `H` / `;` / `Y` / `P` | 휠 업/다운/좌/우 | | |

---

## 3. MOUSE 레이어 (Caps tap = ON / Shift tap = OFF)

- 진입: **Caps 탭** (항상 ON)
- 해제(OFF):
  - **좌Shift 탭 = MOUSE OFF**(항상 OFF), **좌Shift 홀드 = 일반 Shift**.
  - **문자 입력 키(알파벳·숫자·기호·Space·우측 Alt(한/영))를 누르면** 그 키가 그대로 입력되면서
    **자동으로 MOUSE OFF → BASE 복귀**. (OS 한/영 상태와 무관하게 동작.)
  - **Space 탭 = Space 입력 + MOUSE OFF**(문자 입력 취급), **Space 홀드 = NAV**.
  - **단, `Ctrl`/`Alt`/`GUI` 가 눌려 있는 동안(=단축키 조합)에는 auto-off 하지 않음.** 예: 마우스로
    단어 블럭 지정 후 `Ctrl+C`/`Ctrl+V` 해도 MOUSE 유지. (Shift 는 예외 — Shift+글자=대문자라
    여전히 문자 입력으로 보고 auto-off.)

| 키 | 동작 | 키 | 동작 |
|---|---|---|---|
| `I`/`J`/`K`/`L` | 마우스 ↑ / ← / ↓ / → | `D` / `F` | 왼쪽 / 오른쪽 클릭 (BTN1 / BTN2) |
| `H` / `;` / `Y` / `P` | 휠 업/다운/좌/우 | **`Shift` 탭 / 홀드** | **MOUSE OFF / 일반 Shift** |
| `Space` 탭 / 홀드 | Space 입력+MOUSE OFF / NAV | **`Caps` 홀드** | NAV (뒤로/앞으로·브라우저·모니터·방향) |

> - **자동 BASE 복귀 대상 = '문자 입력' 키만**(알파벳·숫자·기호·Space·우측 Alt(한/영)). 마우스
>   이동/클릭/휠, NAV 키, modifier, layer/커스텀 제어 키, media, **encoder 회전/클릭**은 대상이 아니며
>   MOUSE 가 유지됩니다. **Ctrl/Alt/GUI 조합(단축키) 중에도 auto-off 안 함**(Shift 조합은 auto-off 유지).
> - **Space 홀드로 NAV 사용 중에는 auto-off 가 일어나지 않습니다**(NAV 활성 시 예외 처리).
> - **MOUSE 사용 중 Caps 를 누르고 있으면 NAV 전체가 덮어쓴다.** 즉 `Caps+ijkl`=방향키,
>   `Caps+D/F`=모니터 이동, `Caps+W/E/R/T`=브라우저, `Caps+A/S`=뒤로/앞으로 등 NAV 기능을
>   그대로 사용. Caps 를 떼면 다시 MOUSE. (이를 위해 **레이어 순서를 NAV > MOUSE** 로 둠 — ijkl·d/f
>   처럼 MOUSE 에도 매핑된 키까지 NAV 가 덮어쓰려면 NAV 가 위에 있어야 함.)
> - **knob/encoder**: BASE·NAV·MOUSE 모두 **회전=볼륨, 클릭=음소거**로 통일(MOUSE 의 휠 매핑 제거).

---

## 4. FN1 = 기존 Keychron 미디어 레이어

Fn 키를 누르면 기존과 똑같이 밝기/볼륨/미디어/블루투스(BT_HST1~3, P2P4G)/RGB/NKRO/배터리 등을
사용. (보드별 원본 배치 그대로, 레이어명만 FN1)

---

## 5. 한/영 전환 (우측 Alt, OS 단)

- **좌Shift 는 BASE 에서 순수 일반 Shift** 입니다. (이전의 `좌Shift 탭 = 한/영` 동작은 제거됨)
- 한/영 전환은 **우측 Alt** 로 OS 단에서 이미 동작하므로 펌웨어에서 별도 매핑하지 않습니다.
  (이번 작업에서 우측 Alt 매핑을 새로 추가/변경하지 않음)
- `HANGEUL_KEYCODE` 정의(`KC_LNG1`)는 (미사용)`HANGEUL` 커스텀 키코드 핸들러가 참조하므로
  정의만 유지합니다. 현재 키맵엔 배치돼 있지 않고, auto-off 판정 대상도 아닙니다.

```c
#define HANGEUL_KEYCODE KC_LNG1   // 기본 (현재 키맵엔 미배치)
// #define HANGEUL_KEYCODE KC_RALT // 우측 Alt 를 한/영으로 쓰는 환경
```

---

## 6. 브라우저 / 뒤로앞으로 / 모니터 / 휠 (NAV 기준)

- 브라우저: `Q`=이전탭, `W`=다음탭, `E`=탭닫기, `R`=창닫기, `T`=새 탭(Ctrl+T)
- 마우스 뒤로/앞으로: `A` / `S` (BTN4 / BTN5)
- 모니터 창 이동: `D` = 왼쪽, `F` = 오른쪽
- 휠: `H`=업, `;`=다운, `Y`=왼쪽, `P`=오른쪽 (NAV·MOUSE 동일 위치)
  (위는 모두 Caps 또는 Space 홀드 상태에서 사용)

> MOUSE 레이어에서도 **Caps 를 누르면** 위 NAV 기능을 그대로 쓸 수 있습니다(폴스루). 그래서
> 알파벳/홈로우 위치를 유지한 채 작업할 수 있습니다.

---

## 7. 마우스 속도 (Kinetic 가속)

- **Kinetic(부드러운 가속) 모드.** 살짝 누르면 한 스텝(정밀), 계속 누르면 가속(최고 `BASE_SPEED`).
- **MOUSE 의 Shift 저속이동(MS_ACL0) 기능은 제거**되었습니다. 이제 MOUSE 의 좌Shift 는
  `MS_OFF_SFT`(탭=MOUSE OFF / 홀드=일반 Shift)입니다. `DECELERATED_SPEED` 값은 kinetic
  알고리즘용으로 config.h 에 남겨두지만 더 이상 키에 바인딩하지 않습니다.
- `users/wanja727/config.h` 현재값: `BASE_SPEED 1000`, `INITIAL_SPEED 100`.
- **OS 가속 구분:** Windows 포인터 속도/"포인터 정밀도 향상"이 곱해집니다. 일정/정밀하게 쓰려면
  *Windows 설정 > 마우스 > 포인터 옵션* 에서 "포인터 정밀도 향상"을 끄는 것을 권장.

---

## 8. 숫자열 tap/hold

- **탭 = 숫자/기호**, **길게(>200ms) = F1~F12** (임계값에서 즉시 발사).

---

## 9. 커스텀 키코드 / 코어 패치

- custom keycode: `NUM_F1~12`(숫자/F열), `MO_NAV`(Caps tap=MOUSE ON / hold=NAV),
  `MS_OFF_SFT`(MOUSE 좌Shift: 탭=MOUSE OFF / 홀드=일반 Shift). VIA UI 에는 raw 로 보이며
  직접 편집은 제한적 — 동작은 펌웨어에 고정.
- **MOUSE 자동 BASE 복귀**: `process_record_user` → `wanja_process_record`. `is_text_input_key()`
  (알파벳/숫자/기호/Space/우측 Alt)이고 `mouse_auto_off_armed()`(MOUSE 활성 & NAV 비활성 &
  Ctrl/Alt/GUI 미사용)이면 키는 그대로 통과시키고 `layer_off(MOUSE)`. 숫자열(NUM_F)·Space(LT)는
  keycode 형태가 달라 각자 분기에서 처리(Space 는 LT tap 일 때만). encoder/마우스/NAV/modifier 는
  비대상이고, Ctrl/Alt/GUI 단축키 조합(예: Ctrl+C/V) 중에는 OFF 하지 않음.
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
- [ ] BASE 좌Shift = 일반 Shift (탭해도 한/영 전환 안 됨)
- [ ] 우측 Alt 한/영 = 기존 동작 그대로 (변경 없음)
- [ ] Caps 탭 = MOUSE ON, Caps 홀드 = NAV, Win+Caps = CapsLock
- [ ] **Space 탭 = Space**, **Space 홀드 = NAV** (BASE)
- [ ] MOUSE: Shift 탭 = MOUSE OFF, Shift 홀드 = 일반 Shift
- [ ] MOUSE: Space 탭 = Space 입력 + MOUSE OFF, Space 홀드 = NAV
- [ ] MOUSE: Space 홀드로 NAV 사용 중 auto-off 안 일어남
- [ ] MOUSE: I/J/K/L 이동·D/F 클릭·휠 = MOUSE 유지
- [ ] MOUSE: A/숫자/기호 입력 = 해당 키 입력 + MOUSE OFF (한/영 상태 무관)
- [ ] MOUSE: 우측 Alt(한/영) = 한/영 전환 + MOUSE OFF
- [ ] MOUSE: Ctrl+C/Ctrl+V 등 Ctrl/Alt/GUI 단축키 중에는 MOUSE 유지 (auto-off 안 됨)
- [ ] MOUSE: Shift+글자 = 대문자 입력 + MOUSE OFF (Shift 는 단축키 예외 아님)
- [ ] MOUSE: modifier/media/layer/custom 키는 auto-off 오판 없음
- [ ] BASE/NAV/MOUSE knob 회전 = 볼륨, 클릭 = 음소거 (MOUSE 휠 매핑 제거)
- [ ] MOUSE 에서 knob 회전/클릭으로 MOUSE 자동 OFF 안 됨
- [ ] NAV(Caps/Space + …): I/J/K/L 방향, U/O Home·End, N/M Bksp·Del
- [ ] NAV: Q/W/E/R/T 브라우저+새탭, A/S 뒤로·앞으로, D/F 모니터, 휠 H/;/Y/P
- [ ] MOUSE 중 Caps 홀드 = NAV 폴스루
- [ ] Fn 키 = 기존 미디어/RGB/BT, 숫자열 tap/hold 정상
