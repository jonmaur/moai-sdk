// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	AKU_WINRT_MODULES_IOS_H
#define	AKU_WINRT_MODULES_IOS_H

#include <host-modules/aku_modules_winrt_config.h>
#include <host-modules/aku_modules.h>

#if AKU_WITH_WINRT
#include <moai-winrt/host.h>
#endif

//----------------------------------------------------------------//
void		AKUModulesWinRTAppFinalize				();
void		AKUModulesWinRTAppInitialize();
void		AKUModulesWinRTContextInitialize();
void		AKUModulesWinRTPause(bool pause);
void		AKUModulesWinRTUpdate();

#endif
