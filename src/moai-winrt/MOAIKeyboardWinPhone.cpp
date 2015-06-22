// Copyright (c) 2012 allaboutapps.at. All Rights Reserved.
//
// Contributed to the MOAI project by Jay Vaughan, allaboutapps.at
//
// This file implements the MOAIKeyboardWinPhone object
// for user-input from the soft keyboard on Android
// 
// http://getmoai.com
//

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-core/headers.h>
#include <moai-winrt/MOAIKeyboardWinPhone.h>

using namespace Windows::UI::Xaml::Controls;
using namespace Windows::ApplicationModel::Core;

//================================================================//
// MOAIKeyboardWinPhone
//================================================================//
  
//----------------------------------------------------------------//
// The listeners need to be called on the event

//----------------------------------------------------------------//
int MOAIKeyboardWinPhone::_hideKeyboard ( lua_State* L ) {
	MOAILuaState state ( L );
  
  lua_pushboolean ( state, false );

	MOAIKeyboardWinPhone::Get ().Finish ();

	return 0;
}

// Listeners use getText to retrieve the input
//----------------------------------------------------------------//
int MOAIKeyboardWinPhone::_getText ( lua_State* L ) {
	MOAILuaState state ( L );
	MOAIKeyboardWinPhone::Get ().PushText ( state );
	return 1;
}

//----------------------------------------------------------------//
int MOAIKeyboardWinPhone::_setListener ( lua_State* L ) {
	MOAILuaState state ( L );

	u32 idx = state.GetValue < u32 >( 1, TOTAL );

	if ( idx < TOTAL ) {
		MOAIKeyboardWinPhone::Get ().mListeners [ idx ].SetRef ( state, 2 );
	}

	return 0;
}

int MOAIKeyboardWinPhone::_setText ( lua_State* L ) { 

	MOAILuaState state ( L ); 

	cc8* text = lua_tostring ( state, 1 );


	return 0;
}

int MOAIKeyboardWinPhone::_showKeyboard ( lua_State* L ) {
	
	
	
	return 0;
}

int MOAIKeyboardWinPhone::_showTextKeyboard( lua_State* L ) {
	return 0;
}

int MOAIKeyboardWinPhone::_showNumberKeyboard( lua_State* L ) {
	return 0;
}

int MOAIKeyboardWinPhone::_showDateTimeKeyboard( lua_State* L ) {
	return 0;
}

int MOAIKeyboardWinPhone::_showPhoneKeyboard( lua_State* L ) {
	return 0;
}



//================================================================//
// MOAIKeyboardWinPhone
//================================================================//

//----------------------------------------------------------------//
void MOAIKeyboardWinPhone::Finish () {
}

//----------------------------------------------------------------//
MOAIKeyboardWinPhone::MOAIKeyboardWinPhone () {
	RTTI_SINGLE ( MOAILuaObject ) 
}

//----------------------------------------------------------------//
MOAIKeyboardWinPhone::~MOAIKeyboardWinPhone () {
	this->Finish ();
}

//----------------------------------------------------------------//
void MOAIKeyboardWinPhone::NotifyKeyEvent ( ) {


	MOAILuaRef& callback = this->mListeners [ EVENT_INPUT ];
	if ( callback ) {
		
		
			//	MOAIScopedLuaState state = callback.GetSelf ();  

				// push the start, length and string
				//state.Push ( 0 );
			//	state.Push ( strlen(ckeystring) );
			//	state.Push( ckeystring );

			//	state.DebugCall ( 3, 0 );

	
	}
}

//----------------------------------------------------------------//
void MOAIKeyboardWinPhone::NotifyTextDone ( ) {
	

	MOAILuaRef& callback = this->mListeners [ EVENT_RETURN ];
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf ();

		state.DebugCall ( 0, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIKeyboardWinPhone::PushText ( MOAILuaState& state ) {
			//state.Push(keystring);
}

void MOAIKeyboardWinPhone::ShowKeyboard(cc8* text, int type, int returnKey, bool secure, int autocap, int appearance) {

	auto view = Windows::ApplicationModel::Core::CoreApplication::GetCurrentView();
	//view->CoreWindow->GetForCurrentThread();

}


//----------------------------------------------------------------//
void MOAIKeyboardWinPhone::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "EVENT_INPUT",         ( u32 )EVENT_INPUT );
	state.SetField ( -1, "EVENT_RETURN",        ( u32 )EVENT_RETURN );

	luaL_Reg regTable [] = {
		{ "getText",        _getText },
		{ "setListener",    _setListener  },

		{ "showKeyboard",           _showKeyboard },
        { "showTextKeyboard",       _showTextKeyboard },
        { "showNumberKeyboard",     _showNumberKeyboard },
        { "showDateTimeKeyboard",   _showDateTimeKeyboard },
        { "showPhoneKeyboard",      _showPhoneKeyboard },

        { "hideKeyboard",   _hideKeyboard },
		{ "setText",      _setText },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

