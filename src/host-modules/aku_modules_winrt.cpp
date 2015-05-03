// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <zl-common/zl_platform.h>
#include <host-modules/aku_modules_winrt.h>

//================================================================//
// implementation
//================================================================//

//----------------------------------------------------------------//
void AKUModulesWinRTAppFinalize () {
#if AKU_WITH_WINRT
	AKUWinRTAppFinalize();
#endif
}

//----------------------------------------------------------------//
void AKUModulesWinRTAppInitialize() {
#if AKU_WITH_WINRT
	AKUWinRTAppInitialize();
#endif
}

//----------------------------------------------------------------//
void AKUModulesWinRTContextInitialize() {
#if AKU_WITH_WINRT
	AKUWinRTContextInitialize();
#endif
}

//----------------------------------------------------------------//
void AKUModulesWinRTPause(bool pause) {
	UNUSED ( pause );
}


//----------------------------------------------------------------//
void AKUModulesWinRTUpdate() {

}
