cmake_minimum_required ( VERSION 2.8.11 )
project ( moai-winrt )


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /ZW /EHsc")
set ( MOAI_WINRT_INCLUDES
  "${MOAI_ROOT}/src/"
  ${CMAKE_BINARY_DIR}/libmoai/config
  "${MOAI_ROOT}/src/moai-winrt/"
)

# Use all mm files in directory as source code
file ( GLOB MOAI_WINRT_SRC
  "${MOAI_ROOT}/src/moai-winrt/*.cpp"
  "${MOAI_ROOT}/src/moai-winrt/*.h"
)


include_directories ( ${MOAI_WINRT_INCLUDES} )
add_library ( moai-winrt STATIC ${MOAI_WINRT_SRC}  )

target_link_libraries ( moai-winrt moai-sim moai-util moai-core)

target_include_directories( moai-winrt PUBLIC
  "$<BUILD_INTERFACE:${MOAI_WINRT_INCLUDES}>"
  "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>"
)

set_target_properties( moai-winrt PROPERTIES FOLDER Modules )
install(TARGETS moai-winrt EXPORT libmoai ARCHIVE DESTINATION lib)
install(FILES "${MOAI_ROOT}/src/moai-winrt/host.h" DESTINATION "include/moai-winrt")
