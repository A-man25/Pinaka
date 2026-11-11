# PINAKA | Project Forge — PowerShell 5.1+ Windows UI and build orchestrator
param(
    [string]$Action = 'menu',
    [string]$Mode = 'debug'
)
$ErrorActionPreference = 'Stop'
$script:Root = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$script:Lua = Join-Path $script:Root 'build\premake\premake5.lua'
$script:GlfwHeader = Join-Path $script:Root 'thirdparty\GLFW\glfw\include\GLFW\glfw3.h'
$script:Workspace = Join-Path $script:Root 'ide\vscode\Pinaka.code-workspace'
$script:Generator = 'vs2022'

function Header([string]$title) { Write-Host "`n  $title" -ForegroundColor Cyan; Write-Host ('  ' + ('-'*66)) -ForegroundColor DarkGray }
function Good([string]$msg) { Write-Host ("  [OK] " + $msg) -ForegroundColor Green }
function Note([string]$msg) { Write-Host ("  [INFO] " + $msg) -ForegroundColor Gray }
function Fail([string]$msg) { Write-Host ("  [ERROR] " + $msg) -ForegroundColor Red }
function Tool([string[]]$names) {
    foreach ($n in $names) { $c=Get-Command $n -ErrorAction SilentlyContinue | Select-Object -First 1; if ($c) { return $c.Source } }
    return $null
}
function Cmd([string]$program, [string[]]$commandArgs, [string]$workingDir) {
    Push-Location -LiteralPath $workingDir
    try {
        # Never use $args as a declared parameter: it is a PowerShell automatic variable.
        Write-Host ("  [RUN] `"{0}`" {1}" -f $program, ($commandArgs -join ' ')) -ForegroundColor DarkCyan
        & $program @commandArgs
        $exitCode = $LASTEXITCODE
        if ($exitCode -ne 0) {
            throw "Command failed ($exitCode): $program $($commandArgs -join ' ')"
        }
    } finally { Pop-Location }
}
function Banner {
    Write-Host ''
    Write-Host '                          )\ ' -ForegroundColor DarkYellow
    Write-Host '                          ) \       P I N A K A' -ForegroundColor DarkYellow
    Write-Host '                =========)  )===================> ' -ForegroundColor Yellow
    Write-Host '                          ) /       ENGINE / PROJECT FORGE' -ForegroundColor DarkYellow
    Write-Host '                          )/' -ForegroundColor DarkYellow
    Write-Host ''
    Write-Host '          C++20  |  GLFW  |  PREMAKE  |  PROJECT FORGE' -ForegroundColor DarkCyan
    Write-Host ''
}
function Intro {
    Clear-Host; Banner
    Write-Host '  Forging PINAKA...' -ForegroundColor Gray
    for ($i=0; $i -le 40; $i+=2) {
        $frame=('  ' + ('-'*$i) + '>').PadRight(58)
        Write-Host -NoNewline ("`r"+$frame) -ForegroundColor Yellow
        Start-Sleep -Milliseconds 28
    }
    Write-Host "`n"
}
function Ensure-Migrated {
    if (Test-Path (Join-Path $script:Root 'src\PinakaEngine\Pinaka')) { return }
    if (Test-Path (Join-Path $script:Root 'PinakaEngine\src')) {
        throw 'Old layout detected. Select [9] Migrate repository before generating/building.'
    }
    throw "PinakaEngine source missing under src\PinakaEngine\Pinaka. Repository: $script:Root"
}
function Get-Premake {
    foreach ($candidate in @(
        (Join-Path $script:Root 'thirdparty\Premake\bin\premake5.exe'),
        (Join-Path $script:Root 'build\tools\premake\premake5.exe')
    )) { if (Test-Path $candidate -PathType Leaf) { return $candidate } }
    return Tool @('premake5.exe','premake5')
}
function Bootstrap-Premake {
    if (Get-Premake) { return }
    Header 'PREMAKE BOOTSTRAP'
    Note 'Portable Premake5 was not found. It can be downloaded from the official Premake GitHub releases.'
    $response = Read-Host '  Download Premake to build\tools\premake ? [y/N]'
    if ($response -notmatch '^(y|yes)$') { throw 'Premake5 required. Install it or place premake5.exe in thirdparty\Premake\bin.' }
    $target = Join-Path $script:Root 'build\tools\premake'
    New-Item -ItemType Directory -Force -Path $target | Out-Null
    $tempDir = Join-Path $env:TEMP ('pinaka-premake-' + [guid]::NewGuid().ToString('n'))
    New-Item -ItemType Directory -Force -Path $tempDir | Out-Null
    try {
        [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
        $releases = Invoke-RestMethod -Uri 'https://api.github.com/repos/premake/premake-core/releases?per_page=20' -Headers @{'User-Agent'='Pinaka-Project-Forge'}
        $asset = $null
        foreach ($release in $releases) {
            foreach ($a in $release.assets) {
                if ($a.name -match '(?i)^premake.*windows.*\.zip$') { $asset = $a; break }
            }
            if ($asset) { break }
        }
        if (-not $asset) { throw 'No compatible Windows release archive found in the Premake GitHub releases.' }
        $archive = Join-Path $tempDir 'premake.zip'
        Note "Downloading $($asset.name)"
        Invoke-WebRequest -Uri $asset.browser_download_url -OutFile $archive -UseBasicParsing
        if ($asset.digest -and $asset.digest -match '^sha256:(.+)$') {
            $hash=(Get-FileHash -Path $archive -Algorithm SHA256).Hash
            if ($hash -ne $Matches[1]) { throw 'Downloaded Premake hash does not match release metadata.' }
        }
        Expand-Archive -Path $archive -DestinationPath (Join-Path $tempDir 'extract') -Force
        $exe = Get-ChildItem (Join-Path $tempDir 'extract') -Filter premake5.exe -Recurse -File | Select-Object -First 1
        if (-not $exe) { throw 'Premake archive did not contain premake5.exe.' }
        Copy-Item $exe.FullName (Join-Path $target 'premake5.exe') -Force
        Good 'Premake installed locally.'
    } finally { Remove-Item $tempDir -Force -Recurse -ErrorAction SilentlyContinue }
}
function Ensure-GLFW {
    if (Test-Path $script:GlfwHeader -PathType Leaf) { return }
    $git=Tool @('git.exe','git')
    if (-not $git) { throw 'Git is missing. Install Git for Windows, then rerun the launcher.' }
    Header 'INITIALIZING GLFW SUBMODULE'
    Cmd -program $git -commandArgs @('submodule','update','--init','--recursive') -workingDir $script:Root
    if (-not (Test-Path $script:GlfwHeader -PathType Leaf)) { throw 'GLFW submodule is still missing.' }
    Good 'GLFW ready.'
}
function Setup {
    Header 'SYSTEM SETUP'
    & (Join-Path $script:Root 'build\setup\SetupWindows.ps1')
    Bootstrap-Premake
    Good 'Prerequisites available. (Visual Studio C++ tools are required to compile.)'
}
function Get-Solution([string]$generator) {
    $dir=Join-Path $script:Root ("proj\"+$generator)
    foreach ($suffix in @('.sln','.slnx')) {
        $p=Join-Path $dir ("Pinaka"+$suffix)
        if (Test-Path $p -PathType Leaf) { return $p }
    }
    return (Join-Path $dir 'Pinaka.sln')
}
function Generate([string]$generator='vs2022') {
    Ensure-Migrated; Ensure-GLFW; Bootstrap-Premake
    if (-not (Test-Path $script:Lua)) { throw "Missing Premake config: $script:Lua" }
    $premake=Get-Premake
    Header "GENERATE / $generator"
    Cmd -program $premake -commandArgs @("--file=$script:Lua", $generator) -workingDir $script:Root
    $s=Get-Solution $generator
    if (-not (Test-Path $s -PathType Leaf)) { throw "Generator completed, but solution was not found: $s" }
    $script:Generator=$generator
    Good "Project ready: $s"
}
function MSBuild {
    $vswhere = $null
    if (${env:ProgramFiles(x86)}) { $vswhere=Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe' }
    if ($vswhere -and (Test-Path $vswhere)) {
        $found=@(& $vswhere -latest -products '*' -requires Microsoft.Component.MSBuild -find 'MSBuild\**\Bin\MSBuild.exe' 2>$null)
        foreach ($f in $found) { if ($f -and (Test-Path $f)) { return $f } }
    }
    return Tool @('MSBuild.exe','msbuild.exe')
}
function Build([string]$configuration='Debug') {
    Ensure-Migrated
    $solution = Get-Solution $script:Generator
    if (-not (Test-Path $solution -PathType Leaf)) { Generate $script:Generator; $solution=Get-Solution $script:Generator }
    $compiler=MSBuild
    if (-not $compiler) { throw 'MSBuild not found. Install Visual Studio Desktop development with C++ workload.' }
    Header "BUILD / $configuration / x64"
    Cmd -program $compiler -commandArgs @($solution,'/nologo','/m','/verbosity:minimal',"/p:Configuration=$configuration",'/p:Platform=x64') -workingDir $script:Root
    Good "Build $configuration succeeded."
}
function Run([string]$configuration='Debug') {
    $bin = Join-Path $script:Root ("build\bin\$configuration-windows-x86_64")
    $exe = Join-Path $bin 'PinakaStudio.exe'
    if (-not (Test-Path $exe)) { throw "Studio executable not found: $exe. Build it first." }
    Header "RUN / PINAKA STUDIO / $configuration"
    Cmd -program $exe -commandArgs @() -workingDir $bin
    Good 'Studio exited successfully.'
}
function OpenVS {
    $s=Get-Solution $script:Generator
    if (-not (Test-Path $s)) { Generate $script:Generator; $s=Get-Solution $script:Generator }
    Start-Process -FilePath $s
    Good 'Visual Studio opening.'
}
function OpenCode {
    $code=Tool @('code.cmd','code.exe','code')
    if (-not $code) {
        foreach ($c in @((Join-Path $env:LOCALAPPDATA 'Programs\Microsoft VS Code\Code.exe'),(Join-Path $env:ProgramFiles 'Microsoft VS Code\Code.exe'))) {
            if (Test-Path $c) {$code=$c; break}
        }
    }
    if (-not $code) { throw 'VS Code not detected. Install VS Code or add code to PATH.' }
    if (-not (Test-Path $script:Workspace)) { throw "Missing VS Code workspace: $script:Workspace" }
    if ($code -match '\.cmd$') { & $code $script:Workspace }
    else { Start-Process -FilePath $code -ArgumentList ('"'+$script:Workspace+'"') }
    Good 'VS Code opening.'
}
function Diagnose {
    Header 'ENVIRONMENT / DIAGNOSTICS'
    Note "Root: $script:Root"
    $checks=@(
        @('New source layout',(Test-Path (Join-Path $script:Root 'src\PinakaEngine\Pinaka'))),
        @('GLFW',(Test-Path $script:GlfwHeader)),
        @('Git',[bool](Tool @('git.exe','git'))),
        @('Premake',[bool](Get-Premake)),
        @('MSBuild',[bool](MSBuild)),
        @('VS Code',[bool](Tool @('code.cmd','code.exe','code')))
    )
    foreach ($c in $checks) { if ($c[1]) { Good $c[0] } else { Fail $c[0] } }
}
function Migrate {
    Header 'MIGRATE / LEGACY PINAKA'
    Note 'Source files will be moved, never generated; original project files and scripts go to build\legacy.'
    Note 'Commit or back up your repository before migrating.'
    $confirm=Read-Host '  Continue migration? [y/N]'
    if ($confirm -notmatch '^(y|yes)$') { Note 'Migration cancelled.'; return }
    $scriptPath=Join-Path $script:Root 'build\setup\MigratePinaka.ps1'
    & $scriptPath
    if (-not $?) { throw 'Migration reported an error.' }
    Good 'Migration completed. Regenerate your IDE projects now.'
}
function ChooseGenerator {
    Header 'PROJECT GENERATOR'
    Write-Host '  [1] Visual Studio 2022 (also readable by newer VS versions)'
    Write-Host '  [2] Visual Studio 2026 (only if current Premake supports vs2026)'
    $g=Read-Host '  Generator [1]'
    if ($g -eq '2') { return 'vs2026' }
    return 'vs2022'
}
function Menu {
    Intro
    while ($true) {
        Clear-Host; Banner
        Write-Host '  [1]  Build + Run  /  Debug' -ForegroundColor Yellow
        Write-Host '  [2]  Build + Run  /  Release' -ForegroundColor Yellow
        Write-Host '  [3]  Generate IDE projects'
        Write-Host '  [4]  Build only / Debug'
        Write-Host '  [5]  Open Visual Studio'
        Write-Host '  [6]  Open VS Code'
        Write-Host '  [7]  Setup / Check dependencies'
        Write-Host '  [8]  Diagnostics'
        Write-Host '  [9]  Verify source layout'
    Write-Host '  [C]  Clean generated projects, binaries and objects'
        Write-Host '  [0]  Exit' -ForegroundColor DarkGray
        Write-Host ''
        Note "Repository: $script:Root"
        $choice=Read-Host '  PINAKA >'
        if ($choice -eq '0') { return }
        try {
            switch ($choice) {
                '1' { Build 'Debug'; Run 'Debug' }
                '2' { Build 'Release'; Run 'Release' }
                '3' { $gen=ChooseGenerator; Generate $gen }
                '4' { Build 'Debug' }
                '5' { OpenVS }
                '6' { OpenCode }
                '7' { Setup }
                '8' { Diagnose }
                '9' { Diagnose }
                'c' { & (Join-Path $script:Root 'build\scripts\CleanWindows.ps1') }
                'C' { & (Join-Path $script:Root 'build\scripts\CleanWindows.ps1') }
                default { Fail 'Choose a number 0–9.' }
            }
        } catch { Fail $_.Exception.Message }
        Read-Host '  Press Enter to return to PINAKA' | Out-Null
    }
}
try {
    switch ($Action.ToLowerInvariant()) {
        'menu' { Menu }
        'migrate' { throw 'Legacy migration is disabled for this finalized repository.' }
        'setup' { Setup }
        'diagnose' { Diagnose }
        'generate' { if (-not $Mode -or $Mode -eq 'debug') {Generate 'vs2022'} else {Generate $Mode} }
        'build' { if ($Mode -eq 'release') {Build 'Release'} else {Build 'Debug'} }
        'run' { if ($Mode -eq 'release') {Run 'Release'} else {Run 'Debug'} }
        'buildrun' { if ($Mode -eq 'release') {Build 'Release';Run 'Release'} else {Build 'Debug';Run 'Debug'} }
        'clean' { & (Join-Path $script:Root 'build\scripts\CleanWindows.ps1') -Yes }
        'vscode' { OpenCode }
        'vs' { OpenVS }
        default { throw "Unknown operation: $Action" }
    }
    exit 0
} catch { Fail $_.Exception.Message; exit 1 }
