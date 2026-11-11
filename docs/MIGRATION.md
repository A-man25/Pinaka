# Migration from the legacy PINAKA layout

**This is a one-time, explicit operation.** The launcher will not silently move your source code. Commit your existing local changes first.

## Moves performed

| Before | After |
| --- | --- |
| `PinakaEngine/` | `src/PinakaEngine/` |
| `PinakaStudio/` | `src/PinakaStudio/` |
| `Tests/` | `tests/` |
| `src/PinakaEngine/docs/` (after first move) | `docs/architecture/PinakaEngine/` |
| Old `proj/vs/` | `build/legacy/root-proj-vs/` |
| Old engine/studio/tests VS projects | `build/legacy/*-proj/` |
| Old `build/premake5.lua`, `setEnv.bat`, `GeneratePinakaProjects.bat` | `build/legacy/` |
| Root `README.md`, if present | `docs/README-original.md` |

Current `thirdparty/GLFW/glfw` stays untouched, so `.gitmodules` needs no submodule-path surgery.

## What stays preserved

- Existing `src/Pinaka/` namespace/source hierarchy, including Core, Events, Foundation, Memory, Windows platform.
- Application and Window v1 PDFs; they move with the engine's docs into `docs/architecture/PinakaEngine/Architectural Notes/`.
- No new dummy source files, no auto-created source subdirectories.
- Old build scripts/project files archived locally under `build/legacy/` (ignored by Git).

## Post-migration verification

```bat
build\launcher\LaunchPinaka.bat diagnose
build\launcher\LaunchPinaka.bat generate vs2022
build\launcher\LaunchPinaka.bat build debug
```

Open `ide/vscode/Pinaka.code-workspace` to develop in VS Code. Confirm include paths, export/import macros and runtime DLL loading once the first Windows build completes. If your source contains hard-coded references to the old physical directory names, update those references.

The migration script refuses to overwrite an already-existing destination tree and prints an error rather than merging source trees automatically. Review `git status` and commit the moves only after a successful local build.
