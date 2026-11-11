# PINAKA | Explicit Windows environment preparation, independent of visual launcher
$ErrorActionPreference='Stop'
$root=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$src=Join-Path $root 'src\PinakaEngine\Pinaka'
if (-not (Test-Path $src -PathType Container)) { throw 'PINAKA source directory missing: src\PinakaEngine\Pinaka.' }
$git=Get-Command git.exe -ErrorAction SilentlyContinue
$glfw=Join-Path $root 'thirdparty\GLFW\glfw\include\GLFW\glfw3.h'
if (-not (Test-Path $glfw -PathType Leaf)) {
    if (-not $git) { throw 'Git for Windows is needed to initialize GLFW.' }
    Push-Location $root
    try { & $git.Source submodule update --init --recursive; if ($LASTEXITCODE -ne 0) {throw 'Git submodule initialization failed.'} }
    finally {Pop-Location}
}
if (-not (Test-Path $glfw -PathType Leaf)) { throw 'GLFW source is not available.' }
Write-Host '[PINAKA] GLFW and source layout ready.' -ForegroundColor Green
Write-Host '[PINAKA] Compiler/Premake checks are handled by the launcher.' -ForegroundColor Gray
