#ifndef MOAIDISPLAYSDL_H
#define MOAIDISPLAYSDL_H


#include <moai-core/headers.h>
#include <host-modules/aku_modules.h>
#include <SDL.h>

/**
 * Graphics functionality helper class; accessible from Lua as
 * MOAIDisplaySDL.
 *
 * @author	Jetha Chan
 * @date	14/09/2013
 */
class MOAIDisplaySDL : 
	public MOAIGlobalClass <MOAIDisplaySDL, MOAILuaObject> {
private:
	static SDL_Window*	m_window;

public:
	DECL_LUA_SINGLETON (MOAIDisplaySDL)

							MOAIDisplaySDL	(  );
							~MOAIDisplaySDL	(  );
	//----------------------------------------------------------------//
	void					RegisterLuaClass		( MOAILuaState& state );
	void					RegisterLuaFuncs		( MOAILuaState& state );
	static void				SetWindowHandle			( SDL_Window*	p_window );

private:
	static s32				DoGetScreenList			( lua_State* L );
	static s32				DoGetResolutionInfo		( lua_State* L );
	static s32				DoSetResolution			( lua_State* L );

};

#endif
