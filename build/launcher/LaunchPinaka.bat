@echo off
setlocal EnableExtensions DisableDelayedExpansion
rem PINAKA | Windows entry point. Runs correctly from any working directory.
set "PROJECT_FORGE=%~dp0PinakaLauncher.ps1"
if not exist "%PROJECT_FORGE%" (
  echo [PINAKA ERROR] Missing companion file: "%PROJECT_FORGE%"
  pause
  exit /b 2
)
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PROJECT_FORGE%" %*
set "RC=%ERRORLEVEL%"
if not "%RC%"=="0" (
  echo.
  echo [PINAKA] Launcher exited with code %RC%.
  if "%~1"=="" pause
)
exit /b %RC%
