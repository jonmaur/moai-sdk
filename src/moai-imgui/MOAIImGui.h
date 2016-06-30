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
	static int _TextColored(lua_State* L);
	static int _TextDisabled(lua_State* L);
	static int _TextWrapped(lua_State* L);
	static int _TextUnformatted(lua_State* L);
	static int _LabelText(lua_State* L);
	static int _Bullet(lua_State* L);
	static int _BulletText(lua_State* L);
	static int _Button(lua_State* L);
	static int _SmallButton(lua_State* L);
	static int _InvisibleButton(lua_State* L);
	// static int _Image(lua_State* L);
	// static int _ImageButton(lua_State* L);
	static int _Checkbox(lua_State* L);
	static int _RadioButton(lua_State* L);
	static int _Combo(lua_State* L);
	static int _ColorButton(lua_State* L);
	static int _ColorEdit3(lua_State* L);
	static int _ColorEdit4(lua_State* L);
	// static int _PlotLines(lua_State* L);
	// static int _PlotHistogram(lua_State* L);
	static int _ProgressBar(lua_State* L);

	static int _DragFloat(lua_State* L);
	static int _DragFloat2(lua_State* L);
	static int _DragFloat3(lua_State* L);
	static int _DragFloat4(lua_State* L);
	static int _DragFloatRange2(lua_State* L);
	static int _DragInt(lua_State* L);
	static int _DragInt2(lua_State* L);
	static int _DragInt3(lua_State* L);
	static int _DragInt4(lua_State* L);
	static int _DragIntRange2(lua_State* L);

	static int _InputText(lua_State* L);
	static int _InputFloat(lua_State* L);
	static int _InputFloat2(lua_State* L);
	static int _InputFloat3(lua_State* L);
	static int _InputFloat4(lua_State* L);

public:

	DECL_LUA_SINGLETON(MOAIImGui)

		//----------------------------------------------------------------//
							MOAIImGui();
							~MOAIImGui();
		void				RegisterLuaClass(MOAILuaState& state);

};

#endif
