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

mkdir ARM
cd ARM
echo Creating ARM Libs
cmake -G "%generator%" ^
-A ARM ^
-DBUILD_WINDOWS_PHONE=true ^
-DMOAI_HTTP_SERVER=false ^
-DMOAI_UNTZ=false ^
-DMOAI_LUAJIT=false ^
-DCMAKE_SYSTEM_NAME=WindowsPhone ^
-DCMAKE_SYSTEM_VERSION=8.1 ^
-DCMAKE_INSTALL_PREFIX=%libprefix%\ARM\Release ^
%rootpath%\cmake || exit /b 1

rem cmake --build . --target INSTALL --config Release || exit /b 1

cd ..
mkdir Win32
cd Win32

echo Creating Win32 Debug Libs
cmake -G "%generator%" ^
-A Win32 ^
-DBUILD_WINDOWS_PHONE=true ^
-DMOAI_HTTP_SERVER=false ^
-DMOAI_UNTZ=false ^
-DMOAI_LUAJIT=false ^
-DCMAKE_SYSTEM_NAME=WindowsPhone ^
-DCMAKE_SYSTEM_VERSION=8.1 ^
-DCMAKE_INSTALL_PREFIX=%libprefix%\Win32\Debug ^
%rootpath%\cmake || exit /b 1

cmake --build . --target INSTALL --config Debug || exit /b 1

rem cmake -G "%generator%" ^
-DCMAKE_INSTALL_PREFIX=%libprefix%\Win32\Release ^
%rootpath%\cmake || exit /b 1

rem cmake --build . --target INSTALL --config Release || exit /b 1


echo "Build complete"