@echo off
rem :: Determine target directory and cmake generator
setlocal enableextensions

set generator=Visual Studio 12

cd %~dp0%..
set rootpath=%cd%
set defaultprefix=%rootpath%\lib\windowsphone\vs2013
set libprefix=%2
if "%libprefix%"=="" set libprefix=%defaultprefix%

mkdir "build\build-vs2013-phone"
cd "build\build-vs2013-phone"

echo Creating Libs
cmake -G "%generator%" ^
-A ARM ^
-DBUILD_WINDOWS_PHONE=true ^
-DMOAI_HTTP_SERVER=false ^
-DMOAI_LUAJIT=false ^
-DCMAKE_SYSTEM_NAME=WindowsPhone ^
-DCMAKE_SYSTEM_VERSION=8.1 ^
-DCMAKE_INSTALL_PREFIX=%libprefix% ^
%rootpath%\cmake || exit /b 1

rem cmake --build . --target INSTALL --config Release || exit /b 1


echo "Build complete"