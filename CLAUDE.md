# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project goal

A custom, Pokemon Fire Red–style game in C++/SFML: a hand-built overworld map (assembled in Tiled from Fire Red tile images), a custom story told through NPCs and dialogue, walkable interiors (houses), running shoes and a bike, and RPG progression (EVs/IVs/natures/EXP) on top of a working battle engine. Custom Pokemon and moves should be easy to add via the data files. Bag/items and a PC box system are intentionally deferred but the codebase should stay easy to extend into them later.

This is the user's own project to build — Claude's role here is design help, planning, debugging, and review, not driving the implementation end-to-end unless explicitly asked to write code.

## Project status

- **Battle engine**: implemented and working (`include/`+`src/` under `pokemon/`, `move/`, `misc/`, `typechart/`, `battle/`), ported from an earlier project. Handles damage calc (STAB, type effectiveness, crits, burn), status effects + immunities, stat stages, confusion, protect, recoil/drain/healing, flinch, priority/speed turn order, PP/Struggle. Currently **console-only** — `Simulator` writes straight to `std::cout`/reads `std::cin`, and `src/main.cpp` is a text-mode 1v1 battle harness, not a real game loop.
- **Overworld / game**: not started. SFML is linked but unused — no window is opened yet. No IVs, EVs, natures, EXP/leveling, maps, NPCs, dialogue, warps, movement modes, or menus exist yet.
- **Data**: `data/test_pokemonv1.txt` (10 species, base stats only) and `data/test_movesv2.txt` (18 moves) are hand-authored CSV-style fixtures, loaded by `Pokemon_loader`/`Move_loader`. Extend these additively (new columns/rows) rather than replacing the format — this is also how custom Pokemon/moves get added later.
- **Assets**: `assets/` is empty. Plan is placeholder shapes first, then real Fire Red–sourced tiles/sprites assembled by the user in Tiled.

## Roadmap

Build in this order, each phase playable/testable before the next:

1. **Scene stack + Simulator I/O refactor** — add an `IScene` scene stack (`Overworld`/`Battle`/`Dialogue`) to `main.cpp`; change `Simulator` to emit a message log instead of printing directly, so both console and graphical battle UIs can consume it.
2. **Overworld skeleton** — `TileMap`/`Camera`/`GridActor`/`Collision` under new `include/world/`+`src/world/`, loading Tiled maps via `tmxlite`; player walks a placeholder-tile test map with collision.
3. **Warps & multi-map** — door `Warp` objects transition between an outdoor map and an interior map.
4. **NPCs & dialogue** — static `Npc` actors, interact key, `DialogueBox`, `GameFlags` (`unordered_map<string,bool>`) for story state.
5. **Battle integration** — new `include/battlescene/`+`src/battlescene/` (kept separate from the `battle/` engine): `BattleScene` wraps `Simulator` with HP bars/text box/move menu; wild-grass `EncounterZone`s and trainer `Npc`s trigger it.
6. **Party system** — `Party` (`vector<Pokemon>`, max 6); starter selection becomes an in-world scene instead of the console picker.
7. **EVs/IVs/Natures/EXP/Leveling** — extend `Stats.h` with `IVs`/`EVs` (0–31/0–252, 510 cap) + `Nature` enum; real stat formula `HP = floor((2*Base+IV+floor(EV/4))*Level/100)+Level+10`, others `floor((floor((2*Base+IV+floor(EV/4))*Level/100)+5)*NatureMultiplier)`; EXP curve + level-up stat recalculation preserving HP lost; extend Pokemon data file with EXP-yield/EV-yield columns.
8. **Running Shoes & Bike** — a `MovementMode` (Walk/Run/Bike) gated by `GameFlags`.
9. **Content pass** — real Tiled maps from Fire Red tiles, real story/dialogue, custom Pokemon/moves as new data rows, real sprites in place of placeholders.

Deferred by design (stub interfaces now, build later): bag/items, PC/box storage, catching, save/load, Pokemon Centers/Mart (needs currency), abilities, evolution, held items, weather, mid-battle switching, Pokedex UI, sound/music, pause menu, rival/gym structure.

Known rough edges in the ported battle engine, worth revisiting: `Recover`-style healing uses base HP stat instead of calculated max HP (looks like a bug); crit chance is a simplified two-tier table rather than the real per-stage one; speed ties resolve via coin flip instead of a speed sub-stat; the type chart has no Fairy type.

## Conventions

- Keep the battle **engine** (`include/battle/`, `src/battle/` — `Simulator`, `DamageCalc`, `StatusDamage`) separate from battle **UI**: graphical battle-scene code (`BattleScene`, HP bar widgets, move menu, text box) belongs in its own `include/battlescene/`+`src/battlescene/`, not mixed into `battle/`.
- Data files (`data/*.txt`) are extended additively — new columns/rows — rather than reformatted, so the existing loaders keep working.

## Build & run

Requires `VCPKG_ROOT` to point at a vcpkg checkout (bootstrapped with `./bootstrap-vcpkg.sh`). Local dev machine has vcpkg at `~/vcpkg`.

```sh
export VCPKG_ROOT=~/vcpkg
cmake --preset default      # configures build/, vcpkg fetches & builds SFML on first run
cmake --build build
./build/martebursdag
```

First configure builds SFML and its dependencies (zlib, libpng, vorbis, flac, etc.) from source via vcpkg — takes about a minute, then is cached. Requires `pkg-config` (installed via `brew install pkg-config`) for zlib's build.

## Architecture

- `CMakeLists.txt` — single executable target `martebursdag`, C++20, links `SFML::System`, `SFML::Window`, `SFML::Graphics`, `SFML::Audio` (SFML 3 uses capitalized components and `SFML::`-namespaced targets, not the old `sfml-*` lowercase names).
- `vcpkg.json` — manifest-mode dependency list (currently just `sfml`).
- `CMakePresets.json` — `default` preset wires the vcpkg toolchain file via `$VCPKG_ROOT` and builds with Ninja into `build/`.
- `src/main.cpp` — entry point; currently a console-only battle harness (see Project status above).
- `include/`, `src/` — organized by subsystem: `pokemon/`, `move/`, `misc/` (Type/Status enums), `typechart/`, `battle/` (the battle engine). New subsystems (`world/`, `battlescene/`, etc.) should follow the same one-folder-per-subsystem pattern.
- `data/` — hand-authored CSV-style Pokemon/move data (`test_pokemonv1.txt`, `test_movesv2.txt`), loaded at startup.
- `assets/` — sprites/tilesets/audio go here (currently empty).

SFML 3 event handling uses the new `std::optional<sf::Event>` polling API (`window.pollEvent()` returns `std::optional`, check kind via `event->is<sf::Event::Closed>()`), not the SFML 2 style `sf::Event` out-param + switch on `event.type`. Keep new code consistent with this if extending the main loop.
