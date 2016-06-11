#ifndef	MOAIIMGUI_H
#define	MOAIIMGUI_H

#include <moai-core/headers.h>
#include <imgui.h>

//================================================================//
// MOAIImGui
//================================================================//
/**	@lua	MOAIEaseType
@text	Namespace to hold ease modes. Moai ease in/out has opposite meaning of Flash ease in/out.

@const	EASE_IN							t ^ 4 - Fast start then slow when approaching value; ease into position.

*/
class MOAIImGui :
	public MOAIGlobalClass < MOAIImGui, MOAILuaObject > {
protected:

	static int _ShowTestWindow(lua_State* L);
	static int _Begin(lua_State* L);
	static int _End(lua_State* L);
	static int _BeginChild(lua_State* L);
	static int _EndChild(lua_State* L);
	static int _Text(lua_State* L);

public:

	DECL_LUA_SINGLETON(MOAIImGui)

		//----------------------------------------------------------------//
							MOAIImGui();
							~MOAIImGui();
		void				RegisterLuaClass(MOAILuaState& state);

};

#endif
