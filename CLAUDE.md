# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project status

A C++ Pokemon-style game, scaffolded but with no game logic yet — `src/main.cpp` just opens a blank SFML window and runs the event loop. Build system (CMake + vcpkg + SFML 3) is verified working.

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
- `src/main.cpp` — entry point.
- `include/` — headers go here (currently empty); `target_include_directories` already points at it.
- `assets/` — sprites/tilesets/audio go here (currently empty).

SFML 3 event handling uses the new `std::optional<sf::Event>` polling API (`window.pollEvent()` returns `std::optional`, check kind via `event->is<sf::Event::Closed>()`), not the SFML 2 style `sf::Event` out-param + switch on `event.type`. Keep new code consistent with this if extending the main loop.
