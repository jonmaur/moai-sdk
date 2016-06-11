#include <moai-imgui/MOAIImGui.h>
#include <moai-imgui/MOAIImVec2.h>


//----------------------------------------------------------------//
MOAIImGui::MOAIImGui() {

	RTTI_SINGLE(MOAILuaObject)
}

//----------------------------------------------------------------//
MOAIImGui::~MOAIImGui() {
}

void MOAIImGui::RegisterLuaClass(MOAILuaState& state) {

	// ImGuiWindowFlags enum
	state.SetField(-1, "ImGuiWindowFlags_NoTitleBar", 					1 << 0);   // Disable title-bar
	state.SetField(-1, "ImGuiWindowFlags_NoResize", 					1 << 1);   // Disable user resizing with the lower-right grip
	state.SetField(-1, "ImGuiWindowFlags_NoMove", 						1 << 2);   // Disable user moving the window
	state.SetField(-1, "ImGuiWindowFlags_NoScrollbar", 					1 << 3);   // Disable scrollbars (window can still scroll with mouse or programatically)
	state.SetField(-1, "ImGuiWindowFlags_NoScrollWithMouse", 			1 << 4);   // Disable user vertically scrolling with mouse wheel
	state.SetField(-1, "ImGuiWindowFlags_NoCollapse", 					1 << 5);   // Disable user collapsing window by double-clicking on it
	state.SetField(-1, "ImGuiWindowFlags_AlwaysAutoResize", 			1 << 6);   // Resize every window to its content every frame
	state.SetField(-1, "ImGuiWindowFlags_ShowBorders", 					1 << 7);   // Show borders around windows and items
	state.SetField(-1, "ImGuiWindowFlags_NoSavedSettings", 				1 << 8);   // Never load/save settings in .ini file
	state.SetField(-1, "ImGuiWindowFlags_NoInputs", 					1 << 9);   // Disable catching mouse or keyboard inputs
	state.SetField(-1, "ImGuiWindowFlags_MenuBar", 						1 << 10);  // Has a menu-bar
	state.SetField(-1, "ImGuiWindowFlags_HorizontalScrollbar", 			1 << 11);  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
	state.SetField(-1, "ImGuiWindowFlags_NoFocusOnAppearing", 			1 << 12);  // Disable taking focus when transitioning from hidden to visible state
	state.SetField(-1, "ImGuiWindowFlags_NoBringToFrontOnFocus", 		1 << 13);  // Disable bringing window to front when taking focus (e.g. clicking on it or programatically giving it focus)
	state.SetField(-1, "ImGuiWindowFlags_AlwaysVerticalScrollbar", 		1 << 14);  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
	state.SetField(-1, "ImGuiWindowFlags_AlwaysHorizontalScrollbar", 	1 << 15);  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
	state.SetField(-1, "ImGuiWindowFlags_AlwaysUseWindowPadding", 		1 << 16);  // Ensure child windows without border uses style.WindowPadding (ignored by default for non-bordered child windows, because more convenient)


	luaL_Reg regTable[] = {
		{ "ShowTestWindow",				_ShowTestWindow },
		{ "Begin",						_Begin },
		{ "End",						_End },
		{ "BeginChild",					_BeginChild },
		{ "EndChild",					_EndChild },
		{ "Text",						_Text },
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

//----------------------------------------------------------------//
/**	@lua	ShowTestWindow
	@text	Show a test window for ImGui.

	@in		MOAIAction self
	@opt	boolean show		Default value is 'true.'
	@out	boolean show
*/
int MOAIImGui::_ShowTestWindow(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool open = state.GetValue < bool >(1, true);

	ImGui::ShowTestWindow(&open);

	state.Push(open);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	Begin
	@text	See ImGui.

	@opt	string name
	@opt	boolean show
	@opt	number flags
	@out	boolean show
*/
int MOAIImGui::_Begin(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	cc8* name = state.GetValue < cc8* >(1, "MOAIImGui");
	bool open = state.GetValue < bool >(2, true);
	int flags = state.GetValue < ImGuiWindowFlags >(3, 0);

	bool ret = ImGui::Begin(name, &open, flags);

	state.Push(ret);
	state.Push(open);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	End
	@text	See ImGui.
*/
int MOAIImGui::_End(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::End();

	return 0;
}

//bool          BeginChild(const char* str_id, const ImVec2& size = ImVec2(0,0), bool border = false, ImGuiWindowFlags extra_flags = 0);    // begin a scrolling region. size==0.0f: use remaining window size, size<0.0f: use remaining window size minus abs(size). size>0.0f: fixed size. each axis can use a different mode, e.g. ImVec2(0,400).
//bool          BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0,0), bool border = false, ImGuiWindowFlags extra_flags = 0);            // "
int MOAIImGui::_BeginChild(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	MOAIImVec2* size = state.GetLuaObject<MOAIImVec2>(2, true);
	bool border = state.GetValue<bool>(3, false);
	int extra_flags = state.GetValue<int>(4, 0);
	
	bool ret = false;
	
	if (state.IsType(1, LUA_TSTRING))
	{
		cc8* str_id = state.GetValue<cc8*>(1, "");

		ret = ImGui::BeginChild(str_id, size->mVec2, border, extra_flags);
	}
	else if (state.IsType(1, LUA_TNUMBER))
	{
		int id = state.GetValue<int>(1, 0);

		ret = ImGui::BeginChild(id, size->mVec2, border, extra_flags);
	}
	else
	{
		// bad call
		MOAILogF(L, ZLLog::LOG_ERROR, MOAILogMessages::MOAI_ParamTypeMismatch_DSS, 1, "NUMBER or STRING", lua_type(L, 1));
	}

	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	EndChild
	@text	See ImGui.
*/
int MOAIImGui::_EndChild(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::EndChild();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	Text
	@text	See ImGui.

	@in		string txt
*/
int MOAIImGui::_Text(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* formatstr = state.GetValue < cc8* >(1, "");
	ImGui::Text(formatstr);

	return 0;
}
