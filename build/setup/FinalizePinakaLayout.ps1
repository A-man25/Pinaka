# PINAKA | Finalize current v1.1 repository layout (NOT the legacy migration)
# Place this file in <repo>/build/setup/ and run:
#   powershell -NoProfile -ExecutionPolicy Bypass -File .\build\setup\FinalizePinakaLayout.ps1
#   powershell -NoProfile -ExecutionPolicy Bypass -File .\build\setup\FinalizePinakaLayout.ps1 -Apply
# The dry run makes no changes. -Apply moves three directories and updates all known paths.
[CmdletBinding()]
param([switch]$Apply)
$ErrorActionPreference = 'Stop'
$root = [System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
function AtRoot([string]$relative) { Join-Path $root $relative }

$moves = @(
    @{From='src\PinakaEngine\src\Pinaka'; To='src\PinakaEngine\Pinaka'; Parent='src\PinakaEngine\src'},
    @{From='src\PinakaStudio\src\Studio'; To='src\PinakaStudio\Studio'; Parent='src\PinakaStudio\src'},
    @{From='tests\src\TestApp'; To='tests\TestApp'; Parent='tests\src'}
)

# Exact substitutions for the existing Project Forge v1.1 files.
# Longer, more specific paths appear before shorter paths.
$changes = @(
    @{File='build\premake\premake5.lua'; Patches=@(
        @{Old='"PinakaEngine/src"'; New='"PinakaEngine"'},
        @{Old='"PinakaStudio/src"'; New='"PinakaStudio"'},
        @{Old='"tests/src"'; New='"tests"'}
    )},
    @{File='build\launcher\PinakaLauncher.ps1'; Patches=@(
        @{Old='src\PinakaEngine\src'; New='src\PinakaEngine\Pinaka'},
        @{Old="Write-Host '  [9]  Migrate existing repository to new layout'"; New="Write-Host '  [9]  Verify source layout'"},
        @{Old="'9' { Migrate }"; New="'9' { Diagnose }"},
        @{Old="'migrate' { Migrate }"; New="'migrate' { throw 'Legacy migration is disabled for this finalized repository.' }"}
    )},
    @{File='build\setup\SetupWindows.ps1'; Patches=@(
        @{Old='src\PinakaEngine\src'; New='src\PinakaEngine\Pinaka'},
        @{Old='PINAKA sources not migrated. First run build\setup\MigratePinaka.bat.'; New='PINAKA source directory missing: src\PinakaEngine\Pinaka.'}
    )},
    @{File='build\scripts\PinakaMac.sh'; Patches=@(
        @{Old='src/PinakaEngine/src/Pinaka/Platform/MacOS'; New='src/PinakaEngine/Pinaka/Platform/MacOS'},
        @{Old='src/PinakaEngine/src'; New='src/PinakaEngine/Pinaka'}
    )},
    @{File='ide\vscode\Pinaka.code-workspace'; Patches=@(
        @{Old='/src/PinakaEngine/src'; New='/src/PinakaEngine'}
    )},
    @{File='docs\README.md'; Patches=@(
        @{Old='PinakaEngine/src/Pinaka'; New='PinakaEngine/Pinaka'},
        @{Old='PinakaStudio/src/Studio'; New='PinakaStudio/Studio'},
        @{Old='tests/src/TestApp'; New='tests/TestApp'}
    )}
)

Write-Host "`nPINAKA / FINAL SOURCE LAYOUT" -ForegroundColor Cyan
Write-Host "Root: $root"
Write-Host 'No generated project files or source content will be deleted.'

# Preflight: require expected source layout and required project/config files.
foreach ($move in $moves) {
    $old = AtRoot $move.From; $new = AtRoot $move.To
    if ((Test-Path -LiteralPath $old) -and (Test-Path -LiteralPath $new)) {
        throw "Conflicting source paths both exist: $($move.From) and $($move.To). Resolve manually."
    }
    if (-not (Test-Path -LiteralPath $old) -and -not (Test-Path -LiteralPath $new)) {
        throw "Missing source directory (old and new): $($move.From)"
    }
    if (Test-Path -LiteralPath $old) {
        Write-Host "  [MOVE] $($move.From) -> $($move.To)" -ForegroundColor Yellow
    } else {
        Write-Host "  [DONE] $($move.To)" -ForegroundColor Green
    }
}
$updates = @()
foreach ($change in $changes) {
    $file = AtRoot $change.File
    if (-not (Test-Path -LiteralPath $file -PathType Leaf)) { throw "Missing configuration file: $($change.File)" }
    $original = [IO.File]::ReadAllText($file)
    $edited = $original
    foreach ($patch in $change.Patches) {
        $before = [string]$patch.Old; $after = [string]$patch.New
        if ($edited.Contains($before)) {
            $edited = $edited.Replace($before, $after)
        } elseif (-not $edited.Contains($after)) {
            throw "Unrecognized config version: '$($change.File)' lacks expected text: $before"
        }
    }
    if ($edited -ne $original) { Write-Host "  [PATCH] $($change.File)" -ForegroundColor Yellow }
    else { Write-Host "  [DONE]  $($change.File)" -ForegroundColor Green }
    $updates += @{File=$file; Original=$original; Edited=$edited}
}

if (-not $Apply) {
    Write-Host "`nDRY RUN ONLY: no files changed." -ForegroundColor Cyan
    Write-Host 'To apply: powershell -NoProfile -ExecutionPolicy Bypass -File .\build\setup\FinalizePinakaLayout.ps1 -Apply'
    exit 0
}

$stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
$backup = AtRoot ("build\legacy\final-layout-backup-" + $stamp)
New-Item -ItemType Directory -Force -Path $backup | Out-Null
foreach ($update in $updates) {
    $relative = $update.File.Substring($root.Length).TrimStart([char]92, [char]47)
    $backupFile = Join-Path $backup $relative
    New-Item -ItemType Directory -Force -Path (Split-Path -Parent $backupFile) | Out-Null
    [IO.File]::Copy($update.File, $backupFile, $true)
}
Write-Host "`nSaved config backups at: $backup" -ForegroundColor Green

foreach ($move in $moves) {
    $old = AtRoot $move.From; $new = AtRoot $move.To
    if (Test-Path -LiteralPath $old) {
        Move-Item -LiteralPath $old -Destination $new
        $oldParent = AtRoot $move.Parent
        $remaining = @(Get-ChildItem -LiteralPath $oldParent -Force)
        if ($remaining.Count -eq 0) { Remove-Item -LiteralPath $oldParent }
        else { Write-Host "  [KEEP] Parent contains other files: $($move.Parent)" -ForegroundColor Yellow }
    }
}
$utf8 = New-Object System.Text.UTF8Encoding($false)
foreach ($update in $updates) {
    if ($update.Edited -ne $update.Original) {
        [IO.File]::WriteAllText($update.File, $update.Edited, $utf8)
    }
}

Write-Host "`n[SUCCESS] Final source layout applied." -ForegroundColor Green
Write-Host 'Next: regenerate proj/vs2022 using the launcher, then inspect git status.'
Write-Host 'Do NOT rerun the legacy MigratePinaka.bat.' -ForegroundColor Yellow
