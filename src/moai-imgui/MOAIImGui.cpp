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
	state.SetField(-1, "WindowFlags_NoTitleBar", 					1 << 0);   // Disable title-bar
	state.SetField(-1, "WindowFlags_NoResize", 						1 << 1);   // Disable user resizing with the lower-right grip
	state.SetField(-1, "WindowFlags_NoMove", 						1 << 2);   // Disable user moving the window
	state.SetField(-1, "WindowFlags_NoScrollbar", 					1 << 3);   // Disable scrollbars (window can still scroll with mouse or programatically)
	state.SetField(-1, "WindowFlags_NoScrollWithMouse", 			1 << 4);   // Disable user vertically scrolling with mouse wheel
	state.SetField(-1, "WindowFlags_NoCollapse", 					1 << 5);   // Disable user collapsing window by double-clicking on it
	state.SetField(-1, "WindowFlags_AlwaysAutoResize", 				1 << 6);   // Resize every window to its content every frame
	state.SetField(-1, "WindowFlags_ShowBorders", 					1 << 7);   // Show borders around windows and items
	state.SetField(-1, "WindowFlags_NoSavedSettings", 				1 << 8);   // Never load/save settings in .ini file
	state.SetField(-1, "WindowFlags_NoInputs", 						1 << 9);   // Disable catching mouse or keyboard inputs
	state.SetField(-1, "WindowFlags_MenuBar", 						1 << 10);  // Has a menu-bar
	state.SetField(-1, "WindowFlags_HorizontalScrollbar", 			1 << 11);  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
	state.SetField(-1, "WindowFlags_NoFocusOnAppearing", 			1 << 12);  // Disable taking focus when transitioning from hidden to visible state
	state.SetField(-1, "WindowFlags_NoBringToFrontOnFocus", 		1 << 13);  // Disable bringing window to front when taking focus (e.g. clicking on it or programatically giving it focus)
	state.SetField(-1, "WindowFlags_AlwaysVerticalScrollbar", 		1 << 14);  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
	state.SetField(-1, "WindowFlags_AlwaysHorizontalScrollbar", 	1 << 15);  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
	state.SetField(-1, "WindowFlags_AlwaysUseWindowPadding", 		1 << 16);  // Ensure child windows without border uses style.WindowPadding (ignored by default for non-bordered child windows, because more convenient)
	
	state.SetField(-1, "InputTextFlags_CharsDecimal",        	 	1 << 0);   // Allow 0123456789.+-*/
	state.SetField(-1, "InputTextFlags_CharsHexadecimal",    	 	1 << 1);   // Allow 0123456789ABCDEFabcdef
	state.SetField(-1, "InputTextFlags_CharsUppercase",      	 	1 << 2);   // Turn a..z into A..Z
	state.SetField(-1, "InputTextFlags_CharsNoBlank",        	 	1 << 3);   // Filter out spaces, tabs
	state.SetField(-1, "InputTextFlags_AutoSelectAll",       	 	1 << 4);   // Select entire text when first taking mouse focus
	state.SetField(-1, "InputTextFlags_EnterReturnsTrue",    	 	1 << 5);   // Return 'true' when Enter is pressed (as opposed to when the value was modified)
	state.SetField(-1, "InputTextFlags_CallbackCompletion",  	 	1 << 6);   // Call user function on pressing TAB (for completion handling)
	state.SetField(-1, "InputTextFlags_CallbackHistory",     	 	1 << 7);   // Call user function on pressing Up/Down arrows (for history handling)
	state.SetField(-1, "InputTextFlags_CallbackAlways",      	 	1 << 8);   // Call user function every time. User code may query cursor position, modify text buffer.
	state.SetField(-1, "InputTextFlags_CallbackCharFilter",  	 	1 << 9);   // Call user function to filter character. Modify data->EventChar to replace/filter input, or return 1 to discard character.
	state.SetField(-1, "InputTextFlags_AllowTabInput",       	 	1 << 10);  // Pressing TAB input a '\t' character into the text field
	state.SetField(-1, "InputTextFlags_CtrlEnterForNewLine", 	 	1 << 11);  // In multi-line mode, allow exiting edition by pressing Enter. Ctrl+Enter to add new line (by default adds new lines with Enter).
	state.SetField(-1, "InputTextFlags_NoHorizontalScroll",  	 	1 << 12);  // Disable following the cursor horizontally
	state.SetField(-1, "InputTextFlags_AlwaysInsertMode",    	 	1 << 13);  // Insert mode
	state.SetField(-1, "InputTextFlags_ReadOnly",            	 	1 << 14);  // Read-only mode
	state.SetField(-1, "InputTextFlags_Password",            	 	1 << 15);  // Password mode, display all characters as '*'

	state.SetField(-1, "SetCond_Always",        1 << 0);	// Set the variable
	state.SetField(-1, "SetCond_Once",          1 << 1);	// Only set the variable on the first call per runtime session
	state.SetField(-1, "SetCond_FirstUseEver",  1 << 2);	// Only set the variable if the window doesn't exist in the .ini file
	state.SetField(-1, "SetCond_Appearing",     1 << 3);	// Only set the variable if the window is appearing after being inactive (or the first time)

	state.SetField(-1, "TreeNodeFlags_Selected",             1 << 0);   // Draw as selected
	state.SetField(-1, "TreeNodeFlags_Framed",               1 << 1);   // Full colored frame (e.g. for CollapsingHeader)
	state.SetField(-1, "TreeNodeFlags_AllowOverlapMode",     1 << 2);   // Hit testing to allow subsequent widgets to overlap this one
	state.SetField(-1, "TreeNodeFlags_NoTreePushOnOpen",     1 << 3);   // Don't do a TreePush() when open (e.g. for CollapsingHeader) = no extra indent nor pushing on ID stack
	state.SetField(-1, "TreeNodeFlags_NoAutoOpenOnLog",      1 << 4);   // Don't automatically and temporarily open node when Logging is active (by default logging will automatically open tree nodes)
	state.SetField(-1, "TreeNodeFlags_DefaultOpen",          1 << 5);   // Default node to be open
	state.SetField(-1, "TreeNodeFlags_OpenOnDoubleClick",    1 << 6);   // Need double-click to open node
	state.SetField(-1, "TreeNodeFlags_OpenOnArrow",          1 << 7);   // Only open when clicking on the arrow part. If ImGuiTreeNodeFlags_OpenOnDoubleClick is also set, single-click arrow or double-click all box to open.
	state.SetField(-1, "TreeNodeFlags_AlwaysOpen",           1 << 8);   // No collapsing, no arrow (use as a convenience for leaf nodes). 
	state.SetField(-1, "TreeNodeFlags_CollapsingHeader",     ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoAutoOpenOnLog);

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
		{ "DragFloat2",					_DragFloat2 },
		{ "DragFloat3",					_DragFloat3 },
		{ "DragFloat4",					_DragFloat4 },
		{ "DragFloatRange2",			_DragFloatRange2 },
		{ "DragInt",					_DragInt },
		{ "DragInt2",					_DragInt2 },
		{ "DragInt3",					_DragInt3 },
		{ "DragInt4",					_DragInt4 },
		{ "DragIntRange2",				_DragIntRange2 },

		{ "InputText",					_InputText },
		{ "InputFloat",					_InputFloat },
		{ "InputFloat2",				_InputFloat2 },
		{ "InputFloat3",				_InputFloat3 },
		{ "InputFloat4",				_InputFloat4 },
		{ "InputInt",					_InputInt },
		{ "InputInt2",					_InputInt2 },
		{ "InputInt3",					_InputInt3 },
		{ "InputInt4",					_InputInt4 },

		{ "SliderFloat",				_SliderFloat },
		{ "SliderFloat2",				_SliderFloat2 },
		{ "SliderFloat3",				_SliderFloat3 },
		{ "SliderFloat4",				_SliderFloat4 },
		{ "SliderAngle",				_SliderAngle },
		{ "SliderInt",					_SliderInt },
		{ "SliderInt2",					_SliderInt2 },
		{ "SliderInt3",					_SliderInt3 },
		{ "SliderInt4",					_SliderInt4 },
		{ "VSliderFloat",				_VSliderFloat },
		{ "VSliderInt",					_VSliderInt },
		
		{ "TreeNode",					_TreeNode },
		{ "TreeNodeEx",					_TreeNodeEx },
		{ "TreePop",					_TreePop },
		{ "TreePush",					_TreePush },
		{ "SetNextTreeNodeOpen",		_SetNextTreeNodeOpen },
		{ "GetTreeNodeToLabelSpacing",			_GetTreeNodeToLabelSpacing },
		{ "CollapsingHeader",			_CollapsingHeader },
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
	state.Push(v);
	state.Push(ret);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	DragFloat2
	@text	See ImGui.

	@in		string 			label
	@in		ImVec2			v
	@opt	number			speed
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@opt	number			power
	@out	boolean			pressed
