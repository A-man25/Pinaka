@echo off
setlocal EnableExtensions
title Smart App Control Manager
set "SACKEY=HKLM\SYSTEM\CurrentControlSet\Control\CI\Policy"
set "SACVALUE=VerifiedAndReputablePolicyState"
fltmc >nul 2>&1
if errorlevel 1 (
    echo Please right-click this file and select Run as administrator.
    pause
    exit /b 1
)
:menu
cls
echo ========================================
echo       SMART APP CONTROL MANAGER
echo ========================================
echo.
echo [1] Turn ON  - request enforcement
echo [2] Turn OFF - system-wide
echo [3] Check current policy status
echo [4] Exit
echo.
choice /c 1234 /n /m "Select an option: "
if errorlevel 4 exit /b 0
if errorlevel 3 goto status
if errorlevel 2 goto off
if errorlevel 1 goto on
goto menu
:on
set "TARGET=1"
goto apply
:off
echo.
echo This reduces protection for ALL applications, not only Pinaka.
echo Some Windows versions cannot easily re-enable Smart App Control.
choice /c YN /n /m "Continue? [Y/N]: "
if errorlevel 2 goto menu
set "TARGET=0"
:apply
echo.
reg.exe add "%SACKEY%" /v "%SACVALUE%" /t REG_DWORD /d %TARGET% /f
if errorlevel 1 goto failed
CiTool.exe -r
if errorlevel 1 goto failed
echo.
echo Requested mode saved and refresh attempted.
echo Check actual enforcement below; the registry alone is not proof.
:status
echo.
reg.exe query "%SACKEY%" /v "%SACVALUE%"
echo.
echo Registry: 0 = OFF, 1 = ON, 2 = EVALUATION.
echo In policy output, find the exact name VerifiedAndReputableDesktop.
echo Is Currently Enforced: true = ON; false = not enforced.
echo If evaluation is enforced, the mode is Evaluation, not ON.
echo.
CiTool.exe -lp
if errorlevel 1 goto failed
echo.
echo If the desired mode is not enforced, it may require a restart
echo or may not be supported by this Windows version.
pause
goto menu
:failed
echo.
echo A command failed. Do not assume protection has changed.
echo Use option 3 to inspect actual status.
pause
goto menu
