# Tower of Doom - Card Game

## Table of Contents
1. [Description](#description)
2. [Demo Video](#demo-video)
3. [Features](#features)
4. [Story & Objectives](#story--objectives)
5. [Feature Checklist vs Course Requirements](#feature-checklist-vs-course-requirements)
6. [Gameplay Overview](#gameplay-overview)
7. [Controls Quick Reference](#controls-quick-reference)
8. [Architecture Walkthrough](#architecture-walkthrough)
9. [Project Structure](#project-structure)
10. [Build and Run](#build-and-run)
11. [Saving, Scores, and Data Files](#saving-scores-and-data-files)
12. [Extending the Game](#extending-the-game)
13. [Contributors](#contributors)

## Description
Welcome to the Tower of Doom, where you have to fend off attacks from varied enemies commanding subject creatures. High replayability from random generation of enemies, events, and cards, ensuring endless hours of fun. This game appeals to fans of card games, text-based games, and adventure games.

## Demo Video
*drop a link to demo here.*

## Features
* **Multiple Difficulty Selection:** To fit different players and playing styles.
* **Multiple Levels:** For players to pace their playtime and adjust their strategies against new enemies.
* **Random Generation:** Generating enemies, events (adjusted for enemy and difficulty level), and cards (adjusted for rarity).
* **Data Structures:** Use of linked lists to store card lists, struct to store player state, class to store game information, maps to store enemies and events.
* **Dynamic Memory Management:** Player and enemy card lists cleared on initialization or new game.
* **Saving and Loading:** Highscore and player storage, with option to continue game from save.
* **Distinct Enemies:** Enemies have distinct strengths, weaknesses, and flavor, and can take exceptional actions. Unique Bosses at the ends of levels.
* **Card Collection:** Option to view encountered player and enemy cards within the current playthrough on winning the game. Hundreds of cards ingame.
* **Robust Scoring System:** Points for rounds completed and level bonus, adjusted to reward harder difficulties.
* **Program codes in multiple files:** Different sections of the game are compartmentalized, readable, and easily modified.
* **Proper indentation and naming styles:** Functions are easily located, read, and modified.
* **In-code documentation:** Code is clearly labelled to ensure clarity, readability, and replicability.

## Story & Objectives
- **Premise:** You are a lone hero scaling three haunted tower floors, facing randomly generated enemies and bosses (Skeleton King ➜ Archer Queen ➜ Dark Lord).
- **Objective:** Survive 30 rounds (10 per floor) by smartly drafting cards and choosing the best stat matchups in each duel.
- **Failure Condition:** HP drops to zero; you’ll be sent back to the main menu but your high score persists.
- **Victory Loop:** Clearing all levels grants a chance to review cards drawn by both sides before restarting for a higher score.

## Feature Checklist vs Course Requirements
| Requirement | Implementation Details |
| --- | --- |
| Randomness | Enemy selection (`generateRandomEnemy`), card draws (`drawncard`), enemy events in `enemy_config.h` all rely on seeded RNG. |
| Data Structures | Linked lists for card decks/hands (`Card`), structs/classes for `Card` and `GameState`, STL maps/vectors for enemy and event tables. |
| Dynamic Memory | Cards are dynamically allocated (`addcard`, `deleteList`) and cleaned between runs. |
| File I/O | `player.txt` + `highscore.txt` handle persistent saves/high scores; `cards.txt` is parsed at runtime for the master deck. |
| Multiple Files | Gameplay logic is separated into modules (`game`, `enemy`, `scoring`, `interface`, `card`, etc.) for clarity. |
| Defensive Programming | Input loops in `interface.cpp` validate every command; file loaders reset to defaults on malformed data. |

## Gameplay Overview

1. **Launch & Continue** – When the ASCII start page appears, press `s` for a fresh run or `c` to resume the last save (if available).
2. **Pick Difficulty** – Choose `e`, `m`, or `h`. Difficulty influences enemy stat multipliers, card rarity odds, score bonuses, and incoming damage.
3. **Draw Cards** – Each round deals three cards with different STR/CHA/WIS values. Press `1`, `2`, or `3` to add one to your hand (duplicates get sorted automatically).
4. **Select Stat** – Inspect the chosen card and press `1` (STR), `2` (CHA), or `3` (WIS) to decide the duel stat.
5. **Resolve Battle** – The enemy draws its own card with level-based stat biases and possible random events. The interface shows both cards, HP impact, and prompts `n` to proceed.
6. **Progression** – Survive 10 rounds to clear a level, then decide: `n` to advance, `s` to save, or `m` to return to the main menu. Bosses await at rounds 10/20/30.
7. **Endgame** – Losing all HP triggers the defeat screen (`m` to return). Clearing all three levels unlocks a victory screen where you can review collected player/enemy cards (`c` / `e`).

### Level & Enemy Progression
- **Rounds 1–9:** Random regular enemies with flavor text and stat biases.
- **Round 10:** Floor boss with guaranteed higher-rarity cards and heavier event modifiers.
- **Between Floors:** Automatically bank a level bonus (`GameState::levelBonus`), then choose to continue, save, or head back to the menu.

### Combat Resolution Details
- Player stats vs enemy stats are compared in `battlePlayer`; draws trigger an immediate rematch against the same foe.
- Damage on defeat is computed via `computeDamage`, which factors in chosen stat differentials and difficulty multipliers.
- Score increments for victories and per-level bonuses; high scores persist globally across runs.

## Architecture Walkthrough

| Component | Responsibilities |
| --- | --- |
| `main.cpp` | Boots the program and hands control to `Game::main_game`. |
| `game.*` | Manages `GameState`, menus, level/round loops, boss transitions, win/lose flows. |
| `interface.*` | Renders every ASCII screen (menus, card selection, battle summaries) and validates user input. |
| `card.cpp` | Parses `cards.txt` into a linked list and prints cards for galleries. |
| `card_drawing.cpp` | Implements the rarity distribution (`qual_prob`), seeded draws, sorted hand insertion, and cleanup utilities. |
| `enemy.*` + `enemy_config.h` | Defines enemy pools, bosses, flavor text, stat biases, and random event effects. |
| `scoring.*` | Stores HP/level/round/difficulty/score, scoring logic, save/load handling, and damage calculations. |

## Project Structure

| File/Directory | Purpose |
| --- | --- |
| `cards.txt` | Master card database (ID, rarity, STR/CHA/WIS stats, display name). |
| `enemy_config.h` | Lists all enemies/bosses, flavor text, stat biases, and random event tables. |
| `game.cpp/.h` | Core orchestrator: menus, difficulty, level/round flow, win/lose logic. |
| `interface.cpp/.h` | ASCII UI rendering plus validated input handlers (start page, selections, contest screen). |
| `card.cpp` | Deck loader from `cards.txt`, card printing for galleries, linked-list builder. |
| `card_drawing.cpp` | Difficulty-aware rarity probabilities (`qual_prob`), card drawing, sorted hand insertion, cleanup helpers. |
| `enemy.cpp/.h` | Enemy selection, card generation with events, battle result messaging. |
| `scoring.cpp/.h` | `GameState` definition, score/damage formulas, save/load, high-score management. |
| `header.h` | Shared `Card` struct and deck-handling function declarations. |
| `main.cpp` | Program entry point that instantiates the `Game` singleton. |
| `Makefile` | Build automation for compiling, linking, cleaning artifacts. |
| `player.txt` | Auto-generated save snapshot (HP, level, round, difficulty, score). |
| `highscore.txt` | Persistent best-score tracker, updated whenever a new record is set. |

Key assets such as `player.txt` and `highscore.txt` are produced automatically the first time you save or finish a run; deleting them resets the game state.


## Build and Run

### Prerequisites

- macOS / Linux environment with `g++` supporting at least GNU++11
- Standard C++ STL headers (no third-party dependencies)

### Compile

```bash
cd "Tower of Doom"
make
```

This generates the `game` executable plus dependency/object files.

### Run

```bash
./game
```

The binary reads/writes saves relative to the `Tower of Doom/` directory, so launch it from there. Use `make clean` anytime you want to remove build artifacts.

## How to Play

1. **Launch & Continue** – When the ASCII start page appears, press `s` for a fresh run or `c` to resume the last save (if available).
2. **Pick Difficulty** – Choose `e`, `m`, or `h`. Difficulty influences enemy stat multipliers, card rarity odds, score bonuses, and incoming damage.
3. **Draw Cards** – Each round deals three cards with different STR/CHA/WIS values. Press `1`, `2`, or `3` to add one to your hand (duplicates get sorted automatically).
4. **Select Stat** – Inspect the chosen card and press `1` (STR), `2` (CHA), or `3` (WIS) to decide the duel stat.
5. **Resolve Battle** – The enemy draws its own card with level-based stat biases and possible random events. The interface shows both cards, HP impact, and prompts `n` to proceed.
6. **Progression** – Survive 10 rounds to clear a level, then decide: `n` to advance, `s` to save, or `m` to return to the main menu. Bosses await at rounds 10/20/30.
7. **Endgame** – Losing all HP triggers the defeat screen (`m` to return). Clearing all three levels unlocks a victory screen where you can review collected player/enemy cards (`c` / `e`).

### Controls Quick Reference

| Screen | Input |
| --- | --- |
| Start page | `s` = new game, `c` = continue |
| Difficulty selection | `e`, `m`, `h` |
| Card selection | `1`, `2`, `3` |
| Stat selection | `1` = STR, `2` = CHA, `3` = WIS |
| Post-battle prompt | `n` to continue |
| Level complete | `n` next level · `s` save · `m` menu |
| Game over | `m` return to main page |
| Game complete | `m` menu · `c` player cards · `e` enemy cards |

## Saving, Scores, and Data Files

- `player.txt` stores HP, level, round, difficulty, and score so you can resume later. Saving also refreshes the high-score file.
- `highscore.txt` keeps the best score ever achieved. It’s updated whenever you beat the previous record.
- Removing either file simply resets progress/high score; the next run will regenerate them automatically.

| File | Contents | How to Reset |
| --- | --- | --- |
| `player.txt` | Five-line snapshot: HP, level, round, difficulty, total score. | Delete the file; a fresh one is generated on next save. |
| `highscore.txt` | Single integer storing the best score ever achieved. | Delete/overwrite to zero the leaderboard. |
| `cards.txt` | Master deck list (ID, rarity, STR, CHA, WIS, card name). | Edit entries or append new cards; run the game again to reload. |

## Extending the Game

1. **Add More Cards** – Append new rows to `cards.txt` (keep the same fixed-width format). The loader automatically absorbs them, and both player/enemy draws can use the new entries.
2. **Create New Enemies** – Update `enemy_config.h` by:
	- Adding the enemy name to `regularEnemySet`/`bossEnemySet`.
	- Providing stat biases, flavor text, event probabilities, and unique event descriptions.
3. **Balance Difficulty** – Adjust the Poisson lambdas in `card_drawing.cpp` or tweak `difficultyMultipliers` and `levelBonus` to change progression pacing.
4. **Customize UI** – `interface.cpp` controls all ASCII scenes; update the layout or add new prompts without touching game logic.
5. **Persist Extra Data** – Extend `GameState::savePlayer` / `loadPlayer` to track new stats (inventory, relics, etc.).


## Contributors
HKU COMP2113 Group 21, H2 2025

Members:
* Shum Jing Shu Nathan (UID: 3036179302)
* Ng Ngo Yin (UID: 3036059007)
* Deng Wai Man (UID: 3036240058)
* Wong Chun Hin (UID: 3036402321)
* Lam Cho Tsun (UID: 3036522523)
* Ari Delon David Winayu (UID: 3036182165)
