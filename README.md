# Pilus Modloader
A WIP modloader for Primordialis.

## AIMS:
- Make making and loading mods as easy as possible
## TODO:
- Modlist
- Inject Mod DLLs
  - 1 Hardcoded DLL (DONE)
  - DLL specified on modlist
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
- Unscuff the super scuffed temporary solutions
- Make a DLL (DONE)
- Organise files
- Precompute relevant symbol addresses
    - Functions (DONE)
    - Labels (DONE)
- Precompute data type definitions
    - Structs
    - Unions
    - Enums
- Hook functions (DONE)
- Helper functions
- Lua API
- External mod config and assets