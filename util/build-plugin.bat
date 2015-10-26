set SCRIPT_DIR=%~dp0%

set rootpath=%cd%\..
set libprefix=%rootpath%\lib\windows\vs2013

cmake -G "Visual Studio 12" -DLIB_PATH=%SCRIPT_DIR%\..\lib\windows\vs2013\Debug ^
-DBUILD_WINDOWS=TRUE ^
-DCMAKE_INSTALL_PREFIX=%libprefix%\Debug ^
-DPLUGIN_DIR=%cd%\..\ ^
%SCRIPT_DIR%..\cmake\hosts\host-plugin

cmake --build . --target INSTALL --config Debug