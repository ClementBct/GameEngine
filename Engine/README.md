#Dependency
vcpkg install sdl3
vcpkg install sdl3-image
vcpkg install box2d
vcpkg install openal-soft

build cmd :

cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:\Users\clebo\Documents\Dev\vcpkg\scripts\buildsystems\vcpkg.cmake
cmake --build build --config Release
cmake --build build --config Debug