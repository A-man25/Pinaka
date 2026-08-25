@echo off
setlocal

REM ============================================================
REM Pinaka Folder Structure Generator
REM ============================================================

echo.
echo ============================================================
echo              Pinaka Folder Structure Generator
echo ============================================================
echo.

REM Directory containing this BAT file: Pinaka\build\
set "BUILD_DIR=%~dp0"

REM Repository root: Pinaka\
set "ROOT_DIR=%BUILD_DIR%.."

echo Repository:
echo %ROOT_DIR%
echo.

REM Move to repository root
pushd "%ROOT_DIR%"


REM ============================================================
REM Root Directories
REM ============================================================

echo ============================================================
echo                  Creating Root Directories
echo ============================================================
echo.

call :CreateFolder "build"
call :CreateFolder "docs"
call :CreateFolder "thirdparty"
call :CreateFolder "proj\vs"


REM ============================================================
REM PinakaEngine
REM ============================================================

echo.
echo ============================================================
echo                    Creating PinakaEngine
echo ============================================================
echo.

call :CreateFolder "PinakaEngine"
call :CreateFolder "PinakaEngine\src"
call :CreateFolder "PinakaEngine\src\Pinaka"
call :CreateFolder "PinakaEngine\src\Pinaka\Foundation"
call :CreateFolder "PinakaEngine\src\Pinaka\Foundation\Containers"
call :CreateFolder "PinakaEngine\src\Pinaka\Foundation\Algorithms"
call :CreateFolder "PinakaEngine\src\Pinaka\Foundation\Geometry"
call :CreateFolder "PinakaEngine\src\Pinaka\Core"
call :CreateFolder "PinakaEngine\docs"
call :CreateFolder "PinakaEngine\proj"
call :CreateFolder "PinakaEngine\proj\vs"


REM ============================================================
REM PinakaStudio
REM ============================================================

echo.
echo ============================================================
echo                    Creating PinakaStudio
echo ============================================================
echo.

call :CreateFolder "PinakaStudio"
call :CreateFolder "PinakaStudio\src"
call :CreateFolder "PinakaStudio\docs"
call :CreateFolder "PinakaStudio\proj"
call :CreateFolder "PinakaStudio\proj\vs"


REM ============================================================
REM Tests
REM ============================================================

echo.
echo ============================================================
echo                       Creating Tests
echo ============================================================
echo.

call :CreateFolder "Tests"
call :CreateFolder "Tests\src"
call :CreateFolder "Tests\docs"
call :CreateFolder "Tests\proj"
call :CreateFolder "Tests\proj\vs"


REM ============================================================
REM Finished
REM ============================================================

echo.
echo ============================================================
echo              Pinaka Structure Ready
echo ============================================================
echo.

popd

exit /b 0


REM ============================================================
REM CreateFolder
REM
REM Creates a directory if it does not exist.
REM Otherwise reports that it already exists.
REM ============================================================

:CreateFolder

if exist "%~1\" (
    echo [EXISTS]   %~1
) else (
    mkdir "%~1"

    if errorlevel 1 (
        echo [FAILED]   %~1
        exit /b 1
    ) else (
        echo [CREATED]  %~1
    )
)

exit /b 0