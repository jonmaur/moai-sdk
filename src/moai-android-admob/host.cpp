// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-android-admob/host.h>
#include <moai-android-admob/MOAIAdmobAndroid.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUAndroidAdmobAppInitialize () {
}

//----------------------------------------------------------------//
void AKUAndroidAdmobAppFinalize () {
}

//----------------------------------------------------------------//
void AKUAndroidAdmobContextInitialize () {
	REGISTER_LUA_CLASS ( MOAIAdmobAndroid )
}