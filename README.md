# Pilus Modloader
A WIP modloader for Primordialis.

## AIMS:
- Make making and loading mods as easy as possible
## TODO:
- Inject Mod DLLs
  - 1 Hardcoded DLL (DONE)
  - Any specified DLLs
- Basic UI
  - Mod list editor
    - Enable/Disable mods
    - Change load order
  - Mod config editor

# Plasmid API
A WIP C++ API for Primordialis mods.

## AIMS:
- C++ API (Plasmid API)
- Extend the LUA API
## TODO:
- Precompute relevant symbol addresses
    - Functions (DONE)
    - Labels
- Precompute data type definitions
    - Structs
    - Unions
    - Enums
- Hook functions (DONE)
- Lua API