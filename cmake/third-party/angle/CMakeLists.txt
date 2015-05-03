cmake_minimum_required ( VERSION 2.8.11 )
project ( angle )

set ( ANGLE_ROOT "${MOAI_ROOT}/3rdparty/angle")
set ( ANGLE_BIN "${ANGLE_ROOT}/winrt/8.1/windowsphone/build" )
set ( ANGLE_LIB "${ANGLE_BIN}/$<CONFIG>_${CMAKE_GENERATOR_PLATFORM}")

add_custom_command(OUTPUT 
    ${ANGLE_BIN}/Debug_${CMAKE_GENERATOR_PLATFORM}/libGLESv2.dll
    ${ANGLE_BIN}/Debug_${CMAKE_GENERATOR_PLATFORM}/libEGL.dll
    WORKING_DIRECTORY ${ANGLE_BIN}
    COMMAND msbuild all.sln /target:all /p:Configuration=Debug /p:Platform=${CMAKE_GENERATOR_PLATFORM}
) 

add_custom_command(OUTPUT 
    ${ANGLE_BIN}/Release_${CMAKE_GENERATOR_PLATFORM}/libGLESv2.dll
    ${ANGLE_BIN}/Release_${CMAKE_GENERATOR_PLATFORM}/libEGL.dll
    WORKING_DIRECTORY ${ANGLE_BIN}
    COMMAND msbuild all.sln /target:all /p:Configuration=Release /p:Platform=${CMAKE_GENERATOR_PLATFORM}
)

add_custom_target(anglebin
    DEPENDS 
    ${ANGLE_BIN}/Debug_${CMAKE_GENERATOR_PLATFORM}/libGLESv2.dll
    ${ANGLE_BIN}/Debug_${CMAKE_GENERATOR_PLATFORM}/libEGL.dll
    ${ANGLE_BIN}/Release_${CMAKE_GENERATOR_PLATFORM}/libGLESv2.dll
    ${ANGLE_BIN}/Release_${CMAKE_GENERATOR_PLATFORM}/libEGL.dll
)

add_library(angle INTERFACE)

target_include_directories(angle INTERFACE ${ANGLE_ROOT}/include)
install(TARGETS angle EXPORT libmoai ARCHIVE DESTINATION lib)
install(DIRECTORY ${ANGLE_ROOT}/include/ DESTINATION include/angle)
install(FILES 
            ${ANGLE_LIB}/lib/libGLESv2.lib 
            ${ANGLE_LIB}/lib/libGLESv2.exp 
            ${ANGLE_LIB}/lib/libEGL.lib 
            ${ANGLE_LIB}/lib/libEGL.exp 
            DESTINATION lib)
install(FILES ${ANGLE_LIB}/libGLESv2.dll ${ANGLE_LIB}/libEGL.dll DESTINATION bin)
