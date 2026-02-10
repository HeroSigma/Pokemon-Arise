# Level Cap System

This project enables level caps that progress with story flags (Gym badges, Elite Four victories, and Champion). Caps affect experience gain and Rare Candy usage according to config.

## Overview

- Cap source: The current cap is derived from the first UNSET milestone flag in a mapping.
- Progression: When you defeat a Gym Leader or Elite Four member, their flag is set; the cap moves to the next milestone automatically.
- Post‑game: After becoming Champion, a trailing placeholder flag provides the post‑game cap.

## Configuration

- EXP cap type: `include/config/caps.h:14` (`B_EXP_CAP_TYPE`)
  - `EXP_CAP_NONE`: No caps at all.
  - `EXP_CAP_HARD`: No EXP at or above the cap (default).
  - `EXP_CAP_SOFT`: Diminishing EXP above the cap.
- Cap selection: `include/config/caps.h:15` (`B_LEVEL_CAP_TYPE`)
  - `LEVEL_CAP_FLAG_LIST` (default): Uses the flag→cap map in `src/caps.c`.
  - `LEVEL_CAP_VARIABLE`: Uses event variable `B_LEVEL_CAP_VARIABLE`.
- Rare Candy rule: `include/config/caps.h:18` (`B_RARE_CANDY_CAP`)
- EXP boost under cap: `include/config/caps.h:19` (`B_LEVEL_CAP_EXP_UP`)

## Implementation

- Function: `src/caps.c:8` `GetCurrentLevelCap()`
  - Iterates `sLevelCapFlagMap` and returns the cap for the first UNSET flag.
  - If all flags are set, returns `MAX_LEVEL`.
- EXP scaling: `src/caps.c:48` `GetSoftLevelCapExpValue()`
  - Applies soft/hard cap EXP rules and optional under‑cap bonus.
- Daycare: Obeys current cap (`src/daycare.c`).
- Rare Candy: Obeys current cap (`src/party_menu.c:5792`).

## Current Cap Map (This Repo)

Defined in `src/caps.c:12`:

- Pre‑Gym caps (first 8 entries use Gym badge flags):
  - Roxanne (Badge 1): 16
  - Brawly (Badge 2): 20
  - Wattson (Badge 3): 24
  - Flannery (Badge 4): 29
  - Norman (Badge 5): 33
  - Winona (Badge 6): 36
  - Tate & Liza (Badge 7): 42
  - Wallace/Juan (Badge 8): 46
- Elite Four (per member, pre‑battle caps):
  - Sidney: 48
  - Phoebe: 49
  - Glacia: 50
  - Drake: 52
- Champion:
  - Pre‑Champion (Wallace): 55
  - Post‑Champion: 65

Notes on semantics:

- “Pre‑X cap” is the cap while the corresponding `FLAG_*` is UNSET.
- After you beat X, the flag is set and the cap advances to the next value.
- The post‑Champion cap uses an always‑unset placeholder flag so it applies only after `FLAG_IS_CHAMPION` is set.

## Adjusting Caps

Edit `src/caps.c` inside `sLevelCapFlagMap`:

```c
// Example: change Winona cap to 37
{FLAG_BADGE06_GET, 37},
```

To change the post‑Champion cap, modify the trailing placeholder entry’s value.

## Variable‑Based Caps (Optional)

If you prefer driving the cap by an event variable (e.g., for custom modes):

1. Set in `include/config/caps.h`:
   - `#define B_LEVEL_CAP_TYPE LEVEL_CAP_VARIABLE`
   - `#define B_LEVEL_CAP_VARIABLE VARS_START + N` (pick a valid event var)
2. Update the variable in scripts as you progress:

```asm
// Example script snippet
setvar VAR_LEVEL_CAP, 29  // set cap to 29
```

## EV Caps (Related)

This repo also supports EV caps with a similar mechanism. See `src/caps.c:92` `GetCurrentEVCap()` and `include/config/caps.h:27`.

## Troubleshooting

- Cap didn’t change after a win:
  - Verify the correct `setflag` runs in the map script for that battle.
  - Check you are using `LEVEL_CAP_FLAG_LIST` and the mapping order is correct.
- Post‑Champion not 65:
  - Ensure Champion entry is 55 and a trailing placeholder flag sets 65 (see `src/caps.c:12`).

