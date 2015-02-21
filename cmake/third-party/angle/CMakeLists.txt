cmake_minimum_required ( VERSION 2.8.11 )
project ( angle )


set ( ANGLE_BIN "${MOAI_ROOT}/3rdparty/angle-bin" )

set ( ANGLE_LIB "${ANGLE_BIN}/windowsphone/Release_ARM/lib")

add_library(angle INTERFACE)

target_include_directories(angle INTERFACE ${ANGLE_BIN}/include)

install(TARGETS angle EXPORT libmoai ARCHIVE DESTINATION lib)
install(DIRECTORY ${ANGLE_BIN}/include/ DESTINATION include/angle)
install(FILES ${ANGLE_LIB}/libGLESv2.lib ${ANGLE_LIB}/libEGL.lib DESTINATION lib)
install(FILES ${ANGLE_LIB}/../libGLESv2.dll ${ANGLE_LIB}/../libEGL.dll DESTINATION bin)
