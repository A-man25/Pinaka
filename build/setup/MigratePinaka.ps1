# PINAKA | One-time, non-destructive legacy-to-Forge migration
# Run from any directory: build\setup\MigratePinaka.bat
$ErrorActionPreference = 'Stop'
$root = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
function Rel([string]$p) { return Join-Path $root $p }
function MoveSafe([string]$old, [string]$new) {
    $a=Rel $old; $b=Rel $new
    if (-not (Test-Path -LiteralPath $a)) { return }
    if (Test-Path -LiteralPath $b) { throw "Destination exists; refusing overwrite: $new" }
    $parent=Split-Path -Parent $b
    New-Item -ItemType Directory -Path $parent -Force | Out-Null
    Move-Item -LiteralPath $a -Destination $b
    Write-Host "  [MOVE] $old -> $new" -ForegroundColor Cyan
}
function TestConflict([string]$old, [string]$new) {
    if ((Test-Path -LiteralPath (Rel $old)) -and (Test-Path -LiteralPath (Rel $new))) {
        throw "Migration cannot continue: both $old and $new exist. Reconcile them manually first."
    }
}
Write-Host "`n  PINAKA / SOURCE TREE MIGRATION" -ForegroundColor DarkYellow
Write-Host "  Root: $root"
Write-Host '  No source directory will be generated; only existing directories will be moved.'
Write-Host '  Commit or back up local changes before proceeding.' -ForegroundColor Yellow

# Fail BEFORE moving anything if mixed old/new layouts exist.
TestConflict 'PinakaEngine' 'src\PinakaEngine'
TestConflict 'PinakaStudio' 'src\PinakaStudio'
# On Windows the Tests/tests names are the same under case-insensitive lookup.
# The two-step rename below handles that safely.
if (-not (Test-Path (Rel 'PinakaEngine')) -and -not (Test-Path (Rel 'src\PinakaEngine'))) {
    throw 'Cannot find original or migrated PinakaEngine sources.'
}

MoveSafe 'PinakaEngine' 'src\PinakaEngine'
MoveSafe 'PinakaStudio' 'src\PinakaStudio'
# Work around case-insensitive case-only rename of Tests -> tests on Windows.
if (Test-Path -LiteralPath (Rel 'Tests')) {
    MoveSafe 'Tests' '_pinaka_tests_migration_'
    MoveSafe '_pinaka_tests_migration_' 'tests'
}

# Preserve PDFs and older IDE files rather than deleting them.
MoveSafe 'src\PinakaEngine\docs' 'docs\architecture\PinakaEngine'
MoveSafe 'src\PinakaEngine\proj' 'build\legacy\PinakaEngine-proj'
MoveSafe 'src\PinakaStudio\proj' 'build\legacy\PinakaStudio-proj'
MoveSafe 'tests\proj' 'build\legacy\Tests-proj'
MoveSafe 'proj\vs' 'build\legacy\root-proj-vs'
MoveSafe 'build\premake5.lua' 'build\legacy\premake5-original.lua'
MoveSafe 'build\GeneratePinakaProjects.bat' 'build\legacy\GeneratePinakaProjects-original.bat'
MoveSafe 'build\setEnv.bat' 'build\legacy\setEnv-original.bat'
MoveSafe 'README.md' 'docs\README-original.md'

# Add ignores without replacing a hand-written existing .gitignore.
$gitignore=Rel '.gitignore'
$marker='# PINAKA PROJECT FORGE MANAGED OUTPUTS'
$add=@'
# PINAKA PROJECT FORGE MANAGED OUTPUTS
/proj/
/build/bin/
/build/obj/
/build/tools/
/build/legacy/
/.vs/
/.vscode/
*.user
*.VC.db
'@
if (-not (Test-Path $gitignore)) { New-Item -Path $gitignore -ItemType File | Out-Null }
$current=Get-Content -LiteralPath $gitignore -Raw -ErrorAction SilentlyContinue
if ($current -notlike "*$marker*") { Add-Content -LiteralPath $gitignore -Value ("`r`n"+$add) }

Write-Host "`n  [SUCCESS] Layout migrated. No original code files were deleted." -ForegroundColor Green
Write-Host '  Next: build\launcher\LaunchPinaka.bat -> [3] Generate IDE projects.'
Write-Host '  Review: git status, then commit the intentional file moves.'
