cmake_minimum_required ( VERSION 2.8.11 )
project ( moai-ios-admob )



set(ADMOB_ROOT ${MOAI_ROOT}/3rdparty/admob-ios-7.3.1/GoogleMobileAds.framework)
set(ADMOB_LIB ${ADMOB_ROOT}/GoogleMobileAds)
add_library(AdMob SHARED IMPORTED)
set_property(TARGET AdMob PROPERTY IMPORTED_LOCATION ${ADMOB_LIB})
set_property(TARGET AdMob PROPERTY FRAMEWORK 1)

install(DIRECTORY "${ADMOB_ROOT}" DESTINATION lib)


add_library(moai-ios-admob STATIC
	#	"${MOAI_ROOT}/src/moai-ios-admob/MOAIAdMobIOS.h"
#		"${MOAI_ROOT}/src/moai-ios-admob/MOAIAdMobIOS.mm"
#		"${MOAI_ROOT}/src/moai-ios-admob/host.mm"
		)
target_include_directories(moai-ios-admob PUBLIC
		"$<BUILD_INTERFACE:${MOAI_ROOT}/src>"
		"$<BUILD_INTERFACE:${ADMOB_ROOT}>"
        "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>"
	)

target_link_libraries(moai-ios-admob AdMob moai-sim moai-util moai-core)
set_target_properties( moai-ios-admob PROPERTIES FOLDER Modules)
install(TARGETS moai-ios-admob EXPORT libmoai ARCHIVE DESTINATION lib)
install(FILES ${MOAI_ROOT}/src/moai-ios-admob/host.h DESTINATION include/moai-ios-admob)
