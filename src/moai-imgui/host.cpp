// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-imgui/host.h>
#include <moai-imgui/headers.h>

//================================================================//
// aku-imgui
//================================================================//

//----------------------------------------------------------------//
void AKUImGuiAppFinalize () {
}

//----------------------------------------------------------------//
void AKUImGuiAppInitialize () {
}

//----------------------------------------------------------------//
void AKUImGuiContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIImGui )
	REGISTER_LUA_CLASS ( MOAIImVec2 )
}
