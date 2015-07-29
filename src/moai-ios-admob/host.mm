// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-ios-admob/host.h>
#include <moai-ios-admob/MOAIAdMobIOS.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUIosAdMobAppFinalize () {
}

//----------------------------------------------------------------//
void AKUIosAdMobAppInitialize () {
    MOAIAdMobIOS::Affirm();
}

void AKUIosAdMobViewControllerInitialize (UIViewController *vc) {
    MOAIAdMobIOS::Get().SetRootViewController(vc);
    MOAIAdMobIOS::Get().CreateAdView(vc);
}

//----------------------------------------------------------------//
void AKUIosAdMobContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIAdMobIOS );
}