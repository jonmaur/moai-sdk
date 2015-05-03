# find_package ( OpenGL REQUIRED )
#include debug info inside the libs (not as .pdb files)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
message("Windows Phone Visual Studio Build Detected")
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -D_WIN32_WINNT=0x0602 -DWINVER=0x0602" )
SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0602 -DWINVER=0x0602"  )
  