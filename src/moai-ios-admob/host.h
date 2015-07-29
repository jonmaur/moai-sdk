//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef AKU_IOS_ADMOB_HOST_H
#define AKU_IOS_ADMOB_HOST_H

#include <moai-core/host.h>
#include <UIKit/UIKit.h>

AKU_API void	AKUIosAdMobAppFinalize				();
AKU_API void	AKUIosAdMobAppInitialize				();
AKU_API void	AKUIosAdMobContextInitialize			();
AKU_API void AKUIosAdMobViewControllerInitialize (UIViewController *vc);
#endif
