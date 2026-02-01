@echo off
set BUILD_DIR=build

if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%
)

cd %BUILD_DIR%

cmake ..
if errorlevel 1 (
    echo Erreur lors de la generation CMake
    exit /b 1
)

cmake --build .
if errorlevel 1 (
    echo Erreur lors de la compilation
    exit /b 1
)

echo Build termine avec succes
pause
