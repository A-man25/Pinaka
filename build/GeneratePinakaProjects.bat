@echo off
setlocal

echo ============================================================
echo                 Pinaka Project Generator
echo ============================================================
echo.

set "BUILD_DIR=%~dp0"
set "ROOT_DIR=%BUILD_DIR%.."

REM ============================================================
REM Create Folder Structure
REM ============================================================

echo ============================================================
echo                 Creating Folder Structure
echo ============================================================
echo.

call "%BUILD_DIR%setEnv.bat"

if errorlevel 1 (
    echo.
    echo [ERROR] Failed to create folder structure.
    pause
    exit /b 1
)

echo.
echo [SUCCESS] Folder structure ready.
echo.


REM ============================================================
REM Premake Configuration
REM ============================================================

set "PREMAKE=%ROOT_DIR%\thirdparty\Premake\bin\premake5.exe"
set "PREMAKE_SCRIPT=%BUILD_DIR%premake5.lua"

echo Repository:
echo %ROOT_DIR%
echo.

if not exist "%PREMAKE%" (
    echo [ERROR] Premake was not found.
    echo.
    echo Expected:
    echo %PREMAKE%
    echo.
    pause
    exit /b 1
)

if not exist "%PREMAKE_SCRIPT%" (
    echo [ERROR] premake5.lua was not found.
    echo.
    echo Expected:
    echo %PREMAKE_SCRIPT%
    echo.
    pause
    exit /b 1
)


REM ============================================================
REM Generate Visual Studio Projects
REM ============================================================

echo ============================================================
echo             Generating Visual Studio Projects
echo ============================================================
echo.

pushd "%BUILD_DIR%"

"%PREMAKE%" --file="premake5.lua" vs2022

if errorlevel 1 (
    echo.
    echo [ERROR] Project generation failed.
    popd
    pause
    exit /b 1
)

popd


REM ============================================================
REM Finished
REM ============================================================

echo.
echo ============================================================
echo          Pinaka projects generated successfully
echo ============================================================
echo.
echo Solution:
echo %ROOT_DIR%\proj\vs\Pinaka.sln
echo.

pause
endlocal