# PINAKA | VS Code Integration

This package is designed for the **already-migrated** PINAKA tree:

- `src/PinakaEngine/Pinaka/`
- `src/PinakaStudio/Studio/`
- `tests/TestApp/`
- `build/launcher/PinakaLauncher.ps1`
- `build/premake/premake5.lua`
- `thirdparty/GLFW/glfw/`

Unzip into the PINAKA repository **root**, preserving folders. This creates `.vscode/` and **replaces** `ide/vscode/Pinaka.code-workspace` to remove old duplicate tasks and debug entries. Back up any personal edits to that workspace file first. No source, build scripts, third-party or project files are changed.

Open either the PINAKA root folder in VS Code, or `ide/vscode/Pinaka.code-workspace`. Install the recommended Microsoft C/C++ extension. On Windows, install Visual Studio with Desktop development with C++ for MSBuild and Windows C++ debugging.

- **Ctrl+Shift+B**: build Debug
- **F5**: select **PINAKA Studio | Windows Debug**, then debug (builds first)
- **Terminal > Run Task**: Setup, Generate VS2022, Build Debug/Release, Run Studio, Build & Run, Diagnostics, Clean (Windows), Rebuild Debug

The PowerShell tasks call `build/launcher/PinakaLauncher.ps1` directly, **the same script started by** `LaunchPinaka.bat`, so the existing build pipeline remains the single source of truth. All paths are relative to `${workspaceFolder}`.

**Known limitations:** Compiling currently fails due to an unrelated existing C++ build error, not because of VS Code. Premake VS2026 generation requires a Premake version that supports the `vs2026` action. macOS generation may work, but a native macOS engine platform implementation is missing, so macOS building/debugging is intentionally not claimed working. The VS Code C++ extension auto-detects MSVC; if it cannot, use **C/C++: Edit Configurations (UI)** to choose your local compiler.
