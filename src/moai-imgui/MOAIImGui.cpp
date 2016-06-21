#include <moai-imgui/MOAIImGui.h>
#include <moai-imgui/MOAIImVec2.h>
#include <moai-imgui/MOAIImVec4.h>


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
		{ "TextColored",				_TextColored },
		{ "TextDisabled",				_TextDisabled },
		{ "TextWrapped",				_TextWrapped },
		{ "TextUnformatted",			_TextUnformatted },
		{ "LabelText",					_LabelText },
		{ "Bullet",						_Bullet },
		{ "BulletText",					_BulletText },
		{ "Button",						_Button },
		{ "SmallButton",				_SmallButton },
		{ "InvisibleButton",			_InvisibleButton },
		{ "Checkbox",					_Checkbox },
		{ "RadioButton",				_RadioButton },
		{ "Combo",						_Combo },
		{ "ColorButton",				_ColorButton },
		{ "ColorEdit3",					_ColorEdit3 },
		{ "ColorEdit4",					_ColorEdit4 },
		// { "PlotLines",					_PlotLines },
		// { "PlotHistogram",				_PlotHistogram },
		{ "ProgressBar",				_ProgressBar },
		{ "DragFloat",					_DragFloat },
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
//----------------------------------------------------------------//
/**	@lua	ShowTestWindow
@text	Show a test window for ImGui.

@in		string or number id
@opt	MOAIImVec2 size
@opt	boolean border		Default value is 'false.'
@opt	number extra_flags	Default value is 0
*/
int MOAIImGui::_BeginChild(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	MOAIImVec2 size;

	if (state.IsType(2, LUA_TUSERDATA))
	{
		size = *state.GetLuaObject<MOAIImVec2>(2, true);
	}

	bool border = state.GetValue<bool>(3, false);
	int extra_flags = state.GetValue<int>(4, 0);
	
	bool ret = false;
	
	if (state.IsType(1, LUA_TSTRING))
	{
		cc8* str_id = state.GetValue<cc8*>(1, "");

		ret = ImGui::BeginChild(str_id, size.mVec2, border, extra_flags);
	}
	else if (state.IsType(1, LUA_TNUMBER))
	{
		int id = state.GetValue<int>(1, 0);

		ret = ImGui::BeginChild(id, size.mVec2, border, extra_flags);
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
	@text	See ImGui. No point in using format strings here, construct the string in lua.

	@in		string txt
*/
int MOAIImGui::_Text(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* txt = state.GetValue < cc8* >(1, "");
	ImGui::Text(txt);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	TextColored
	@text	See ImGui. No point in using format strings here, construct the string in lua.

	@in MOAIImVec4		color
	@in	string 			txt
*/
int MOAIImGui::_TextColored(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "US");

	MOAIImVec4* color = state.GetLuaObject<MOAIImVec4>(1, true);
	cc8* txt = state.GetValue < cc8* >(2, "");

	ImGui::TextColored(color->mVec4, txt);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	TextDisabled
	@text	See ImGui. No point in using format strings here, construct the string in lua.

	@in	string 			txt
*/
int MOAIImGui::_TextDisabled(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* txt = state.GetValue < cc8* >(1, "");

	ImGui::TextDisabled(txt);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	TextWrapped
	@text	See ImGui. No point in using format strings here, construct the string in lua.

	@in	string 			txt
*/
int MOAIImGui::_TextWrapped(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* txt = state.GetValue < cc8* >(1, "");

	ImGui::TextWrapped(txt);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	TextUnformatted
	@text	See ImGui. No point in using format strings here, construct the string in lua.

	@in	string 			txt
*/
int MOAIImGui::_TextUnformatted(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	size_t len;
	const char *txt = lua_tolstring(L, 1, &len);
	
	ImGui::TextUnformatted(txt, txt+len);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	LabelText
	@text	See ImGui. No point in using format strings here, construct the string in lua.

	@in	string 			label
	@in	string 			txt
*/
int MOAIImGui::_LabelText(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SS");

	cc8* txt = state.GetValue < cc8* >(1, "");
	cc8* lbl = state.GetValue < cc8* >(2, "");

	ImGui::LabelText(txt, lbl);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	Bullet
	@text	See ImGui.
*/
int MOAIImGui::_Bullet(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::Bullet();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	BulletText
	@text	See ImGui. No point in using format strings here, construct the string in lua.

	@in	string 			txt
*/
int MOAIImGui::_BulletText(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* txt = state.GetValue < cc8* >(1, "");

	ImGui::BulletText(txt);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	Button
	@text	See ImGui. No point in using format strings here, construct the string in lua.

	@in		string 			lbl
	@opt 	MOAIImVec2		size
	@out	boolean			pressed
*/
int MOAIImGui::_Button(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* lbl = state.GetValue < cc8* >(1, "");
	
	MOAIImVec2 size;

	if (state.IsType(2, LUA_TUSERDATA))
	{
		size = *state.GetLuaObject<MOAIImVec2>(2, true);
	}

	bool ret = ImGui::Button(lbl, size.mVec2);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	SmallButton
	@text	See ImGui. No point in using format strings here, construct the string in lua.

	@in		string 			lbl
	@out	boolean			pressed
*/
int MOAIImGui::_SmallButton(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* lbl = state.GetValue < cc8* >(1, "");

	bool ret = ImGui::SmallButton(lbl);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	InvisibleButton
	@text	See ImGui. No point in using format strings here, construct the string in lua.

	@in		string 			id
	@in 	MOAIImVec2		size
	@out	boolean			pressed
*/
int MOAIImGui::_InvisibleButton(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* id = state.GetValue < cc8* >(1, "");
	
	MOAIImVec2* size = state.GetLuaObject<MOAIImVec2>(2, true);

	bool ret = ImGui::InvisibleButton(id, size->mVec2);
	state.Push(ret);

	return 1;
}

//Image(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0), const ImVec2& uv1 = ImVec2(1,1), const ImVec4& tint_col = ImVec4(1,1,1,1), const ImVec4& border_col = ImVec4(0,0,0,0));
//bool          ImageButton(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0),  const ImVec2& uv1 = ImVec2(1,1), int frame_padding = -1, const ImVec4& bg_col = ImVec4(0,0,0,0), const ImVec4& tint_col = ImVec4(1,1,1,1));    // <0 frame_padding uses default frame padding settings. 0 for no padding

//----------------------------------------------------------------//
/**	@lua	Checkbox
	@text	See ImGui.

	@in		string 			lbl
	@in		boolean			checked
	@out	boolean			pressed
	@out	boolean			checked
*/
int MOAIImGui::_Checkbox(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SB");

	cc8* lbl = state.GetValue < cc8* >(1, "");
	bool checked = state.GetValue < bool >(2, false);

	bool ret = ImGui::Checkbox(lbl, &checked);
	state.Push(checked);
	state.Push(ret);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	RadioButton
	@text	See ImGui.

	@in		string 			lbl
	@in		number			activebutton
	@in		number			buttonid
	@out	boolean			pressed
	@out	number			activebutton
*/
int MOAIImGui::_RadioButton(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SNN");

	cc8* lbl = state.GetValue < cc8* >(1, "");
	int activebutton = state.GetValue < int >(2, 0);
	int buttonid = state.GetValue < int >(3, 0);

	bool ret = ImGui::RadioButton(lbl, &activebutton, buttonid);
	state.Push(activebutton);
	state.Push(ret);

	return 2;
}

// item getter for Combo()
bool items_getter(void* data, int idx, const char** out_text)
{
	MOAILuaState* state = (MOAILuaState*)data;
	state->GetField ( 3, idx+1 );
	cc8* value = state->GetValue < cc8* >( -1, 0 );
	lua_pop ( *state, 1 );
	
	if ( value )
	{
		*out_text = value;
		return true;
	}

	return false;
}

//----------------------------------------------------------------//
/**	@lua	Combo
	@text	See ImGui.

	@in		string 			lbl
	@in		number			currentitem
	@in		table			items
	@opt	number			height
	@out	boolean			selected
	@out	number			currentitem
*/
int MOAIImGui::_Combo(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SNT");

	cc8* lbl = state.GetValue < cc8* >(1, "");
	int currentitem = state.GetValue < int >(2, 0);
	int numitems = (int)lua_objlen(L, 3);
	int height = state.GetValue < int >(4, -1);

	// lua array to c array translation
	--currentitem;
	bool ret = ImGui::Combo(lbl, &currentitem, items_getter, &state, numitems, height);
	state.Push(currentitem + 1); // c array to lua array translation
	state.Push(ret);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	ColorButton
	@text	See ImGui.

	@in 	MOAIImVec4		color
	@in		boolean			small_height
	@in		boolean			border
	@out	boolean			pressed
*/
int MOAIImGui::_ColorButton(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "U");

	MOAIImVec4* color = state.GetLuaObject<MOAIImVec4>(1, true);
	bool small_height = state.GetValue < bool >(2, false);
	bool border = state.GetValue < bool >(3, true);

	bool ret = ImGui::ColorButton(color->mVec4, small_height, border);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	ColorEdit3
	@text	See ImGui.

	@in		string			label
	@in 	MOAIImVec4		color
	@out	boolean			pressed
*/
int MOAIImGui::_ColorEdit3(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* lbl = state.GetValue < cc8* >(1, "");
	MOAIImVec4* color = state.GetLuaObject<MOAIImVec4>(2, true);

	bool ret = ImGui::ColorEdit3(lbl, &color->mVec4.x);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	ColorEdit4
	@text	See ImGui.

	@in		string			label
	@in 	MOAIImVec4		color
	@in		boolean			showalpha	Default value is 'false.'
	@out	boolean			pressed
*/
int MOAIImGui::_ColorEdit4(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* lbl = state.GetValue < cc8* >(1, "");
	MOAIImVec4* color = state.GetLuaObject<MOAIImVec4>(2, true);
	bool showalpha = state.GetValue < bool >(3, true);

	bool ret = ImGui::ColorEdit4(lbl, &color->mVec4.x, showalpha);
	state.Push(ret);

	return 1;
}

//void          PlotLines(const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0,0));

// void          PlotHistogram(const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0,0));


//----------------------------------------------------------------//
/**	@lua	ProgressBar
	@text	See ImGui.

	@in		number			fraction
	@opt 	MOAIImVec2		size
	@opt	string			overlay
*/
int MOAIImGui::_ProgressBar(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	float fraction = state.GetValue < float >(1, 0.0f);

	if (state.IsType(2, LUA_TUSERDATA))
	{
		MOAIImVec2* size = state.GetLuaObject<MOAIImVec2>(2, true);
		if (state.IsType(3, LUA_TSTRING))
		{
			cc8* overlay = state.GetValue < cc8* >(3, "");
			ImGui::ProgressBar(fraction, size->mVec2, overlay);
		}
		else
		{
			ImGui::ProgressBar(fraction, size->mVec2);
		}
	}
	else if (state.IsType(3, LUA_TSTRING))
	{
		cc8* overlay = state.GetValue < cc8* >(3, "");
		ImGui::ProgressBar(fraction, ImVec2(-1, 0), overlay);
	}
	else
	{
		ImGui::ProgressBar(fraction);
	}


	return 0;
}

//----------------------------------------------------------------//
/**	@lua	DragFloat
	@text	See ImGui.

	@in		string 			label
	@in		number			v
	@opt	number			speed
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@opt	number			power
	@out	boolean			pressed
	@out	number			currentv
*/
int MOAIImGui::_DragFloat(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SN");

	cc8* label = state.GetValue < cc8* >(1, "");
	float v = state.GetValue < float >(2, 0);
	float speed = state.GetValue < float >(3, 1.0f);
	float min = state.GetValue < float >(4, 0.0f);
	float max = state.GetValue < float >(5, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(6, "%.3f");
	float power = state.GetValue < float >(7, 1.0f);

	bool ret = ImGui::DragFloat(label, &v, speed, min, max, display_format, power);
	state.Push(v); // c array to lua array translation
	state.Push(ret);

	return 2;
}
