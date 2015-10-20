cmake_minimum_required(VERSION 2.8.11)

#Host project for compiling a standalone binary plugin using moaisdk
project(host-plugin)
get_filename_component(MY_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake-modules" ABSOLUTE)
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${MY_SOURCE}")

set (LUA_LIB_DIR  "")
set (MOAI_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../..")

if (LIB_PATH)
  get_filename_component(LIB_PATH ${LIB_PATH} ABSOLUTE)
endif(LIB_PATH)

if (BUILD_ANDROID) 
  include(../../cmake-modules/platform-android.cmake)
endif (BUILD_ANDROID)

if (BUILD_IOS)
  include(../../cmake-modules/platform-ios.cmake)
endif (BUILD_IOS)

if (BUILD_LINUX)
  include(../../cmake-modules/platform-linux.cmake)
endif (BUILD_LINUX)

if (BUILD_OSX)
  include(../../cmake-modules/platform-osx.cmake)
endif (BUILD_OSX)

if (BUILD_WINDOWS)
  include(../../cmake-modules/platform-windows.cmake)
endif (BUILD_WINDOWS)

if (BUILD_HTML)
  include(../../cmake-modules/platform-html.cmake) 
endif (BUILD_HTML)

#common setup
include(../../cmake-modules/platform-common.cmake)
include(../../cmake-modules/module-setup.cmake)

include(../../cmake-modules/libmoai-setup)

#all setup, now include our plugin
add_subdirectory(${PLUGIN_DIR} "plugin")




