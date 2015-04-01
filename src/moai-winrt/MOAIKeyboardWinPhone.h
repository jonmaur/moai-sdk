// Copyright (c) 2012 allaboutapps.at. All Rights Reserved.
//
// Contributed to the MOAI project by Jay Vaughan, allaboutapps.at
//
// This file implements the MOAIKeyboardWinPhone object
// for user-input from the soft keyboard on Windows Phones
//
// http://getmoai.com
//

#ifndef MOAIKEYBOARDWINPHONE_H
#define MOAIKEYBOARDWINPHONE_H

#include <moai-core/headers.h>



//================================================================//
// MOAIKeyboardWinPhone
//================================================================//
/** @lua MOAIKeyboardWinPhone
  @text <p>Wrapper for the native keyboard on Windows Phone.  Compatible
  with the iOS methods.
*/

class MOAIKeyboardWinPhone :
	public MOAIGlobalClass < MOAIKeyboardWinPhone, MOAIGlobalEventSource > {

private:

	Windows::UI::Xaml::Controls::TextBox^ mTextField;
	//----------------------------------------------------------------//
	static int _getText              ( lua_State* L );

	static int _showKeyboard         ( lua_State* L );
	static int _showTextKeyboard     ( lua_State* L );
	static int _showNumberKeyboard   ( lua_State* L );
	static int _showDateTimeKeyboard ( lua_State* L );
	static int _showPhoneKeyboard    ( lua_State* L );

	static int _hideKeyboard         ( lua_State* L );
	static int _setListener          ( lua_State* L );
	static int _setText              ( lua_State* L );


	//----------------------------------------------------------------//
	void      ShowKeyboard      ( cc8* text, int type, int returnKey, bool secure, int autocap, int appearance );

public:

	DECL_LUA_SINGLETON ( MOAIKeyboardWinPhone )

	enum {
		EVENT_INPUT,
		EVENT_RETURN,
		TOTAL
	};

	MOAILuaStrongRef  mListeners [ TOTAL ];

	//----------------------------------------------------------------//
	void      Finish                ();
	          MOAIKeyboardWinPhone  ();
	          ~MOAIKeyboardWinPhone  ();
	void      RegisterLuaClass      ( MOAILuaState& state );

	void      PushText              ( MOAILuaState& state );
	void      NotifyKeyEvent		();
	void      NotifyTextDone		();

};

#endif