*/
int MOAIImGui::_DragFloat2(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec2* v = state.GetLuaObject<MOAIImVec2>(2, true);
	float speed = state.GetValue < float >(3, 1.0f);
	float min = state.GetValue < float >(4, 0.0f);
	float max = state.GetValue < float >(5, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(6, "%.3f");
	float power = state.GetValue < float >(7, 1.0f);

	bool ret = ImGui::DragFloat2(label, &v->mVec2.x, speed, min, max, display_format, power);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	DragFloat3
	@text	See ImGui.

	@in		string 			label
	@in		ImVec4			v
	@opt	number			speed
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@opt	number			power
	@out	boolean			pressed
*/
int MOAIImGui::_DragFloat3(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec4* v = state.GetLuaObject<MOAIImVec4>(2, true);
	float speed = state.GetValue < float >(3, 1.0f);
	float min = state.GetValue < float >(4, 0.0f);
	float max = state.GetValue < float >(5, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(6, "%.3f");
	float power = state.GetValue < float >(7, 1.0f);

	bool ret = ImGui::DragFloat3(label, &v->mVec4.x, speed, min, max, display_format, power);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	DragFloat4
	@text	See ImGui.

	@in		string 			label
	@in		ImVec4			v
	@opt	number			speed
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@opt	number			power
	@out	boolean			pressed
*/
int MOAIImGui::_DragFloat4(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec4* v = state.GetLuaObject<MOAIImVec4>(2, true);
	float speed = state.GetValue < float >(3, 1.0f);
	float min = state.GetValue < float >(4, 0.0f);
	float max = state.GetValue < float >(5, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(6, "%.3f");
	float power = state.GetValue < float >(7, 1.0f);

	bool ret = ImGui::DragFloat4(label, &v->mVec4.x, speed, min, max, display_format, power);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	DragFloatRange2
	@text	See ImGui.

	@in		string 			label
	@in		number			v_min
	@in		number			v_max
	@opt	number			speed
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@opt	number			power
	@out	boolean			pressed
	@out	number			current_max
	@out	number			current_min
*/
int MOAIImGui::_DragFloatRange2(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SN");

	cc8* label = state.GetValue < cc8* >(1, "");
	float v_min = state.GetValue < float >(2, 0);
	float v_max = state.GetValue < float >(3, 0);
	float speed = state.GetValue < float >(4, 1.0f);
	float min = state.GetValue < float >(5, 0.0f);
	float max = state.GetValue < float >(6, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(7, "%.3f");
	cc8* display_format_max = state.GetValue < cc8* >(8, display_format);
	float power = state.GetValue < float >(9, 1.0f);

	bool ret = ImGui::DragFloatRange2(label, &v_min, &v_max, speed, min, max, display_format, display_format_max, power);
	state.Push(v_min);
	state.Push(v_max);
	state.Push(ret);

	return 3;
}

//----------------------------------------------------------------//
/**	@lua	DragInt
	@text	See ImGui.

	@in		string 			label
	@in		number			v
	@opt	number			speed
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@out	boolean			pressed
	@out	number			currentv
*/
int MOAIImGui::_DragInt(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SN");

	cc8* label = state.GetValue < cc8* >(1, "");
	int v = state.GetValue < int >(2, 0);
	float speed = state.GetValue < float >(3, 1.0f);
	int min = state.GetValue < int >(4, 0);
	int max = state.GetValue < int >(5, 0);
	cc8* display_format = state.GetValue < cc8* >(6, "%.0f");

	bool ret = ImGui::DragInt(label, &v, speed, min, max, display_format);
	state.Push(v);
	state.Push(ret);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	DragInt2
	@text	See ImGui.

	@in		string 			label
	@in		ImVec2			v
	@opt	number			speed
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@out	boolean			pressed
*/
int MOAIImGui::_DragInt2(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec2* v = state.GetLuaObject<MOAIImVec2>(2, true);
	float speed = state.GetValue < float >(3, 1.0f);
	int min = state.GetValue < int >(4, 0);
	int max = state.GetValue < int >(5, 0);
	cc8* display_format = state.GetValue < cc8* >(6, "%.0f");

	int integers[2];
	integers[0] = (int)v->mVec2.x;
	integers[1] = (int)v->mVec2.y;
	bool ret = ImGui::DragInt2(label, integers, speed, min, max, display_format);
	state.Push(ret);

	v->mVec2.x = (float)integers[0];
	v->mVec2.y = (float)integers[1];

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	DragInt3
	@text	See ImGui.

	@in		string 			label
	@in		ImVec4			v
	@opt	number			speed
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@out	boolean			pressed
*/
int MOAIImGui::_DragInt3(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec4* v = state.GetLuaObject<MOAIImVec4>(2, true);
	float speed = state.GetValue < float >(3, 1.0f);
	int min = state.GetValue < int >(4, 0);
	int max = state.GetValue < int >(5, 0);
	cc8* display_format = state.GetValue < cc8* >(6, "%.0f");

	int integers[3];
	integers[0] = (int)v->mVec4.x;
	integers[1] = (int)v->mVec4.y;
	integers[2] = (int)v->mVec4.z;
	bool ret = ImGui::DragInt3(label, integers, speed, min, max, display_format);
	state.Push(ret);

	v->mVec4.x = (float)integers[0];
	v->mVec4.y = (float)integers[1];
	v->mVec4.z = (float)integers[2];

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	DragInt4
	@text	See ImGui.

	@in		string 			label
	@in		ImVec4			v
	@opt	number			speed
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@out	boolean			pressed
*/
int MOAIImGui::_DragInt4(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec4* v = state.GetLuaObject<MOAIImVec4>(2, true);
	float speed = state.GetValue < float >(3, 1.0f);
	int min = state.GetValue < int >(4, 0);
	int max = state.GetValue < int >(5, 0);
	cc8* display_format = state.GetValue < cc8* >(6, "%.0f");

	int integers[4];
	integers[0] = (int)v->mVec4.x;
	integers[1] = (int)v->mVec4.y;
	integers[2] = (int)v->mVec4.z;
	integers[3] = (int)v->mVec4.w;
	bool ret = ImGui::DragInt4(label, integers, speed, min, max, display_format);
	state.Push(ret);

	v->mVec4.x = (float)integers[0];
	v->mVec4.y = (float)integers[1];
	v->mVec4.z = (float)integers[2];
	v->mVec4.w = (float)integers[3];
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	DragIntRange2
	@text	See ImGui.

	@in		string 			label
	@in		number			v_min
	@in		number			v_max
	@opt	number			speed
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@out	boolean			pressed
	@out	number			current_max
	@out	number			current_min
*/
int MOAIImGui::_DragIntRange2(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SN");

	cc8* label = state.GetValue < cc8* >(1, "");
	int v_min = state.GetValue < int >(2, 0);
	int v_max = state.GetValue < int >(3, 0);
	float speed = state.GetValue < float >(4, 1.0f);
	int min = state.GetValue < int >(5, 0);
	int max = state.GetValue < int >(6, 0);
	cc8* display_format = state.GetValue < cc8* >(7, "%.0f");
	cc8* display_format_max = state.GetValue < cc8* >(8, display_format);

	bool ret = ImGui::DragIntRange2(label, &v_min, &v_max, speed, min, max, display_format, display_format_max);
	state.Push(v_min);
	state.Push(v_max);
	state.Push(ret);

	return 3;
}

//----------------------------------------------------------------//
/**	@lua	InputText
	@text	See ImGui. buf_size defaults to 1024. callback not supported. 
	user_data not needed. 

	@in		string 			label
	@in		string 			buf
	@opt	number			buf_size (max)
	@opt	number			flags
	@out	boolean			pressed
	@out	string 			buf
*/
int MOAIImGui::_InputText(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SS");

	cc8* label = state.GetValue < cc8* >(1, "");
	cc8* buf = state.GetValue < cc8* >(2, "");
	int buf_size = state.GetValue < int >(3, 1024);
	int flags = state.GetValue < int >(4, 0);

	char* temp = (char*)alloca(buf_size);
	strncpy(temp, buf, buf_size);

	bool ret = ImGui::InputText(label, temp, buf_size, flags);
	state.Push(temp);
	state.Push(ret);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	InputFloat
	@text	See ImGui.

	@in		string 			label
	@in		number 			v
	@opt	number			step
	@opt	number			step_fast
	@opt	number			decimal_precision
	@opt	number			extra_flags
	@out	boolean			pressed
	@out	number 			value
*/
int MOAIImGui::_InputFloat(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SN");

	cc8* label = state.GetValue < cc8* >(1, "");
	float v = state.GetValue < float >(2, 0.0f);
	float step = state.GetValue < float >(3, 0.0f);
	float step_fast = state.GetValue < float >(4, 0.0f);
	int decimal_precision = state.GetValue < int >(5, -1);
	int extra_flags = state.GetValue < int >(6, 0);

	bool ret = ImGui::InputFloat(label, &v, step, step_fast, decimal_precision, extra_flags);
	state.Push(v);
	state.Push(ret);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	InputFloat2
	@text	See ImGui.

	@in		string 			label
	@in		ImVec2			v
	@opt	number			decimal_precision
	@opt	number			extra_flags
	@out	boolean			pressed
*/
int MOAIImGui::_InputFloat2(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec2* v = state.GetLuaObject<MOAIImVec2>(2, true);
	int decimal_precision = state.GetValue < int >(3, -1);
	int extra_flags = state.GetValue < int >(4, 0);
	
	bool ret = ImGui::InputFloat2(label, &v->mVec2.x, decimal_precision, extra_flags);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	InputFloat3
@text	See ImGui.

@in		string 			label
@in		ImVec4			v
@opt	number			decimal_precision
@opt	number			extra_flags
@out	boolean			pressed
*/
int MOAIImGui::_InputFloat3(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec4* v = state.GetLuaObject<MOAIImVec4>(2, true);
	int decimal_precision = state.GetValue < int >(3, -1);
	int extra_flags = state.GetValue < int >(4, 0);

	bool ret = ImGui::InputFloat3(label, &v->mVec4.x, decimal_precision, extra_flags);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	InputFloat4
@text	See ImGui.

@in		string 			label
@in		ImVec4			v
@opt	number			decimal_precision
@opt	number			extra_flags
@out	boolean			pressed
*/
int MOAIImGui::_InputFloat4(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec4* v = state.GetLuaObject<MOAIImVec4>(2, true);
	int decimal_precision = state.GetValue < int >(3, -1);
	int extra_flags = state.GetValue < int >(4, 0);

	bool ret = ImGui::InputFloat4(label, &v->mVec4.x, decimal_precision, extra_flags);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	InputInt
	@text	See ImGui.

	@in		string 			label
	@in		number 			v
	@opt	number			step
	@opt	number			step_fast
	@opt	number			extra_flags
	@out	boolean			pressed
	@out	number 			value
*/
int MOAIImGui::_InputInt(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SN");

	cc8* label = state.GetValue < cc8* >(1, "");
	int v = state.GetValue < int >(2, 0);
	int step = state.GetValue < int >(3, 1);
	int step_fast = state.GetValue < int >(4, 100);
	int extra_flags = state.GetValue < int >(5, 0);

	bool ret = ImGui::InputInt(label, &v, step, step_fast, extra_flags);
	state.Push(v);
	state.Push(ret);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	InputInt2
	@text	See ImGui.

	@in		string 			label
	@in		ImVec2			v
	@opt	number			extra_flags
	@out	boolean			pressed
*/
int MOAIImGui::_InputInt2(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec2* v = state.GetLuaObject<MOAIImVec2>(2, true);
	int extra_flags = state.GetValue < int >(3, 0);
	
	int integers[2];
	integers[0] = (int)v->mVec2.x;
	integers[1] = (int)v->mVec2.y;
	bool ret = ImGui::InputInt2(label, integers, extra_flags);
	state.Push(ret);

	v->mVec2.x = (float)integers[0];
	v->mVec2.y = (float)integers[1];

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	InputInt3
	@text	See ImGui.

	@in		string 			label
	@in		ImVec4			v
	@opt	number			extra_flags
	@out	boolean			pressed
*/
int MOAIImGui::_InputInt3(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec4* v = state.GetLuaObject<MOAIImVec4>(2, true);
	int extra_flags = state.GetValue < int >(3, 0);
	
	int integers[3];
	integers[0] = (int)v->mVec4.x;
	integers[1] = (int)v->mVec4.y;
	integers[2] = (int)v->mVec4.z;
	bool ret = ImGui::InputInt3(label, integers, extra_flags);
	state.Push(ret);

	v->mVec4.x = (float)integers[0];
	v->mVec4.y = (float)integers[1];
	v->mVec4.z = (float)integers[2];

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	InputInt4
	@text	See ImGui.

	@in		string 			label
	@in		ImVec4			v
	@opt	number			extra_flags
	@out	boolean			pressed
*/
int MOAIImGui::_InputInt4(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec4* v = state.GetLuaObject<MOAIImVec4>(2, true);
	int extra_flags = state.GetValue < int >(3, 0);
	
	int integers[4];
	integers[0] = (int)v->mVec4.x;
	integers[1] = (int)v->mVec4.y;
	integers[2] = (int)v->mVec4.z;
	integers[3] = (int)v->mVec4.w;
	bool ret = ImGui::InputInt4(label, integers, extra_flags);
	state.Push(ret);

	v->mVec4.x = (float)integers[0];
	v->mVec4.y = (float)integers[1];
	v->mVec4.z = (float)integers[2];
	v->mVec4.w = (float)integers[3];

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	SliderFloat
	@text	See ImGui.

	@in		string 			label
	@in		number			v
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@opt	number			power
	@out	boolean			pressed
	@out	number			v
*/
int MOAIImGui::_SliderFloat(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SN");

	cc8* label = state.GetValue < cc8* >(1, "");
	float v = state.GetValue < float >(2, 0);
	float min = state.GetValue < float >(3, 0.0f);
	float max = state.GetValue < float >(4, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(5, "%.3f");
	float power = state.GetValue < float >(6, 1.0f);

	bool ret = ImGui::SliderFloat(label, &v, min, max, display_format, power);
	state.Push(v);
	state.Push(ret);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	SliderFloat2
	@text	See ImGui.

	@in		string 			label
	@in		ImVec2			v
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@opt	number			power
	@out	boolean			pressed
*/
int MOAIImGui::_SliderFloat2(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec2* v = state.GetLuaObject<MOAIImVec2>(2, true);
	float min = state.GetValue < float >(3, 0.0f);
	float max = state.GetValue < float >(4, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(5, "%.3f");
	float power = state.GetValue < float >(6, 1.0f);

	bool ret = ImGui::SliderFloat2(label, &v->mVec2.x, min, max, display_format, power);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	SliderFloat3
	@text	See ImGui.

	@in		string 			label
	@in		ImVec4			v
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@opt	number			power
	@out	boolean			pressed
*/
int MOAIImGui::_SliderFloat3(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec4* v = state.GetLuaObject<MOAIImVec4>(2, true);
	float min = state.GetValue < float >(3, 0.0f);
	float max = state.GetValue < float >(4, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(5, "%.3f");
	float power = state.GetValue < float >(6, 1.0f);

	bool ret = ImGui::SliderFloat3(label, &v->mVec4.x, min, max, display_format, power);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	SliderFloat4
	@text	See ImGui.

	@in		string 			label
	@in		ImVec4			v
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@opt	number			power
	@out	boolean			pressed
*/
int MOAIImGui::_SliderFloat4(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec4* v = state.GetLuaObject<MOAIImVec4>(2, true);
	float min = state.GetValue < float >(3, 0.0f);
	float max = state.GetValue < float >(4, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(5, "%.3f");
	float power = state.GetValue < float >(6, 1.0f);

	bool ret = ImGui::SliderFloat4(label, &v->mVec4.x, min, max, display_format, power);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	SliderAngle
	@text	See ImGui.

	@in		string 			label
	@in		number			v_rad
	@opt	number			v_degrees_min
	@opt	number			v_degrees_max
	@out	boolean			pressed
	@out	number			v_rad
*/
int MOAIImGui::_SliderAngle(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SN");

	cc8* label = state.GetValue < cc8* >(1, "");
	float v_rad = state.GetValue < float >(2, 0);
	float v_degrees_min = state.GetValue < float >(3, -360.0f);
	float v_degrees_max = state.GetValue < float >(4, 360.0f);

	bool ret = ImGui::SliderAngle(label, &v_rad, v_degrees_min, v_degrees_max);
	state.Push(v_rad);
	state.Push(ret);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	SliderInt
	@text	See ImGui.

	@in		string 			label
	@in		number			v
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@out	boolean			pressed
	@out	number			currentv
*/
int MOAIImGui::_SliderInt(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SN");

	cc8* label = state.GetValue < cc8* >(1, "");
	int v = state.GetValue < int >(2, 0);
	int min = state.GetValue < int >(3, 0);
	int max = state.GetValue < int >(4, 0);
	cc8* display_format = state.GetValue < cc8* >(5, "%.0f");

	bool ret = ImGui::SliderInt(label, &v, min, max, display_format);
	state.Push(v);
	state.Push(ret);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	SliderInt2
	@text	See ImGui.

	@in		string 			label
	@in		ImVec2			v
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@out	boolean			pressed
*/
int MOAIImGui::_SliderInt2(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec2* v = state.GetLuaObject<MOAIImVec2>(2, true);
	int min = state.GetValue < int >(3, 0);
	int max = state.GetValue < int >(4, 0);
	cc8* display_format = state.GetValue < cc8* >(5, "%.0f");

	int integers[2];
	integers[0] = (int)v->mVec2.x;
	integers[1] = (int)v->mVec2.y;
	bool ret = ImGui::SliderInt2(label, integers, min, max, display_format);
	state.Push(ret);

	v->mVec2.x = (float)integers[0];
	v->mVec2.y = (float)integers[1];

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	SliderInt3
	@text	See ImGui.

	@in		string 			label
	@in		ImVec4			v
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@out	boolean			pressed
*/
int MOAIImGui::_SliderInt3(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec4* v = state.GetLuaObject<MOAIImVec4>(2, true);
	int min = state.GetValue < int >(3, 0);
	int max = state.GetValue < int >(4, 0);
	cc8* display_format = state.GetValue < cc8* >(5, "%.0f");

	int integers[3];
	integers[0] = (int)v->mVec4.x;
	integers[1] = (int)v->mVec4.y;
	integers[2] = (int)v->mVec4.z;
	bool ret = ImGui::SliderInt3(label, integers, min, max, display_format);
	state.Push(ret);

	v->mVec4.x = (float)integers[0];
	v->mVec4.y = (float)integers[1];
	v->mVec4.z = (float)integers[2];

	return 1;
}

bool          SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* display_format = "%.0f");
//----------------------------------------------------------------//
/**	@lua	SliderInt4
	@text	See ImGui.

	@in		string 			label
	@in		ImVec4			v
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@out	boolean			pressed
*/
int MOAIImGui::_SliderInt4(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SU");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec4* v = state.GetLuaObject<MOAIImVec4>(2, true);
	int min = state.GetValue < int >(3, 0);
	int max = state.GetValue < int >(4, 0);
	cc8* display_format = state.GetValue < cc8* >(5, "%.0f");

	int integers[4];
	integers[0] = (int)v->mVec4.x;
	integers[1] = (int)v->mVec4.y;
	integers[2] = (int)v->mVec4.z;
	integers[3] = (int)v->mVec4.w;
	bool ret = ImGui::SliderInt4(label, integers, min, max, display_format);
	state.Push(ret);

	v->mVec4.x = (float)integers[0];
	v->mVec4.y = (float)integers[1];
	v->mVec4.z = (float)integers[2];
	v->mVec4.w = (float)integers[3];
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	VSliderFloat
	@text	See ImGui.

	@in		string 			label
	@in		ImVec2			size
	@in		number			v
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@opt	number			power
	@out	boolean			pressed
	@out	number			v
*/
int MOAIImGui::_VSliderFloat(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SUN");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec2* size = state.GetLuaObject<MOAIImVec2>(2, true);
	float v = state.GetValue < float >(3, 0);
	float min = state.GetValue < float >(4, 0.0f);
	float max = state.GetValue < float >(5, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(6, "%.3f");
	float power = state.GetValue < float >(7, 1.0f);

	bool ret = ImGui::VSliderFloat(label, size->mVec2, &v, min, max, display_format, power);
	state.Push(v);
	state.Push(ret);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	VSliderInt
	@text	See ImGui.

	@in		string 			label
	@in		ImVec2			size
	@in		number			v
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@out	boolean			pressed
	@out	number			currentv
*/
int MOAIImGui::_VSliderInt(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SUN");

	cc8* label = state.GetValue < cc8* >(1, "");
	MOAIImVec2* size = state.GetLuaObject<MOAIImVec2>(2, true);
	int v = state.GetValue < int >(3, 0);
	int min = state.GetValue < int >(4, 0);
	int max = state.GetValue < int >(5, 0);
	cc8* display_format = state.GetValue < cc8* >(6, "%.0f");

	bool ret = ImGui::VSliderInt(label, size->mVec2, &v, min, max, display_format);
	state.Push(v);
	state.Push(ret);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	TreeNode
	@text	See ImGui.

	@in		string id
	@opt	string txt
	@out	boolean			open
*/
int MOAIImGui::_TreeNode(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* id = state.GetValue < cc8* >(1, "");
	cc8* txt = state.GetValue < cc8* >(2, id);
	bool ret = ImGui::TreeNode(id, txt);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	TreeNodeEx
	@text	See ImGui. No point in using format strings here, construct the string in lua.

	@in		string 		id
	@in		number		flags
	@opt	string 		txt
	@out	boolean		open
*/
int MOAIImGui::_TreeNodeEx(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SN");

	cc8* id = state.GetValue < cc8* >(1, "");
	int flags = state.GetValue < int >(2, 0);
	cc8* txt = state.GetValue < cc8* >(3, id);
	
	bool ret = ImGui::TreeNodeEx(id, flags, txt);

	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	TreePop
	@text	See ImGui. No point in using format strings here, construct the string in lua.

*/
int MOAIImGui::_TreePop(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::TreePop();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	TreePush
	@text	See ImGui.

	@in		string 		id
*/
int MOAIImGui::_TreePush(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	cc8* id = state.GetValue < cc8* >(1, "");
	ImGui::TreePush(id);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetNextTreeNodeOpen
	@text	See ImGui.

	@in		boolean 	is_open
	@opt	number		cond
*/
int MOAIImGui::_SetNextTreeNodeOpen(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "B");

	bool is_open = state.GetValue < bool >(1, true);
	int cond = state.GetValue < int >(2, 0);

	ImGui::SetNextTreeNodeOpen(is_open, cond);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	GetTreeNodeToLabelSpacing
	@text	See ImGui.

	@opt	number	 	flags
	@out	number		spacing
*/
int MOAIImGui::_GetTreeNodeToLabelSpacing(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	int flags = state.GetValue < int >(1, 0);

	float ret = ImGui::GetTreeNodeToLabelSpacing(flags);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	CollapsingHeader
	@text	See ImGui.

	@in		string	 	label
	@opt 	boolean		p_open
	@opt	number	 	flags
	@out	number		spacing
*/
int MOAIImGui::_CollapsingHeader(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* label = state.GetValue < cc8* >(1, "");

	if (state.IsType(2, LUA_TNUMBER))
	{
		int flags = state.GetValue < int >(2, 0);
		bool ret = ImGui::CollapsingHeader(label, flags);
		state.Push(ret);

		return 1;
	}
	else if (state.IsType(2, LUA_TBOOLEAN))
	{
		bool p_open = state.GetValue < bool >(2, false);
		int flags = state.GetValue < int >(3, 0);
		bool ret = ImGui::CollapsingHeader(label, &p_open, flags);
		state.Push(p_open);
		state.Push(ret);

		return 2;
	}
		
	bool ret = ImGui::CollapsingHeader(label);
	state.Push(ret);

	return 1;
}
