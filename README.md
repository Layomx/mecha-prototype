# Mecha Prototype

A low-poly mecha game clone written in modern C++.

## Requirements

- CMake 3.25 or newer
- Ninja
- A compiler with C++23 support
- `clangd` and `clang-format` for Helix integration

## Build and run

The presets generate build artifacts inside `build/`, which is not tracked:

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
./build/debug/mecha_prototype
```

For an optimized build:

```sh
cmake --preset release
cmake --build --preset release
ctest --preset release
```

`compile_commands.json` is generated automatically. `clangd` uses the
compilation database in `build/debug`, so configure that preset before
starting development.

## Initial structure

- `include/`: public headers organized by module.
- `src/`: module implementations and the entry point.
- `tests/`: tests run through CTest.
- `assets/`: game assets, including shaders.
