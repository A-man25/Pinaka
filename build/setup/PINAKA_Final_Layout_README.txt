PINAKA FINAL LAYOUT — FOR YOUR CURRENT MIGRATED TREE ONLY

IMPORTANT: Do NOT rerun build/setup/MigratePinaka.bat or select the old launcher migration option 9.

1. Back up/commit your current work and create a refactor branch.
2. Copy FinalizePinakaLayout.ps1 into <PINAKA>/build/setup/.
3. Open PowerShell at the PINAKA repository root.
4. Preview planned changes (NO files changed):
   powershell -NoProfile -ExecutionPolicy Bypass -File .\build\setup\FinalizePinakaLayout.ps1
5. After reviewing the preview, apply the changes:
   powershell -NoProfile -ExecutionPolicy Bypass -File .\build\setup\FinalizePinakaLayout.ps1 -Apply
6. Generate the Visual Studio solution again:
   .\build\launcher\LaunchPinaka.bat generate vs2022
7. Review the final git status and commit the intentional source moves when satisfied.

This script performs THREE directory moves, updates Premake, Windows setup/launcher,
macOS path checks, VS Code workspace and docs/README.md. It saves original configs
under ignored build/legacy/final-layout-backup-<timestamp>.

It does NOT fix existing C++ compilation errors and does NOT prove macOS engine portability.
The launcher menu's option 9 is repurposed to diagnostics after the patch.

Script was statically checked against the supplied Forge v1.1 text files; it has not
been executed under PowerShell/Windows here.
