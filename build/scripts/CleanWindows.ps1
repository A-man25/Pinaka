# PINAKA | Remove ONLY generated projects, binaries and intermediates
param([switch]$Yes)
$ErrorActionPreference='Stop'
$root=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$paths=@('proj\vs2022','proj\vs2026','build\bin','build\obj')
Write-Host '[PINAKA] Generated output scheduled for cleaning:' -ForegroundColor Yellow
foreach ($p in $paths) { Write-Host "  $p" }
if (-not $Yes) {
    $reply=Read-Host 'Remove only these generated folders? [y/N]'
    if ($reply -notmatch '^(y|yes)$') { Write-Host 'Cancelled'; exit 0 }
}
foreach ($p in $paths) {
    $full=Join-Path $root $p
    if (Test-Path -LiteralPath $full) { Remove-Item -LiteralPath $full -Recurse -Force }
}
Write-Host '[PINAKA] Clean complete.' -ForegroundColor Green
