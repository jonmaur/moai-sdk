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

	state.SetField(-1, "TreeNodeFlags_Selected",             		1 << 0);   // Draw as selected
	state.SetField(-1, "TreeNodeFlags_Framed",               		1 << 1);   // Full colored frame (e.g. for CollapsingHeader)
	state.SetField(-1, "TreeNodeFlags_AllowOverlapMode",     		1 << 2);   // Hit testing to allow subsequent widgets to overlap this one
	state.SetField(-1, "TreeNodeFlags_NoTreePushOnOpen",     		1 << 3);   // Don't do a TreePush() when open (e.g. for CollapsingHeader) = no extra indent nor pushing on ID stack
	state.SetField(-1, "TreeNodeFlags_NoAutoOpenOnLog",      		1 << 4);   // Don't automatically and temporarily open node when Logging is active (by default logging will automatically open tree nodes)
	state.SetField(-1, "TreeNodeFlags_DefaultOpen",          		1 << 5);   // Default node to be open
	state.SetField(-1, "TreeNodeFlags_OpenOnDoubleClick",    		1 << 6);   // Need double-click to open node
	state.SetField(-1, "TreeNodeFlags_OpenOnArrow",          		1 << 7);   // Only open when clicking on the arrow part. If ImGuiTreeNodeFlags_OpenOnDoubleClick is also set, single-click arrow or double-click all box to open.
	state.SetField(-1, "TreeNodeFlags_AlwaysOpen",           		1 << 8);   // No collapsing, no arrow (use as a convenience for leaf nodes). 
	state.SetField(-1, "TreeNodeFlags_CollapsingHeader",     		ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoAutoOpenOnLog);

	state.SetField(-1, "SelectableFlags_DontClosePopups",			1 << 0);   // Clicking this don't close parent popup window
	state.SetField(-1, "SelectableFlags_SpanAllColumns",			1 << 1);   // Selectable frame can span all columns (text will still fit in current column)
	state.SetField(-1, "SelectableFlags_AllowDoubleClick",			1 << 2);   // Generate press events on double clicks too

	state.SetField(-1, "Key_Tab",									0);
	state.SetField(-1, "Key_LeftArrow",								1);
	state.SetField(-1, "Key_RightArrow",							2);
	state.SetField(-1, "Key_UpArrow",								3);
	state.SetField(-1, "Key_DownArrow",								4);
	state.SetField(-1, "Key_PageUp",								5);
	state.SetField(-1, "Key_PageDown",								6);
	state.SetField(-1, "Key_Home",									7);
	state.SetField(-1, "Key_End",									8);
	state.SetField(-1, "Key_Delete",								9);
	state.SetField(-1, "Key_Backspace",								10);
	state.SetField(-1, "Key_Enter",									11);
	state.SetField(-1, "Key_Escape",								12);
	state.SetField(-1, "Key_A",										13);
	state.SetField(-1, "Key_C",										14);
	state.SetField(-1, "Key_V",										15);
	state.SetField(-1, "Key_X",										16);
	state.SetField(-1, "Key_Y",										17);
	state.SetField(-1, "Key_Z",										18);

	state.SetField(-1, "Col_Text",									0);
	state.SetField(-1, "Col_TextDisabled",							1);
	state.SetField(-1, "Col_WindowBg",								2);
	state.SetField(-1, "Col_ChildWindowBg",							3);
	state.SetField(-1, "Col_PopupBg",								4);
	state.SetField(-1, "Col_Border",								5);
	state.SetField(-1, "Col_BorderShadow",							6);
	state.SetField(-1, "Col_FrameBg",								7);
	state.SetField(-1, "Col_FrameBgHovered",						8);
	state.SetField(-1, "Col_FrameBgActive",							9);
	state.SetField(-1, "Col_TitleBg",								10);
	state.SetField(-1, "Col_TitleBgCollapsed",						11);
	state.SetField(-1, "Col_TitleBgActive",							12);
	state.SetField(-1, "Col_MenuBarBg",								13);
	state.SetField(-1, "Col_ScrollbarBg",							14);
	state.SetField(-1, "Col_ScrollbarGrab",							15);
	state.SetField(-1, "Col_ScrollbarGrabHovered",					16);
	state.SetField(-1, "Col_ScrollbarGrabActive",					17);	
	state.SetField(-1, "Col_ComboBg",								18);
	state.SetField(-1, "Col_CheckMark",								19);
	state.SetField(-1, "Col_SliderGrab",							20);
	state.SetField(-1, "Col_SliderGrabActive",						21);
	state.SetField(-1, "Col_Button",								22);
	state.SetField(-1, "Col_ButtonHovered",							23);
	state.SetField(-1, "Col_ButtonActive",							24);
	state.SetField(-1, "Col_Header",								25);
	state.SetField(-1, "Col_HeaderHovered",							26);
	state.SetField(-1, "Col_HeaderActive",							27);
	state.SetField(-1, "Col_Column",								28);
	state.SetField(-1, "Col_ColumnHovered",							29);
	state.SetField(-1, "Col_ColumnActive",							30);
	state.SetField(-1, "Col_ResizeGrip",							31);
	state.SetField(-1, "Col_ResizeGripHovered",						32);	
	state.SetField(-1, "Col_ResizeGripActive",						33);
	state.SetField(-1, "Col_CloseButton",							34);
	state.SetField(-1, "Col_CloseButtonHovered",					35);		
	state.SetField(-1, "Col_CloseButtonActive",						36);
	state.SetField(-1, "Col_PlotLines",								37);
	state.SetField(-1, "Col_PlotLinesHovered",						38);	
	state.SetField(-1, "Col_PlotHistogram",							39);
	state.SetField(-1, "Col_PlotHistogramHovered",					40);	
	state.SetField(-1, "Col_TextSelectedBg",						41);
	state.SetField(-1, "Col_ModalWindowDarkening",					42);

	state.SetField(-1, "Align_Left",     							1 << 0);
	state.SetField(-1, "Align_Center",   							1 << 1);
	state.SetField(-1, "Align_Right",    							1 << 2);
	state.SetField(-1, "Align_Top",      							1 << 3);
	state.SetField(-1, "Align_VCenter",  							1 << 4);
	state.SetField(-1, "Align_Default",  							ImGuiAlign_Left | ImGuiAlign_Top);

	state.SetField(-1, "ColorEditMode_UserSelect",					-2);
	state.SetField(-1, "ColorEditMode_UserSelectShowButton",		-1);
	state.SetField(-1, "ColorEditMode_RGB",							0);
	state.SetField(-1, "ColorEditMode_HSV",							1);
	state.SetField(-1, "ColorEditMode_HEX",							2);

	state.SetField(-1, "MouseCursor_Arrow",							0);
	state.SetField(-1, "MouseCursor_TextInput",						1);
	state.SetField(-1, "MouseCursor_Move",							2);
	state.SetField(-1, "MouseCursor_ResizeNS",						3);
	state.SetField(-1, "MouseCursor_ResizeEW",						4);
	state.SetField(-1, "MouseCursor_ResizeNESW",					5);	
	state.SetField(-1, "MouseCursor_ResizeNWSE",					6);	
	state.SetField(-1, "MouseCursor_Count_",						7);

	state.SetField(-1, "SetCond_Always",        					1 << 0);	// Set the variable
	state.SetField(-1, "SetCond_Once",          					1 << 1);	// Only set the variable on the first call per runtime session
	state.SetField(-1, "SetCond_FirstUseEver",  					1 << 2);	// Only set the variable if the window doesn't exist in the .ini file
	state.SetField(-1, "SetCond_Appearing",     					1 << 3);	// Only set the variable if the window is appearing after being inactive (or the first time)


	luaL_Reg regTable[] = {
		{ "ShowTestWindow",						_ShowTestWindow },
		{ "ShowMetricsWindow",					_ShowMetricsWindow },

		{ "Begin",								_Begin },
		{ "End",								_End },
		{ "BeginChild",							_BeginChild },
		{ "EndChild",							_EndChild },

		{ "GetContentRegionMax",				_GetContentRegionMax },
		{ "GetContentRegionAvail",				_GetContentRegionAvail },
		{ "GetContentRegionAvailWidth",			_GetContentRegionAvailWidth },
		{ "GetWindowContentRegionMin",			_GetWindowContentRegionMin },
		{ "GetWindowContentRegionMax",			_GetWindowContentRegionMax },
		{ "GetWindowContentRegionWidth",		_GetWindowContentRegionWidth },
		{ "GetWindowPos",						_GetWindowPos },
		{ "GetWindowSize",						_GetWindowSize },
		{ "GetWindowWidth",						_GetWindowWidth },
		{ "GetWindowHeight",					_GetWindowHeight },

		{ "SetNextWindowPos",					_SetNextWindowPos },
		{ "SetNextWindowPosCenter",				_SetNextWindowPosCenter },
		{ "SetNextWindowSize",					_SetNextWindowSize },
		{ "SetNextWindowSizeConstraint",		_SetNextWindowSizeConstraint },
		{ "SetNextWindowContentSize",			_SetNextWindowContentSize },
		{ "SetNextWindowContentWidth",			_SetNextWindowContentWidth },
		{ "SetNextWindowCollapsed",				_SetNextWindowCollapsed },
		{ "SetNextWindowFocus",					_SetNextWindowFocus },
		{ "SetWindowPos",						_SetWindowPos },
		{ "SetWindowSize",						_SetWindowSize },
		{ "SetWindowCollapsed",					_SetWindowCollapsed },
		{ "SetWindowFocus",						_SetWindowFocus },

		{ "GetScrollX",							_GetScrollX },
		{ "GetScrollY",							_GetScrollY },
		{ "GetScrollMaxX",						_GetScrollMaxX },
		{ "GetScrollMaxY",						_GetScrollMaxY },
		{ "SetScrollX",							_SetScrollX },
		{ "SetScrollY",							_SetScrollY },
		{ "SetScrollHere",						_SetScrollHere },
		{ "SetScrollFromPosY",					_SetScrollFromPosY },
		{ "SetKeyboardFocusHere",				_SetKeyboardFocusHere },
		// { "SetStateStorage",					_SetStateStorage },
		// { "GetStateStorage",					_GetStateStorage },

		{ "Separator",							_Separator },
		{ "SameLine",							_SameLine },
		{ "NewLine",							_NewLine },
		{ "Spacing",							_Spacing },
		{ "Dummy",								_Dummy },
		{ "Indent",								_Indent },
		{ "Unindent",							_Unindent },
		{ "BeginGroup",							_BeginGroup },
		{ "EndGroup",							_EndGroup },
		{ "GetCursorPos",						_GetCursorPos },
		{ "GetCursorPosX",						_GetCursorPosX },
		{ "GetCursorPosY",						_GetCursorPosY },
		{ "SetCursorPos",						_SetCursorPos },
		{ "SetCursorPosX",						_SetCursorPosX },
		{ "SetCursorPosY",						_SetCursorPosY },
		{ "GetCursorStartPos",					_GetCursorStartPos },
		{ "GetCursorScreenPos",					_GetCursorScreenPos },
		{ "SetCursorScreenPos",					_SetCursorScreenPos },
		{ "AlignFirstTextHeightToWidgets",		_AlignFirstTextHeightToWidgets },
		{ "GetTextLineHeight",					_GetTextLineHeight },
		{ "GetTextLineHeightWithSpacing",		_GetTextLineHeightWithSpacing },
		{ "GetItemsLineHeightWithSpacing",		_GetItemsLineHeightWithSpacing },

		{ "Columns",							_Columns },
		{ "NextColumn",							_NextColumn },
		{ "GetColumnIndex",						_GetColumnIndex },
		{ "GetColumnOffset",					_GetColumnOffset },
		{ "SetColumnOffset",					_SetColumnOffset },
		{ "GetColumnWidth",						_GetColumnWidth },
		{ "GetColumnsCount",					_GetColumnsCount },
		
		{ "PushID",								_PushID },
		{ "PopID",								_PopID },
		{ "GetID",								_GetID },
		
		{ "Text",								_Text },
		{ "TextColored",						_TextColored },
		{ "TextDisabled",						_TextDisabled },
		{ "TextWrapped",						_TextWrapped },
		{ "TextUnformatted",					_TextUnformatted },
		{ "LabelText",							_LabelText },
		{ "Bullet",								_Bullet },
		{ "BulletText",							_BulletText },
		{ "Button",								_Button },
		{ "SmallButton",						_SmallButton },
		{ "InvisibleButton",					_InvisibleButton },
		{ "Checkbox",							_Checkbox },
		{ "RadioButton",						_RadioButton },
		{ "Combo",								_Combo },
		{ "ColorButton",						_ColorButton },
		{ "ColorEdit3",							_ColorEdit3 },
		{ "ColorEdit4",							_ColorEdit4 },
		{ "PlotLines",							_PlotLines },
		{ "PlotHistogram",						_PlotHistogram },
		{ "ProgressBar",						_ProgressBar },
		
		{ "DragFloat",							_DragFloat },
		{ "DragFloat2",							_DragFloat2 },
		{ "DragFloat3",							_DragFloat3 },
		{ "DragFloat4",							_DragFloat4 },
		{ "DragFloatRange2",					_DragFloatRange2 },
		{ "DragInt",							_DragInt },
		{ "DragInt2",							_DragInt2 },
		{ "DragInt3",							_DragInt3 },
		{ "DragInt4",							_DragInt4 },
		{ "DragIntRange2",						_DragIntRange2 },

		{ "InputText",							_InputText },
		{ "InputFloat",							_InputFloat },
		{ "InputFloat2",						_InputFloat2 },
		{ "InputFloat3",						_InputFloat3 },
		{ "InputFloat4",						_InputFloat4 },
		{ "InputInt",							_InputInt },
		{ "InputInt2",							_InputInt2 },
		{ "InputInt3",							_InputInt3 },
		{ "InputInt4",							_InputInt4 },

		{ "SliderFloat",						_SliderFloat },
		{ "SliderFloat2",						_SliderFloat2 },
		{ "SliderFloat3",						_SliderFloat3 },
		{ "SliderFloat4",						_SliderFloat4 },
		{ "SliderAngle",						_SliderAngle },
		{ "SliderInt",							_SliderInt },
		{ "SliderInt2",							_SliderInt2 },
		{ "SliderInt3",							_SliderInt3 },
		{ "SliderInt4",							_SliderInt4 },
		{ "VSliderFloat",						_VSliderFloat },
		{ "VSliderInt",							_VSliderInt },
		
		{ "TreeNode",							_TreeNode },
		{ "TreeNodeEx",							_TreeNodeEx },
		{ "TreePop",							_TreePop },
		{ "TreePush",							_TreePush },
		{ "SetNextTreeNodeOpen",				_SetNextTreeNodeOpen },
		{ "GetTreeNodeToLabelSpacing",			_GetTreeNodeToLabelSpacing },
		{ "CollapsingHeader",					_CollapsingHeader },

		{ "Selectable",							_Selectable },
		{ "ListBox",							_ListBox },
		{ "ListBoxHeader",						_ListBoxHeader },
		{ "ListBoxFooter",						_ListBoxFooter },
		
		{ "Value",								_Value },
		{ "ValueColor",							_ValueColor },

		{ "SetTooltip",							_SetTooltip },
		{ "BeginTooltip",						_BeginTooltip },
		{ "EndTooltip",							_EndTooltip },

		{ "BeginMainMenuBar",					_BeginMainMenuBar },
		{ "EndMainMenuBar",						_EndMainMenuBar },
		{ "BeginMenuBar",						_BeginMenuBar },
		{ "EndMenuBar",							_EndMenuBar },
		{ "BeginMenu",							_BeginMenu },
		{ "EndMenu",							_EndMenu },
		{ "MenuItem",							_MenuItem },

		{ "OpenPopup",							_OpenPopup },
		{ "BeginPopup",							_BeginPopup },
		{ "BeginPopupModal",					_BeginPopupModal },
		{ "BeginPopupContextItem",				_BeginPopupContextItem },
		{ "BeginPopupContextWindow",			_BeginPopupContextWindow },
		{ "BeginPopupContextVoid",				_BeginPopupContextVoid },
		{ "EndPopup",							_EndPopup },
		{ "CloseCurrentPopup",					_CloseCurrentPopup },

		{ "LogToTTY",							_LogToTTY },
		{ "LogToFile",							_LogToFile },
		{ "LogToClipboard",						_LogToClipboard },
		{ "LogFinish",							_LogFinish },
		{ "LogButtons",							_LogButtons },
		{ "LogText",							_LogText },

		{ "PushClipRect",						_PushClipRect },
		{ "PopClipRect",						_PopClipRect },

		{ "IsItemHovered",						_IsItemHovered },
		{ "IsItemHoveredRect",					_IsItemHoveredRect },
		{ "IsItemActive",						_IsItemActive },

		{ "IsItemClicked",						_IsItemClicked },
		{ "IsItemVisible",						_IsItemVisible },
		{ "IsAnyItemHovered",					_IsAnyItemHovered },
		{ "IsAnyItemActive",					_IsAnyItemActive },
		{ "GetItemRectMin",						_GetItemRectMin },
		{ "GetItemRectMax",						_GetItemRectMax },
		{ "GetItemRectSize",					_GetItemRectSize },
		{ "SetItemAllowOverlap",				_SetItemAllowOverlap },
		{ "IsWindowHovered",					_IsWindowHovered },
		{ "IsWindowFocused",					_IsWindowFocused },
		{ "IsRootWindowFocused",				_IsRootWindowFocused },
		{ "IsRootWindowOrAnyChildFocused",		_IsRootWindowOrAnyChildFocused },
		{ "IsRootWindowOrAnyChildHovered",		_IsRootWindowOrAnyChildHovered },
		{ "IsRectVisible",						_IsRectVisible },
		{ "IsPosHoveringAnyWindow",				_IsPosHoveringAnyWindow },
		{ "GetTime",							_GetTime },
		{ "GetFrameCount",						_GetFrameCount },
		{ "GetStyleColName",					_GetStyleColName },
		{ "CalcItemRectClosestPoint",			_CalcItemRectClosestPoint },
		{ "CalcTextSize",						_CalcTextSize },
		// { "CalcListClipping",					_CalcListClipping },

		{ "BeginChildFrame",					_BeginChildFrame },
		{ "EndChildFrame",						_EndChildFrame },

		{ "ColorConvertU32ToFloat4",			_ColorConvertU32ToFloat4 },
		{ "ColorConvertFloat4ToU32",			_ColorConvertFloat4ToU32 },
		{ "ColorConvertRGBtoHSV",				_ColorConvertRGBtoHSV },
		{ "ColorConvertHSVtoRGB",				_ColorConvertHSVtoRGB },

		{ "GetKeyIndex",						_GetKeyIndex },
		{ "IsKeyDown",							_IsKeyDown },
		{ "IsKeyPressed",						_IsKeyPressed },
		{ "IsKeyReleased",						_IsKeyReleased },
		{ "IsMouseDown",						_IsMouseDown },
		{ "IsMouseClicked",						_IsMouseClicked },
		{ "IsMouseDoubleClicked",				_IsMouseDoubleClicked },
		{ "IsMouseReleased",					_IsMouseReleased },
		{ "IsMouseHoveringWindow",				_IsMouseHoveringWindow },
		{ "IsMouseHoveringAnyWindow",			_IsMouseHoveringAnyWindow },
		{ "IsMouseHoveringRect",				_IsMouseHoveringRect },
		{ "IsMouseDragging",					_IsMouseDragging },
		{ "GetMousePos",						_GetMousePos },
		{ "GetMousePosOnOpeningCurrentPopup",	_GetMousePosOnOpeningCurrentPopup },
		{ "GetMouseDragDelta",					_GetMouseDragDelta },
		{ "ResetMouseDragDelta",				_ResetMouseDragDelta },
		{ "GetMouseCursor",						_GetMouseCursor },
		{ "SetMouseCursor",						_SetMouseCursor },
		{ "CaptureKeyboardFromApp",				_CaptureKeyboardFromApp },
		{ "CaptureMouseFromApp",				_CaptureMouseFromApp },

		{ "GetClipboardText",					_GetClipboardText },
		{ "SetClipboardText",					_SetClipboardText },

		{ "GetVersion",							_GetVersion },

		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

// Helper for grabbing different types of MOAIImVec2 from lua
// It might be MOAIImVec2 or 2 number params or a table/object with x and y fields or a table array with 2 numbers
bool imvec2_getter(MOAILuaState& state, int& idx, ImVec2** out_vec2)
{

	// is it a MOAI object?
	MOAILuaObject* luaObject = (MOAILuaObject*)state.GetPtrUserData(idx);
	if (luaObject)
	{
		MOAIImVec2* vec = state.GetLuaObject<MOAIImVec2>(idx, true);
		if (vec)
		{
			*out_vec2 = &vec->mVec2;
			++idx;
			return true;
		}
		else if (state.HasField(idx, "x", LUA_TNUMBER) && state.HasField(idx, "y", LUA_TNUMBER))
		{
			// some other moai object? look for x and y
			float x = state.GetField < float> ( idx, "x", 0.0f );
			float y = state.GetField < float> ( idx, "y", 0.0f );

			(*out_vec2)->x = x;
			(*out_vec2)->y = y;
			++idx;
			return true;
		}
	}

	// is it a table with x and y?
	if (state.IsType(idx, LUA_TTABLE))
	{
		if (state.HasField(idx, 1, LUA_TNUMBER) && state.HasField(idx, 2, LUA_TNUMBER))
		{
			float x = state.GetField < float>(idx, 1, 0.0f);
			float y = state.GetField < float>(idx, 2, 0.0f);

			(*out_vec2)->x = x;
			(*out_vec2)->y = y;
			++idx;
			return true;
		}
		else if (state.HasField(idx, "x", LUA_TNUMBER) && state.HasField(idx, "y", LUA_TNUMBER))
		{
			float x = state.GetField < float>(idx, "x", 0.0f);
			float y = state.GetField < float>(idx, "y", 0.0f);

			(*out_vec2)->x = x;
			(*out_vec2)->y = y;
			++idx;
			return true;
		}

		return false;
	}

	// just numbers
	if (state.IsType(idx, LUA_TNUMBER) && state.IsType(idx+1, LUA_TNUMBER))
	{
		float x = state.GetValue<float>(idx++, 0.0f);
		float y = state.GetValue<float>(idx++, 0.0f);

		(*out_vec2)->x = x;
		(*out_vec2)->y = y;
		return true;
	}

	return false;
}

// Helper for grabbing different types of MOAIImVec4 from lua
// It might be MOAIImVec4 or 4 number params or a table/object with x, y, z, w fields or a table array with 4 numbers
bool imvec4_getter(MOAILuaState& state, int& idx, ImVec4** out_vec4)
{

	// is it a MOAI object?
	MOAILuaObject* luaObject = (MOAILuaObject*)state.GetPtrUserData(idx);
	if (luaObject)
	{
		MOAIImVec4* vec = state.GetLuaObject<MOAIImVec4>(idx, true);
		if (vec)
		{
			*out_vec4 = &vec->mVec4;
			++idx;
			return true;
		}
		else if (state.HasField(idx, "x", LUA_TNUMBER) && state.HasField(idx, "y", LUA_TNUMBER) && state.HasField(idx, "z", LUA_TNUMBER) && state.HasField(idx, "z", LUA_TNUMBER))
		{
			// some other moai object? look for x and y
			float x = state.GetField < float> ( idx, "x", 0.0f );
			float y = state.GetField < float> ( idx, "y", 0.0f );
			float z = state.GetField < float> ( idx, "z", 0.0f );
			float w = state.GetField < float> ( idx, "w", 0.0f );

			(*out_vec4)->x = x;
			(*out_vec4)->y = y;
			(*out_vec4)->y = z;
			(*out_vec4)->y = w;
			++idx;
			return true;
		}
	}

	// is it a table with x and y?
	if (state.IsType(idx, LUA_TTABLE))
	{
		if (state.HasField(idx, 1, LUA_TNUMBER) && state.HasField(idx, 2, LUA_TNUMBER) && state.HasField(idx, 3, LUA_TNUMBER) && state.HasField(idx, 4, LUA_TNUMBER))
		{
			float x = state.GetField < float>(idx, 1, 0.0f);
			float y = state.GetField < float>(idx, 2, 0.0f);
			float z = state.GetField < float>(idx, 3, 0.0f);
			float w = state.GetField < float>(idx, 4, 0.0f);

			(*out_vec4)->x = x;
			(*out_vec4)->y = y;
			(*out_vec4)->z = z;
			(*out_vec4)->w = w;
			++idx;
			return true;
		}
		else if (state.HasField(idx, "x", LUA_TNUMBER) && state.HasField(idx, "y", LUA_TNUMBER) && state.HasField(idx, "z", LUA_TNUMBER) && state.HasField(idx, "w", LUA_TNUMBER))
		{
			float x = state.GetField < float>(idx, "x", 0.0f);
			float y = state.GetField < float>(idx, "y", 0.0f);
			float z = state.GetField < float>(idx, "z", 0.0f);
			float w = state.GetField < float>(idx, "w", 0.0f);

			(*out_vec4)->x = x;
			(*out_vec4)->y = y;
			(*out_vec4)->z = z;
			(*out_vec4)->w = w;
			++idx;
			return true;
		}

		return false;
	}

	// just numbers
	if (state.IsType(idx, LUA_TNUMBER) && state.IsType(idx+1, LUA_TNUMBER) && state.IsType(idx+2, LUA_TNUMBER) && state.IsType(idx+3, LUA_TNUMBER))
	{
		float x = state.GetValue<float>(idx++, 0.0f);
		float y = state.GetValue<float>(idx++, 0.0f);
		float z = state.GetValue<float>(idx++, 0.0f);
		float w = state.GetValue<float>(idx++, 0.0f);

		(*out_vec4)->x = x;
		(*out_vec4)->y = y;
		(*out_vec4)->z = z;
		(*out_vec4)->w = w;
		return true;
	}

	return false;
}

//----------------------------------------------------------------//
/**	@lua	ShowTestWindow
	@text	Show a test window for ImGui.

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
/**	@lua	ShowMetricsWindow
	@text	Show a metrics window for ImGui.

	@opt	boolean show		Default value is 'true.'
	@out	boolean show
*/
int MOAIImGui::_ShowMetricsWindow(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool open = state.GetValue < bool >(1, true);

	ImGui::ShowMetricsWindow(&open);

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

//----------------------------------------------------------------//
/**	@lua	BeginChild
	@text	See ImGui.

	@in		string or number id
	@opt	MOAIImVec2 size
	@opt	boolean border		Default value is 'false.'
	@opt	number extra_flags	Default value is 0
*/
int MOAIImGui::_BeginChild(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	bool border = state.GetValue<bool>(idx++, false);
	int extra_flags = state.GetValue<int>(idx++, 0);
	
	bool ret = false;
	
	if (state.IsType(1, LUA_TSTRING))
	{
		cc8* str_id = state.GetValue<cc8*>(1, "");

		ret = ImGui::BeginChild(str_id, *pv, border, extra_flags);
	}
	else if (state.IsType(1, LUA_TNUMBER))
	{
		int id = state.GetValue<int>(1, 0);

		ret = ImGui::BeginChild(id, *pv, border, extra_flags);
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
/**	@lua	GetContentRegionMax
	@text	See ImGui.

	@out	number x
	@out	number y
*/
int MOAIImGui::_GetContentRegionMax(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImVec2 ret = ImGui::GetContentRegionMax();
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	GetContentRegionAvail
	@text	See ImGui.

	@out	number x
	@out	number y
*/
int MOAIImGui::_GetContentRegionAvail(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImVec2 ret = ImGui::GetContentRegionAvail();
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	GetContentRegionAvailWidth
	@text	See ImGui.

	@out	number width
*/
int MOAIImGui::_GetContentRegionAvailWidth(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float width = ImGui::GetContentRegionAvailWidth();
	state.Push(width);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetWindowContentRegionMin
	@text	See ImGui.

	@out	number x
	@out	number y
*/
int MOAIImGui::_GetWindowContentRegionMin(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImVec2 ret = ImGui::GetWindowContentRegionMin();
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	GetWindowContentRegionMax
	@text	See ImGui.

	@out	number x
	@out	number y
*/
int MOAIImGui::_GetWindowContentRegionMax(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImVec2 ret = ImGui::GetWindowContentRegionMax();
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	GetWindowContentRegionWidth
	@text	See ImGui.

	@out	number width
*/
int MOAIImGui::_GetWindowContentRegionWidth(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float width = ImGui::GetWindowContentRegionWidth();
	state.Push(width);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetWindowPos
	@text	See ImGui.

	@out	number x
	@out	number y
*/
int MOAIImGui::_GetWindowPos(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImVec2 ret = ImGui::GetWindowPos();
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	GetWindowSize
	@text	See ImGui.

	@out	number x
	@out	number y
*/
int MOAIImGui::_GetWindowSize(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImVec2 ret = ImGui::GetWindowSize();
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	GetWindowWidth
	@text	See ImGui.

	@out	number width
*/
int MOAIImGui::_GetWindowWidth(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float width = ImGui::GetWindowWidth();
	state.Push(width);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetWindowHeight
	@text	See ImGui.

	@out	number height
*/
int MOAIImGui::_GetWindowHeight(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float height = ImGui::GetWindowHeight();
	state.Push(height);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsWindowCollapsed
	@text	See ImGui.

	@out	bool collapsed
*/
int MOAIImGui::_IsWindowCollapsed(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool collapsed = ImGui::IsWindowCollapsed();
	state.Push(collapsed);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	SetWindowFontScale
	@text	See ImGui.

	@in		number scale
*/
int MOAIImGui::_SetWindowFontScale(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	float scale = state.GetValue < float >(1, 1.0f);
	ImGui::SetWindowFontScale(scale);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetNextWindowPos
	@text	See ImGui.

	@in 	MOAIImVec2		pos
	@opt 	number			cond
*/
int MOAIImGui::_SetNextWindowPos(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 1;
	imvec2_getter(state, idx, &pv);
	
	int cond = state.GetValue < int >(idx++, 0);

	ImGui::SetNextWindowPos(*pv, cond);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetNextWindowPosCenter
	@text	See ImGui.

	@opt 	number			cond
*/
int MOAIImGui::_SetNextWindowPosCenter(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	int cond = state.GetValue < int >(1, 0);

	ImGui::SetNextWindowPosCenter(cond);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetNextWindowSize
	@text	See ImGui.

	@in 	MOAIImVec2		size
	@opt 	number			cond
*/
int MOAIImGui::_SetNextWindowSize(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 1;
	imvec2_getter(state, idx, &pv);

	int cond = state.GetValue < int >(idx++, 0);

	ImGui::SetNextWindowSize(*pv, cond);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetNextWindowSizeConstraint
	@text	See ImGui.

	@in 	MOAIImVec2		size_min
	@in 	MOAIImVec2		size_max
*/
int MOAIImGui::_SetNextWindowSizeConstraint(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@@");

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 1;
	imvec2_getter(state, idx, &pv);

	ImVec2 v2;
	ImVec2* pv2 = &v2;
	imvec2_getter(state, idx, &pv2);

	ImGui::SetNextWindowSizeConstraint(*pv, *pv2);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetNextWindowContentSize
	@text	See ImGui.

	@in 	MOAIImVec2		size
*/
int MOAIImGui::_SetNextWindowContentSize(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 1;
	imvec2_getter(state, idx, &pv);

	ImGui::SetNextWindowContentSize(*pv);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetNextWindowContentWidth
	@text	See ImGui.

	@in 	number		width
*/
int MOAIImGui::_SetNextWindowContentWidth(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	float width = state.GetValue < float >(1, 0.0f);

	ImGui::SetNextWindowContentWidth(width);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetNextWindowCollapsed
	@text	See ImGui.

	@in 	bool		collapsed
	@opt 	number		cond
*/
int MOAIImGui::_SetNextWindowCollapsed(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "B");

	bool collapsed = state.GetValue < bool >(1, true);
	int cond = state.GetValue < int >(2, 0);

	ImGui::SetNextWindowCollapsed(collapsed, cond);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetNextWindowFocus
	@text	See ImGui.
*/
int MOAIImGui::_SetNextWindowFocus(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::SetNextWindowFocus();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetWindowPos
	@text	See ImGui.

	@in 	string			name
	@in 	MOAIImVec2		pos
	@opt 	number			cond
*/
int MOAIImGui::_SetWindowPos(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* name = state.GetValue < cc8* >(1, "");
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	int cond = state.GetValue < int >(idx++, 0);

	ImGui::SetWindowPos(name, *pv, cond);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetWindowSize
	@text	See ImGui.

	@in 	string			name
	@in 	MOAIImVec2		size
	@opt 	number			cond
*/
int MOAIImGui::_SetWindowSize(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* name = state.GetValue < cc8* >(1, "");

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	int cond = state.GetValue < int >(idx++, 0);

	ImGui::SetWindowSize(name, *pv, cond);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetWindowCollapsed
	@text	See ImGui.

	@in 	string			name
	@in 	boolean			collapsed
	@opt 	number			cond
*/
int MOAIImGui::_SetWindowCollapsed(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SB");

	cc8* name = state.GetValue < cc8* >(1, "");
	bool collapsed = state.GetValue < bool >(2, true);
	int cond = state.GetValue < int >(3, 0);

	ImGui::SetWindowCollapsed(name, collapsed, cond);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetWindowFocus
	@text	See ImGui.

	@in 	string			name
*/
int MOAIImGui::_SetWindowFocus(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* name = state.GetValue < cc8* >(1, "");

	ImGui::SetWindowFocus(name);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	GetScrollX
	@text	See ImGui.

	@out	number x
*/
int MOAIImGui::_GetScrollX(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float ret = ImGui::GetScrollX();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetScrollY
	@text	See ImGui.

	@out	number y
*/
int MOAIImGui::_GetScrollY(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float ret = ImGui::GetScrollY();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetScrollMaxX
	@text	See ImGui.

	@out	number x
*/
int MOAIImGui::_GetScrollMaxX(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float ret = ImGui::GetScrollMaxX();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetScrollMaxY
	@text	See ImGui.

	@out	number y
*/
int MOAIImGui::_GetScrollMaxY(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float ret = ImGui::GetScrollMaxY();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	SetScrollX
	@text	See ImGui.

	@in 	number			scroll_x
*/
int MOAIImGui::_SetScrollX(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	float scroll_x = state.GetValue < float >(1, 0.0f);

	ImGui::SetScrollX(scroll_x);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetScrollY
	@text	See ImGui.

	@in 	number			scroll_y
*/
int MOAIImGui::_SetScrollY(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	float scroll_y = state.GetValue < float >(1, 0.0f);

	ImGui::SetScrollY(scroll_y);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetScrollHere
	@text	See ImGui.

	@opt 	number			center_y_ratio
*/
int MOAIImGui::_SetScrollHere(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float center_y_ratio = state.GetValue < float >(1, 0.5f);

	ImGui::SetScrollHere(center_y_ratio);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetScrollFromPosY
	@text	See ImGui.

	@in 	number			pos_y
	@opt 	number			center_y_ratio
*/
int MOAIImGui::_SetScrollFromPosY(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	float pos_y = state.GetValue < float >(1, 0.0f);
	float center_y_ratio = state.GetValue < float >(2, 0.5f);

	ImGui::SetScrollFromPosY(pos_y, center_y_ratio);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetKeyboardFocusHere
	@text	See ImGui.

	@opt 	number			offset
*/
int MOAIImGui::_SetKeyboardFocusHere(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	int offset = state.GetValue < int >(1, 0);

	ImGui::SetKeyboardFocusHere(offset);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	Separator
	@text	See ImGui.
*/
int MOAIImGui::_Separator(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::Separator();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SameLine
	@text	See ImGui.

	@opt	number pos_x
	@opt	number txt
*/
int MOAIImGui::_SameLine(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float pos_x = state.GetValue < float >(1, 0.0f);
	float spacing_w = state.GetValue < float >(2, -1.0f);
	ImGui::SameLine(pos_x, spacing_w);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	NewLine
	@text	See ImGui.
*/
int MOAIImGui::_NewLine(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::NewLine();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	Spacing
	@text	See ImGui.
*/
int MOAIImGui::_Spacing(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::Spacing();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	Dummy
	@text	See ImGui.

	@in MOAIImVec2		size
*/
int MOAIImGui::_Dummy(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 1;
	imvec2_getter(state, idx, &pv);

	ImGui::Dummy(*pv);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	Indent
	@text	See ImGui.
*/
int MOAIImGui::_Indent(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::Indent();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	Unindent
	@text	See ImGui.
*/
int MOAIImGui::_Unindent(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::Unindent();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	BeginGroup
	@text	See ImGui.
*/
int MOAIImGui::_BeginGroup(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::BeginGroup();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	EndGroup
	@text	See ImGui.
*/
int MOAIImGui::_EndGroup(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::EndGroup();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	GetCursorPos
	@text	See ImGui.

	@out	number x
	@out	number y
*/
int MOAIImGui::_GetCursorPos(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImVec2 ret = ImGui::GetCursorPos();
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	GetCursorPosX
	@text	See ImGui.

	@out	number x
*/
int MOAIImGui::_GetCursorPosX(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float ret = ImGui::GetCursorPosX();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetCursorPosY
	@text	See ImGui.

	@out	number y
*/
int MOAIImGui::_GetCursorPosY(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float ret = ImGui::GetCursorPosY();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	SetCursorPos
	@text	See ImGui.

	@in MOAIImVec2		local_pos
*/
int MOAIImGui::_SetCursorPos(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 1;
	imvec2_getter(state, idx, &pv);

	ImGui::SetCursorPos(*pv);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetCursorPosX
	@text	See ImGui.

	@in number		x
*/
int MOAIImGui::_SetCursorPosX(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	float x = state.GetValue<float>(1, 0.0f);

	ImGui::SetCursorPosX(x);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetCursorPosY
	@text	See ImGui.

	@in number		y
*/
int MOAIImGui::_SetCursorPosY(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	float y = state.GetValue<float>(1, 0.0f);

	ImGui::SetCursorPosY(y);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	GetCursorStartPos
	@text	See ImGui.

	@out	number x
	@out	number y
*/
int MOAIImGui::_GetCursorStartPos(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImVec2 ret = ImGui::GetCursorStartPos();
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	GetCursorScreenPos
	@text	See ImGui.

	@out	number x
	@out	number y
*/
int MOAIImGui::_GetCursorScreenPos(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImVec2 ret = ImGui::GetCursorScreenPos();
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	SetCursorScreenPos
	@text	See ImGui.

	@in MOAIImVec2		pos
*/
int MOAIImGui::_SetCursorScreenPos(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 1;
	imvec2_getter(state, idx, &pv);

	ImGui::SetCursorScreenPos(*pv);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	AlignFirstTextHeightToWidgets
	@text	See ImGui.
*/
int MOAIImGui::_AlignFirstTextHeightToWidgets(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::AlignFirstTextHeightToWidgets();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	GetTextLineHeight
	@text	See ImGui.

	@out	number height
*/
int MOAIImGui::_GetTextLineHeight(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float ret = ImGui::GetTextLineHeight();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetTextLineHeightWithSpacing
	@text	See ImGui.

	@out	number height
*/
int MOAIImGui::_GetTextLineHeightWithSpacing(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float ret = ImGui::GetTextLineHeightWithSpacing();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetItemsLineHeightWithSpacing
	@text	See ImGui.

	@out	number height
*/
int MOAIImGui::_GetItemsLineHeightWithSpacing(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float ret = ImGui::GetItemsLineHeightWithSpacing();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	Columns
	@text	See ImGui.

	@opt		number count
	@opt		string id
	@opt		boolean border
*/
int MOAIImGui::_Columns(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	int count = state.GetValue < int >(1, 1);
	cc8* id = state.GetValue < cc8* >(2, "");
	if (*id == '\0')
	{
		id = NULL;
	}
	bool border = state.GetValue < bool >(3, true);

	ImGui::Columns(count, id, border);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	NextColumn
	@text	See ImGui.
*/
int MOAIImGui::_NextColumn(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::NextColumn();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	GetColumnIndex
	@text	See ImGui.

	@out	number current column index
*/
int MOAIImGui::_GetColumnIndex(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float ret = (float)ImGui::GetColumnIndex();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetColumnOffset
	@text	See ImGui.

	@opt	number column_index
	@out	number column offset
*/
int MOAIImGui::_GetColumnOffset(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	int column_index = state.GetValue < int >(1, -1);
	float ret = (float)ImGui::GetColumnOffset(column_index);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	SetColumnOffset
	@text	See ImGui.

	@in		number column_index
	@in		number offset_x
*/
int MOAIImGui::_SetColumnOffset(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "NN");

	int column_index = state.GetValue < int >(1, 0);
	float offset_x = state.GetValue < float >(2, 0.0f);
	ImGui::SetColumnOffset(column_index, offset_x);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	GetColumnWidth
	@text	See ImGui.

	@opt	number column_index
	@out	number column width
*/
int MOAIImGui::_GetColumnWidth(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	int column_index = state.GetValue < int >(1, -1);
	float ret = (float)ImGui::GetColumnWidth(column_index);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetColumnsCount
	@text	See ImGui.

	@out	number columns count
*/
int MOAIImGui::_GetColumnsCount(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float ret = (float)ImGui::GetColumnsCount();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	PushID
	@text	See ImGui. char* and int versions.

	@in		number or string  id
*/
int MOAIImGui::_PushID(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	if (state.IsType(1, LUA_TSTRING))
	{
		cc8* id = state.GetValue < cc8* >(1, "");
		ImGui::PushID(id);
		return 0;
	}

	if (state.IsType(1, LUA_TNUMBER))
	{
		int id = state.GetValue < int >(1, 0);
		ImGui::PushID(id);
		return 0;
	}

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	PopID
	@text	See ImGui.
*/
int MOAIImGui::_PopID(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::PopID();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	GetID
	@text	See ImGui.

	@in		string id
	@out	number id
*/
int MOAIImGui::_GetID(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* column_index = state.GetValue < cc8* >(1, "");
	unsigned int ret = ImGui::GetID(column_index);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	Text
	@text	See ImGui.

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
	@text	See ImGui.

	@in MOAIImVec4		color
	@in	string 			txt
*/
int MOAIImGui::_TextColored(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@@");

	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 1;
	imvec4_getter(state, idx, &pv);

	cc8* txt = state.GetValue < cc8* >(idx++, "");

	ImGui::TextColored(*pv, txt);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	TextDisabled
	@text	See ImGui.

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
	@text	See ImGui.

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
	@text	See ImGui.

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
	@text	See ImGui.

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
	@text	See ImGui.

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
	@text	See ImGui.

	@in		string 			lbl
	@opt 	MOAIImVec2		size
	@out	boolean			pressed
*/
int MOAIImGui::_Button(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* lbl = state.GetValue < cc8* >(1, "");
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	bool ret = ImGui::Button(lbl, *pv);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	SmallButton
	@text	See ImGui.

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
	@text	See ImGui.

	@in		string 			id
	@in 	MOAIImVec2		size
	@out	boolean			pressed
*/
int MOAIImGui::_InvisibleButton(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* id = state.GetValue < cc8* >(1, "");
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	bool ret = ImGui::InvisibleButton(id, *pv);
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
	state.Push(ret);
	state.Push(checked);

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
	state.Push(ret);
	state.Push(activebutton);

	return 2;
}

// item getter for Combo() and ListBox()
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
	state.Push(ret);
	state.Push(currentitem + 1); // c array to lua array translation

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	ColorButton
	@text	See ImGui.

	@in 	MOAIImVec4		color
	@opt	boolean			small_height
	@opt	boolean			border
	@out	boolean			pressed
*/
int MOAIImGui::_ColorButton(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 1;
	imvec4_getter(state, idx, &pv);

	bool small_height = state.GetValue < bool >(idx++, false);
	bool border = state.GetValue < bool >(idx++, true);

	bool ret = ImGui::ColorButton(*pv, small_height, border);
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(pv->w);

	return 5;
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
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* lbl = state.GetValue < cc8* >(1, "");

	// TODO: some sort of array getter might make more sense here...
	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	bool ret = ImGui::ColorEdit3(lbl, &(pv->x));
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(1.0f);	// alpha is ignored but should be 1.0f always

	return 5;
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
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* lbl = state.GetValue < cc8* >(1, "");
	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	bool showalpha = state.GetValue < bool >(idx++, false);

	bool ret = ImGui::ColorEdit4(lbl, &(pv->x), showalpha);
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(pv->w);

	return 5;
}

// value getter for plot lines
float values_getter(void* data, int idx)
{
	MOAILuaState* state = (MOAILuaState*)data;
	state->GetField ( 2, idx+1 );
	float value = state->GetValue < float >( -1, 0.0f );
	lua_pop ( *state, 1 );
	
	return value;
}

//----------------------------------------------------------------//
/**	@lua	PlotLines
	@text	See ImGui.

	@in		string 			label
	@in		table			items
	@opt	number			values_offset
	@opt	string			overlay_text
	@opt	number			scale_min
	@opt	number			scale_max
	@opt 	MOAIImVec2		graph_size
*/
int MOAIImGui::_PlotLines(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "ST");

	cc8* label = state.GetValue < cc8* >(1, "");
	int values_count = (int)lua_objlen(L, 2);
	int values_offset = state.GetValue < int >(3, 1);
	cc8* overlay_text = state.GetValue < cc8* >(4, NULL);
	float scale_min = state.GetValue < float >(5, FLT_MAX);
	float scale_max = state.GetValue < float >(6, FLT_MAX);

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 7;
	imvec2_getter(state, idx, &pv);

	// lua array to c array translation
	--values_offset;
	ImGui::PlotLines(label, values_getter, &state, values_count, values_offset, overlay_text, scale_min, scale_max, *pv);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	PlotHistogram
	@text	See ImGui.

	@in		string 			label
	@in		table			items
	@opt	number			values_offset
	@opt	string			overlay_text
	@opt	number			scale_min
	@opt	number			scale_max
	@opt 	MOAIImVec2		graph_size
*/
int MOAIImGui::_PlotHistogram(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "ST");

	cc8* label = state.GetValue < cc8* >(1, "");
	int values_count = (int)lua_objlen(L, 2);
	int values_offset = state.GetValue < int >(3, 1);
	cc8* overlay_text = state.GetValue < cc8* >(4, NULL);
	float scale_min = state.GetValue < float >(5, FLT_MAX);
	float scale_max = state.GetValue < float >(6, FLT_MAX);

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 7;
	imvec2_getter(state, idx, &pv);

	// lua array to c array translation
	--values_offset;
	ImGui::PlotHistogram(label, values_getter, &state, values_count, values_offset, overlay_text, scale_min, scale_max, *pv);

	return 0;
}

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

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	
	if (imvec2_getter(state, idx, &pv))
	{
		if (state.IsType(idx, LUA_TSTRING))
		{
			cc8* overlay = state.GetValue < cc8* >(idx, "");
			ImGui::ProgressBar(fraction, *pv, overlay);
		}
		else
		{
			ImGui::ProgressBar(fraction, *pv);
		}
	}
	else if (state.IsType(idx, LUA_TSTRING))
	{
		cc8* overlay = state.GetValue < cc8* >(idx, "");
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
	state.Push(ret);
	state.Push(v);

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
	@out 	number 			x
	@out 	number 			y
*/
int MOAIImGui::_DragFloat2(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	float speed = state.GetValue < float >(idx++, 1.0f);
	float min = state.GetValue < float >(idx++, 0.0f);
	float max = state.GetValue < float >(idx++, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(idx++, "%.3f");
	float power = state.GetValue < float >(idx++, 1.0f);

	bool ret = ImGui::DragFloat2(label, &(pv->x), speed, min, max, display_format, power);
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);

	return 3;
}

//----------------------------------------------------------------//
/**	@lua	DragFloat3
	@text	See ImGui.

	@in		string 			label
	@in		MOAIImVec4		v
	@opt	number			speed
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@opt	number			power
	@out	boolean			pressed
*/
int MOAIImGui::_DragFloat3(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	// TODO: some sort of 3 getter
	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	float speed = state.GetValue < float >(idx++, 1.0f);
	float min = state.GetValue < float >(idx++, 0.0f);
	float max = state.GetValue < float >(idx++, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(idx++, "%.3f");
	float power = state.GetValue < float >(idx++, 1.0f);

	bool ret = ImGui::DragFloat3(label, &(pv->x), speed, min, max, display_format, power);
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(pv->w);

	return 5;
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
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	float speed = state.GetValue < float >(idx++, 1.0f);
	float min = state.GetValue < float >(idx++, 0.0f);
	float max = state.GetValue < float >(idx++, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(idx++, "%.3f");
	float power = state.GetValue < float >(idx++, 1.0f);

	bool ret = ImGui::DragFloat4(label, &(pv->x), speed, min, max, display_format, power);
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(pv->w);

	return 5;
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
	state.Push(ret);
	state.Push(v_min);
	state.Push(v_max);

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
	state.Push(ret);
	state.Push(v);

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
	@out	number			x
	@out	number			y
*/
int MOAIImGui::_DragInt2(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	float speed = state.GetValue < float >(idx++, 1.0f);
	int min = state.GetValue < int >(idx++, 0);
	int max = state.GetValue < int >(idx++, 0);
	cc8* display_format = state.GetValue < cc8* >(idx++, "%.0f");

	int integers[2];
	integers[0] = (int)pv->x;
	integers[1] = (int)pv->y;
	bool ret = ImGui::DragInt2(label, integers, speed, min, max, display_format);

	pv->x = (float)integers[0];
	pv->y = (float)integers[1];
	
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);

	return 3;
}

//----------------------------------------------------------------//
/**	@lua	DragInt3
	@text	See ImGui.

	@in		string 			label
	@in		MOAIImVec4		v
	@opt	number			speed
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@out	boolean			pressed
*/
int MOAIImGui::_DragInt3(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	float speed = state.GetValue < float >(idx++, 1.0f);
	int min = state.GetValue < int >(idx++, 0);
	int max = state.GetValue < int >(idx++, 0);
	cc8* display_format = state.GetValue < cc8* >(idx++, "%.0f");
// here v
	int integers[3];
	integers[0] = (int)pv->x;
	integers[1] = (int)pv->y;
	integers[2] = (int)pv->z;
	bool ret = ImGui::DragInt3(label, integers, speed, min, max, display_format);

	pv->x = (float)integers[0];
	pv->y = (float)integers[1];
	pv->z = (float)integers[2];

	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(pv->w);
	
	return 5;
}

//----------------------------------------------------------------//
/**	@lua	DragInt4
	@text	See ImGui.

	@in		string 			label
	@in		MOAIImVec4		v
	@opt	number			speed
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@out	boolean			pressed
*/
int MOAIImGui::_DragInt4(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	float speed = state.GetValue < float >(idx++, 1.0f);
	int min = state.GetValue < int >(idx++, 0);
	int max = state.GetValue < int >(idx++, 0);
	cc8* display_format = state.GetValue < cc8* >(idx++, "%.0f");

	int integers[4];
	integers[0] = (int)pv->x;
	integers[1] = (int)pv->y;
	integers[2] = (int)pv->z;
	integers[3] = (int)pv->w;
	bool ret = ImGui::DragInt4(label, integers, speed, min, max, display_format);

	pv->x = (float)integers[0];
	pv->y = (float)integers[1];
	pv->z = (float)integers[2];
	pv->w = (float)integers[3];
	
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(pv->w);
	
	return 5;
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
	state.Push(ret);
	state.Push(v_min);
	state.Push(v_max);

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
	state.Push(ret);
	state.Push(temp);

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
	state.Push(ret);
	state.Push(v);

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
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	int decimal_precision = state.GetValue < int >(idx++, -1);
	int extra_flags = state.GetValue < int >(idx++, 0);
	
	bool ret = ImGui::InputFloat2(label, &(pv->x), decimal_precision, extra_flags);
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);

	return 3;
}

//----------------------------------------------------------------//
/**	@lua	InputFloat3
@text	See ImGui.

@in		string 			label
@in		MOAIImVec4		v
@opt	number			decimal_precision
@opt	number			extra_flags
@out	boolean			pressed
*/
int MOAIImGui::_InputFloat3(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");
	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	int decimal_precision = state.GetValue < int >(idx++, -1);
	int extra_flags = state.GetValue < int >(idx++, 0);

	bool ret = ImGui::InputFloat3(label, &(pv->x), decimal_precision, extra_flags);
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(pv->w);
	
	return 5;
}

//----------------------------------------------------------------//
/**	@lua	InputFloat4
@text	See ImGui.

@in		string 			label
@in		MOAIImVec4		v
@opt	number			decimal_precision
@opt	number			extra_flags
@out	boolean			pressed
*/
int MOAIImGui::_InputFloat4(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	int decimal_precision = state.GetValue < int >(idx++, -1);
	int extra_flags = state.GetValue < int >(idx++, 0);

	bool ret = ImGui::InputFloat4(label, &(pv->x), decimal_precision, extra_flags);
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(pv->w);
	
	return 5;
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
	state.Push(ret);
	state.Push(v);

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
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	int extra_flags = state.GetValue < int >(idx++, 0);
	
	int integers[2];
	integers[0] = (int)pv->x;
	integers[1] = (int)pv->y;
	bool ret = ImGui::InputInt2(label, integers, extra_flags);

	pv->x = (float)integers[0];
	pv->y = (float)integers[1];

	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);

	return 3;
}

//----------------------------------------------------------------//
/**	@lua	InputInt3
	@text	See ImGui.

	@in		string 			label
	@in		MOAIImVec4		v
	@opt	number			extra_flags
	@out	boolean			pressed
*/
int MOAIImGui::_InputInt3(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	int extra_flags = state.GetValue < int >(idx++, 0);
	
	int integers[3];
	integers[0] = (int)pv->x;
	integers[1] = (int)pv->y;
	integers[2] = (int)pv->z;
	bool ret = ImGui::InputInt3(label, integers, extra_flags);

	pv->x = (float)integers[0];
	pv->y = (float)integers[1];
	pv->z = (float)integers[2];
	
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(pv->w);
	
	return 5;
}

//----------------------------------------------------------------//
/**	@lua	InputInt4
	@text	See ImGui.

	@in		string 			label
	@in		MOAIImVec4		v
	@opt	number			extra_flags
	@out	boolean			pressed
*/
int MOAIImGui::_InputInt4(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	int extra_flags = state.GetValue < int >(idx++, 0);
	
	int integers[4];
	integers[0] = (int)pv->x;
	integers[1] = (int)pv->y;
	integers[2] = (int)pv->z;
	integers[3] = (int)pv->w;
	bool ret = ImGui::InputInt4(label, integers, extra_flags);

	pv->x = (float)integers[0];
	pv->y = (float)integers[1];
	pv->z = (float)integers[2];
	pv->w = (float)integers[3];

	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(pv->w);
	
	return 5;
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
	state.Push(ret);
	state.Push(v);

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
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	float min = state.GetValue < float >(idx++, 0.0f);
	float max = state.GetValue < float >(idx++, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(idx++, "%.3f");
	float power = state.GetValue < float >(idx++, 1.0f);

	bool ret = ImGui::SliderFloat2(label, &(pv->x), min, max, display_format, power);
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);

	return 3;
}

//----------------------------------------------------------------//
/**	@lua	SliderFloat3
	@text	See ImGui.

	@in		string 			label
	@in		MOAIImVec4		v
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@opt	number			power
	@out	boolean			pressed
*/
int MOAIImGui::_SliderFloat3(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	float min = state.GetValue < float >(idx++, 0.0f);
	float max = state.GetValue < float >(idx++, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(idx++, "%.3f");
	float power = state.GetValue < float >(idx++, 1.0f);

	bool ret = ImGui::SliderFloat3(label, &(pv->x), min, max, display_format, power);
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(pv->w);
	
	return 5;
}

//----------------------------------------------------------------//
/**	@lua	SliderFloat4
	@text	See ImGui.

	@in		string 			label
	@in		MOAIImVec4		v
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@opt	number			power
	@out	boolean			pressed
*/
int MOAIImGui::_SliderFloat4(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");
	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	float min = state.GetValue < float >(idx++, 0.0f);
	float max = state.GetValue < float >(idx++, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(idx++, "%.3f");
	float power = state.GetValue < float >(idx++, 1.0f);

	bool ret = ImGui::SliderFloat4(label, &(pv->x), min, max, display_format, power);
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(pv->w);
	
	return 5;
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
	state.Push(ret);
	state.Push(v_rad);

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
	state.Push(ret);
	state.Push(v);

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
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	int min = state.GetValue < int >(idx++, 0);
	int max = state.GetValue < int >(idx++, 0);
	cc8* display_format = state.GetValue < cc8* >(idx++, "%.0f");

	int integers[2];
	integers[0] = (int)pv->x;
	integers[1] = (int)pv->y;
	bool ret = ImGui::SliderInt2(label, integers, min, max, display_format);

	pv->x = (float)integers[0];
	pv->y = (float)integers[1];

	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);

	return 3;
}

//----------------------------------------------------------------//
/**	@lua	SliderInt3
	@text	See ImGui.

	@in		string 			label
	@in		MOAIImVec4		v
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@out	boolean			pressed
*/
int MOAIImGui::_SliderInt3(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	int min = state.GetValue < int >(idx++, 0);
	int max = state.GetValue < int >(idx++, 0);
	cc8* display_format = state.GetValue < cc8* >(idx++, "%.0f");

	int integers[3];
	integers[0] = (int)pv->x;
	integers[1] = (int)pv->y;
	integers[2] = (int)pv->z;
	bool ret = ImGui::SliderInt3(label, integers, min, max, display_format);

	pv->x = (float)integers[0];
	pv->y = (float)integers[1];
	pv->z = (float)integers[2];

	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(pv->w);
	
	return 5;
}

bool          SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* display_format = "%.0f");
//----------------------------------------------------------------//
/**	@lua	SliderInt4
	@text	See ImGui.

	@in		string 			label
	@in		MOAIImVec4		v
	@opt	number			min
	@opt	number			max
	@opt	string			display_format
	@out	boolean			pressed
*/
int MOAIImGui::_SliderInt4(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	int min = state.GetValue < int >(idx++, 0);
	int max = state.GetValue < int >(idx++, 0);
	cc8* display_format = state.GetValue < cc8* >(idx++, "%.0f");

	int integers[4];
	integers[0] = (int)pv->x;
	integers[1] = (int)pv->y;
	integers[2] = (int)pv->z;
	integers[3] = (int)pv->w;
	bool ret = ImGui::SliderInt4(label, integers, min, max, display_format);

	pv->x = (float)integers[0];
	pv->y = (float)integers[1];
	pv->z = (float)integers[2];
	pv->w = (float)integers[3];
	
	state.Push(ret);
	state.Push(pv->x);
	state.Push(pv->y);
	state.Push(pv->z);
	state.Push(pv->w);
	
	return 5;
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
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@@");

	cc8* label = state.GetValue < cc8* >(1, "");
	
	ImVec2 size;
	ImVec2* pv = &size;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	float v = state.GetValue < float >(idx++, 0);
	float min = state.GetValue < float >(idx++, 0.0f);
	float max = state.GetValue < float >(idx++, 0.0f);
	cc8* display_format = state.GetValue < cc8* >(idx++, "%.3f");
	float power = state.GetValue < float >(idx++, 1.0f);

	bool ret = ImGui::VSliderFloat(label, *pv, &v, min, max, display_format, power);
	state.Push(ret);
	state.Push(v);

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
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@@");

	cc8* label = state.GetValue < cc8* >(1, "");
	
	ImVec2 size;
	ImVec2* pv = &size;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	int v = state.GetValue < int >(idx++, 0);
	int min = state.GetValue < int >(idx++, 0);
	int max = state.GetValue < int >(idx++, 0);
	cc8* display_format = state.GetValue < cc8* >(idx++, "%.0f");

	bool ret = ImGui::VSliderInt(label, *pv, &v, min, max, display_format);
	state.Push(ret);
	state.Push(v);

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
	@text	See ImGui.

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
	@text	See ImGui.

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
		state.Push(ret);
		state.Push(p_open);

		return 2;
	}
		
	bool ret = ImGui::CollapsingHeader(label);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	Selectable
	@text	See ImGui.

	@in		string	 	label
	@opt 	boolean		selected
	@opt	number	 	flags
	@opt	ImVec2	 	size
	@out	boolean		selected
	@out	boolean		pressed
*/
int MOAIImGui::_Selectable(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* label = state.GetValue < cc8* >(1, "");
	bool selected = state.GetValue < bool >(2, false);
	int flags = state.GetValue < int >(3, 0);

	bool ret = false;

	ImVec2 size;
	ImVec2* pv = &size;
	int idx = 4;
	if (imvec2_getter(state, idx, &pv))
	{
		ret = ImGui::Selectable(label, &selected, flags, *pv);
	}
	else
	{
		ret = ImGui::Selectable(label, &selected, flags);
	}
	state.Push(ret);
	state.Push(selected);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	ListBox
	@text	See ImGui.

	@in		string 			lbl
	@in		number			currentitem
	@in		table			items
	@opt	number			height
	@out	boolean			selected
	@out	number			currentitem
*/
int MOAIImGui::_ListBox(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "SNT");

	cc8* lbl = state.GetValue < cc8* >(1, "");
	int currentitem = state.GetValue < int >(2, 0);
	int numitems = (int)lua_objlen(L, 3);
	int height = state.GetValue < int >(4, -1);

	// lua array to c array translation
	--currentitem;
	bool ret = ImGui::ListBox(lbl, &currentitem, items_getter, &state, numitems, height);
	state.Push(ret);
	state.Push(currentitem + 1); // c array to lua array translation

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	ListBoxHeader
	@text	See ImGui.

	@in		string	 				label
	@in		MOAIImVec2 or number	size or items_count
	@opt 	number height_in_items
*/
int MOAIImGui::_ListBoxHeader(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* label = state.GetValue < cc8* >(1, "");

	bool ret;
	ImVec2 size;
	ImVec2* pv = &size;
	int idx = 2;
	if (imvec2_getter(state, idx, &pv))
	{
		ret = ImGui::ListBoxHeader(label, *pv);
	}
	else if (state.IsType(2, LUA_TNUMBER))
	{
		int items_count = state.GetValue < int >(2, 0);
		int height_in_items = state.GetValue < int >(3, -1);
		ret = ImGui::ListBoxHeader(label, items_count, height_in_items);
	}

	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	ListBoxFooter
	@text	See ImGui.
*/
int MOAIImGui::_ListBoxFooter(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::ListBoxFooter();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	Value
	@text	See ImGui.

	@in		string prefix
	@opt 	value
*/
int MOAIImGui::_Value(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* prefix = state.GetValue < cc8* >(1, "");

	int type = lua_type ( L, 2 );

	// Print value, if possible
	switch ( type )
	{
		case LUA_TNIL:
			ImGui::Text("%s: %s", prefix, state.GetLuaTypeName(type));
			break;
		case LUA_TBOOLEAN:
		{
			bool val = state.GetValue < bool >(2, false);
			ImGui::Value(prefix, val);
			break;
		}
		case LUA_TNUMBER:
		{
			float val = state.GetValue < float >(2, 0.0f);
			ImGui::Value(prefix, val);
			break;
		}
		case LUA_TSTRING:
		{
			cc8* val = state.GetValue < cc8* >(2, "");
			ImGui::Text("%s: %s", prefix, val);
			break;
		}
		case LUA_TUSERDATA:
		{
			// Moai uses userdata exclusively for pointers to MOAILuaObject instances.
			// This code will most likely crash if it encounters userdata that is used differently.
			MOAILuaObject* luaObject = (MOAILuaObject*)state.GetPtrUserData(2);
			if (luaObject)
			{
				ImGui::Text("%s: <%s %p>", prefix, luaObject->TypeName(), lua_topointer(L, 2));
			}
			else
			{
				ImGui::Text("%s: <%s %p>", prefix, "NON-MOAI USERDATA?", lua_topointer(L, 2));
			}
			break;
		}
		case LUA_TLIGHTUSERDATA:
		{
			void* val = state.GetValue < void* >(2, false);
			break;
		}
		case LUA_TTABLE:
		case LUA_TFUNCTION:
		case LUA_TTHREAD:
			// anything with an address
			ImGui::Text("%s: <%s %p>", prefix, state.GetLuaTypeName(type), lua_topointer(L, 2));
			break;
	}

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	ValueColor
	@text	See ImGui.

	@in	string 			prefix
	@in MOAIImVec4		color
*/
int MOAIImGui::_ValueColor(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S@");

	cc8* prefix = state.GetValue < cc8* >(1, "");

	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	ImGui::ValueColor(prefix, *pv);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	SetTooltip
	@text	See ImGui.

	@in	string 			txt
*/
int MOAIImGui::_SetTooltip(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* txt = state.GetValue < cc8* >(1, "");

	ImGui::SetTooltip(txt);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	BeginTooltip
	@text	See ImGui.
*/
int MOAIImGui::_BeginTooltip(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::BeginTooltip();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	EndTooltip
	@text	See ImGui.
*/
int MOAIImGui::_EndTooltip(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::EndTooltip();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	BeginMainMenuBar
	@text	See ImGui.

	@out	boolean	success
*/
int MOAIImGui::_BeginMainMenuBar(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::BeginMainMenuBar();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	EndMainMenuBar
	@text	See ImGui.
*/
int MOAIImGui::_EndMainMenuBar(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::EndMainMenuBar();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	BeginMenuBar
	@text	See ImGui.

	@out	boolean	success
*/
int MOAIImGui::_BeginMenuBar(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::BeginMenuBar();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	EndMenuBar
	@text	See ImGui.
*/
int MOAIImGui::_EndMenuBar(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::EndMenuBar();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	BeginMenu
	@text	See ImGui.

	@in 	string 	label
	@opt 	boolean	enabled

	@out	boolean	success
*/
int MOAIImGui::_BeginMenu(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	cc8* label = state.GetValue < cc8* >(1, "");
	bool enabled = state.GetValue < bool >(2, true);

	bool ret = ImGui::BeginMenu(label, enabled);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	EndMenu
	@text	See ImGui.
*/
int MOAIImGui::_EndMenu(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::EndMenu();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	MenuItem
	@text	See ImGui.

	@in 	string 	label
	@opt 	string 	shortcut
	@opt 	boolean	selected
	@opt 	boolean	enabled

	@out	boolean	selected
	@out	boolean	success
*/
int MOAIImGui::_MenuItem(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* label = state.GetValue < cc8* >(1, "");
	cc8* shortcut = state.GetValue < cc8* >(2, NULL);
	bool selected = state.GetValue < bool >(3, false);
	bool enabled = state.GetValue < bool >(4, true);

	bool success = ImGui::MenuItem(label, shortcut, &selected, enabled);
	state.Push(selected);
	state.Push(success);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	OpenPopup
	@text	See ImGui.

	@in 	string 	str_id
*/
int MOAIImGui::_OpenPopup(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* str_id = state.GetValue < cc8* >(1, "");

	ImGui::OpenPopup(str_id);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	BeginPopup
	@text	See ImGui.

	@in 	string 		str_id

	@out 	boolean 	open
*/
int MOAIImGui::_BeginPopup(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* str_id = state.GetValue < cc8* >(1, "");

	bool ret = ImGui::BeginPopup(str_id);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	BeginPopupModal
	@text	See ImGui.

	@in 	string 		name
	@opt 	boolean		open
	@opt 	number 		extra_flags

	@out 	boolean 	is_open
	@out 	boolean 	open
*/
int MOAIImGui::_BeginPopupModal(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* name = state.GetValue < cc8* >(1, "");
	int extra_flags = state.GetValue < int >(3, 0);

	if (state.IsType(2, LUA_TBOOLEAN))
	{
		bool open = state.GetValue < bool >(2, false);
		bool ret = ImGui::BeginPopupModal(name, &open, extra_flags);

		state.Push(ret);
		state.Push(open);

		return 2;
	}

	bool ret = ImGui::BeginPopupModal(name, NULL, extra_flags);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	BeginPopupContextItem
	@text	See ImGui.

	@in 	string 		str_id
	@opt 	number 		mouse_button

	@out 	boolean 	open
*/
int MOAIImGui::_BeginPopupContextItem(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* str_id = state.GetValue < cc8* >(1, "");
	int mouse_button = state.GetValue < int >(2, 1);

	bool ret = ImGui::BeginPopupContextItem(str_id, mouse_button);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	BeginPopupContextWindow
	@text	See ImGui.

	@opt 	boolean		also_over_items
	@opt 	string 		str_id
	@opt 	number 		mouse_button

	@out 	boolean 	open
*/
int MOAIImGui::_BeginPopupContextWindow(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool also_over_items = state.GetValue < bool >(1, true);
	cc8* str_id = state.GetValue < cc8* >(2, NULL);
	int mouse_button = state.GetValue < int >(3, 1);

	bool ret = ImGui::BeginPopupContextWindow(also_over_items, str_id, mouse_button);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	BeginPopupContextVoid
	@text	See ImGui.

	@opt 	string 		str_id
	@opt 	number 		mouse_button

	@out 	boolean 	open
*/
int MOAIImGui::_BeginPopupContextVoid(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	cc8* str_id = state.GetValue < cc8* >(1, NULL);
	int mouse_button = state.GetValue < int >(2, 1);

	bool ret = ImGui::BeginPopupContextVoid(str_id, mouse_button);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	EndPopup
	@text	See ImGui.
*/
int MOAIImGui::_EndPopup(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::EndPopup();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	CloseCurrentPopup
	@text	See ImGui.
*/
int MOAIImGui::_CloseCurrentPopup(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::CloseCurrentPopup();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	LogToTTY
	@text	See ImGui.

	@opt 	number 	max_depth
*/
int MOAIImGui::_LogToTTY(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	int max_depth = state.GetValue < int >(1, -1);

	ImGui::LogToTTY(max_depth);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	LogToFile
	@text	See ImGui.

	@opt 	number 	max_depth
	@opt 	string 	filename
*/
int MOAIImGui::_LogToFile(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	int max_depth = state.GetValue < int >(1, -1);
	cc8* filename = state.GetValue < cc8* >(2, NULL);

	ImGui::LogToFile(max_depth, filename);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	LogToClipboard
	@text	See ImGui.

	@opt 	number 	max_depth
*/
int MOAIImGui::_LogToClipboard(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	int max_depth = state.GetValue < int >(1, -1);

	ImGui::LogToClipboard(max_depth);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	LogFinish
	@text	See ImGui.
*/
int MOAIImGui::_LogFinish(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::LogFinish();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	LogButtons
	@text	See ImGui.
*/
int MOAIImGui::_LogButtons(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::LogButtons();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	LogText
	@text	See ImGui.

	@in 	string 	txt
*/
int MOAIImGui::_LogText(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* txt = state.GetValue < cc8* >(1, "");

	ImGui::LogText(txt);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	PushClipRect
	@text	See ImGui.

	@in 	MOAIImVec2		clip_rect_min
	@in 	MOAIImVec2		clip_rect_max
	@in 	boolean			intersect_with_current_clip_rect
*/
int MOAIImGui::_PushClipRect(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@@@");

	ImVec2 clip_rect_min;
	ImVec2* pclip_rect_min = &clip_rect_min;
	int idx = 1;
	imvec2_getter(state, idx, &pclip_rect_min);

	ImVec2 clip_rect_max;
	ImVec2* pclip_rect_max = &clip_rect_max;
	imvec2_getter(state, idx, &pclip_rect_max);

	bool intersect_with_current_clip_rect = state.GetValue < bool >(idx++, true);

	ImGui::PushClipRect(*pclip_rect_min, *pclip_rect_max, intersect_with_current_clip_rect);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	PopClipRect
	@text	See ImGui.
*/
int MOAIImGui::_PopClipRect(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::PopClipRect();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	IsItemHovered
	@text	See ImGui.

	@out	boolean	hovered
*/
int MOAIImGui::_IsItemHovered(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::IsItemHovered();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsItemHoveredRect
	@text	See ImGui.
	
	@out	boolean	hovered
*/
int MOAIImGui::_IsItemHoveredRect(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::IsItemHoveredRect();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsItemActive
	@text	See ImGui.
	
	@out	boolean	hovered
*/
int MOAIImGui::_IsItemActive(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::IsItemActive();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsItemClicked
	@text	See ImGui.
	
	@opt	number	mouse_button

	@out	boolean	clicked
*/
int MOAIImGui::_IsItemClicked(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	int mouse_button = state.GetValue < int >(1, 0);

	bool ret = ImGui::IsItemClicked(mouse_button);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsItemVisible
	@text	See ImGui.
	
	@out	boolean	visible
*/
int MOAIImGui::_IsItemVisible(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::IsItemVisible();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsAnyItemHovered
	@text	See ImGui.
	
	@out	boolean	hovered
*/
int MOAIImGui::_IsAnyItemHovered(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::IsAnyItemHovered();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsAnyItemActive
	@text	See ImGui.
	
	@out	boolean	active
*/
int MOAIImGui::_IsAnyItemActive(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::IsAnyItemActive();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetItemRectMin
	@text	See ImGui.

	@out	number x
	@out	number y
*/
int MOAIImGui::_GetItemRectMin(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImVec2 ret = ImGui::GetItemRectMin();
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	GetItemRectMax
	@text	See ImGui.

	@out	number x
	@out	number y
*/
int MOAIImGui::_GetItemRectMax(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImVec2 ret = ImGui::GetItemRectMax();
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	GetItemRectSize
	@text	See ImGui.

	@out	number x
	@out	number y
*/
int MOAIImGui::_GetItemRectSize(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImVec2 ret = ImGui::GetItemRectSize();
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	SetItemAllowOverlap
	@text	See ImGui.
*/
int MOAIImGui::_SetItemAllowOverlap(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::SetItemAllowOverlap();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	IsWindowHovered
	@text	See ImGui.
	
	@out	boolean	hovered
*/
int MOAIImGui::_IsWindowHovered(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::IsWindowHovered();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsWindowFocused
	@text	See ImGui.
	
	@out	boolean	focused
*/
int MOAIImGui::_IsWindowFocused(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::IsWindowFocused();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsRootWindowFocused
	@text	See ImGui.
	
	@out	boolean	focused
*/
int MOAIImGui::_IsRootWindowFocused(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::IsRootWindowFocused();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsRootWindowOrAnyChildFocused
	@text	See ImGui.
	
	@out	boolean	focused
*/
int MOAIImGui::_IsRootWindowOrAnyChildFocused(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::IsRootWindowOrAnyChildFocused();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsRootWindowOrAnyChildHovered
	@text	See ImGui.
	
	@out	boolean	hovered
*/
int MOAIImGui::_IsRootWindowOrAnyChildHovered(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::IsRootWindowOrAnyChildHovered();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsRectVisible
	@text	See ImGui.

	@in 	MOAIImVec2		size
	@out 	boolean			visible
*/
int MOAIImGui::_IsRectVisible(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	ImVec2 size;
	ImVec2* pv = &size;
	int idx = 1;
	imvec2_getter(state, idx, &pv);

	bool ret = ImGui::IsRectVisible(*pv);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsPosHoveringAnyWindow
	@text	See ImGui.

	@in 	MOAIImVec2		pos
	@out 	boolean			hovering
*/
int MOAIImGui::_IsPosHoveringAnyWindow(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	ImVec2 pos;
	ImVec2* pv = &pos;
	int idx = 1;
	imvec2_getter(state, idx, &pv);

	bool ret = ImGui::IsPosHoveringAnyWindow(*pv);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetTime
	@text	See ImGui.
	
	@out	number	time
*/
int MOAIImGui::_GetTime(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	float ret = ImGui::GetTime();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetFrameCount
	@text	See ImGui.
	
	@out	number	framecount
*/
int MOAIImGui::_GetFrameCount(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	int ret = ImGui::GetFrameCount();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetStyleColName
	@text	See ImGui.
	
	@opt	number	idx

	@out	boolean	clicked
*/
int MOAIImGui::_GetStyleColName(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	int idx = state.GetValue < int >(1, 0);

	cc8* ret = ImGui::GetStyleColName(idx);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	CalcItemRectClosestPoint
	@text	See ImGui.

	@in		MOAIImVec2 	pos
	@opt	boolean 	on_edge
	@opt	number 		outward

	@out	number x
	@out	number y
*/
int MOAIImGui::_CalcItemRectClosestPoint(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	ImVec2 pos;
	ImVec2* pv = &pos;
	int idx = 1;
	imvec2_getter(state, idx, &pv);

	bool on_edge = state.GetValue < bool >(idx++, false);
	float outward = state.GetValue < float >(idx++, 0.0f);

	ImVec2 ret = ImGui::CalcItemRectClosestPoint(*pv, on_edge, outward);
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	CalcTextSize
	@text	See ImGui.

	@in		string 		text
	@opt	bool 		hide_text_after_double_hash
	@opt	number 		wrap_width

	@out	number x
	@out	number y
*/
int MOAIImGui::_CalcTextSize(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* text = state.GetValue < cc8* >(1, "");
	bool hide_text_after_double_hash = state.GetValue < bool >(2, false);
	float wrap_width = state.GetValue < float >(3, -1.0f);

	ImVec2 ret = ImGui::CalcTextSize(text, NULL, hide_text_after_double_hash, wrap_width);
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	BeginChildFrame
	@text	See ImGui.

	@in		number 		id
	@in		MOAIImVec2 	size
	@opt	number 		extra_flags

	@out	boolean 	ok
*/
int MOAIImGui::_BeginChildFrame(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N@");

	int id = state.GetValue < int >(1, 0);

	ImVec2 size;
	ImVec2* pv = &size;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	int extra_flags = state.GetValue < int >(idx++, 0);

	bool ret = ImGui::BeginChildFrame(id, *pv, extra_flags);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	EndChildFrame
	@text	See ImGui.
*/
int MOAIImGui::_EndChildFrame(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::EndChildFrame();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	ColorConvertU32ToFloat4
	@text	See ImGui.

	@in		number 		in

	@out	number r
	@out	number g
	@out	number b
	@out	number a
*/
int MOAIImGui::_ColorConvertU32ToFloat4(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	unsigned int in = state.GetValue < unsigned int >(1, 0);

	ImVec4 ret = ImGui::ColorConvertU32ToFloat4(in);
	state.Push(ret.x);
	state.Push(ret.y);
	state.Push(ret.z);
	state.Push(ret.w);

	return 4;
}

//----------------------------------------------------------------//
/**	@lua	ColorConvertFloat4ToU32
	@text	See ImGui.

	@in		MOAIImVec4	in

	@out	number 		out
*/
int MOAIImGui::_ColorConvertFloat4ToU32(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@");

	ImVec4 v;
	ImVec4* pv = &v;
	int idx = 2;
	imvec4_getter(state, idx, &pv);

	ImU32 ret = ImGui::ColorConvertFloat4ToU32(*pv);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	ColorConvertRGBtoHSV
	@text	See ImGui.

	@in		number 	r
	@in		number 	g
	@in		number 	b

	@out	number 	h
	@out	number 	s
	@out	number 	v
*/
int MOAIImGui::_ColorConvertRGBtoHSV(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "NNN");

	float r = state.GetValue < float >(1, 0.0f);
	float g = state.GetValue < float >(2, 0.0f);
	float b = state.GetValue < float >(3, 0.0f);

	float h = 0.0f;
	float s = 0.0f;
	float v = 0.0f;

	ImGui::ColorConvertRGBtoHSV(r, g, b, h, s, v);
	state.Push(h);
	state.Push(s);
	state.Push(v);

	return 3;
}

//----------------------------------------------------------------//
/**	@lua	ColorConvertHSVtoRGB
	@text	See ImGui.

	@in		number 	h
	@in		number 	s
	@in		number 	v

	@out	number 	r
	@out	number 	g
	@out	number 	b
*/
int MOAIImGui::_ColorConvertHSVtoRGB(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "NNN");

	float h = state.GetValue < float >(1, 0.0f);
	float s = state.GetValue < float >(2, 0.0f);
	float v = state.GetValue < float >(3, 0.0f);

	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;

	ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b);
	state.Push(r);
	state.Push(g);
	state.Push(b);

	return 3;
}

//----------------------------------------------------------------//
/**	@lua	GetKeyIndex
	@text	See ImGui.

	@in		number 	key

	@out	number 	idx
*/
int MOAIImGui::_GetKeyIndex(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	int key = state.GetValue < int >(1, 0);

	int ret = ImGui::GetKeyIndex(key);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsKeyDown
	@text	See ImGui.

	@in		number 	key_index

	@out	boolean	down
*/
int MOAIImGui::_IsKeyDown(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	int key_index = state.GetValue < int >(1, 0);

	bool ret = ImGui::IsKeyDown(key_index);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsKeyPressed
	@text	See ImGui.

	@in		number 		key_index
	@opt	boolean 	repeat

	@out	boolean 	down
*/
int MOAIImGui::_IsKeyPressed(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	int key_index = state.GetValue < int >(1, 0);
	bool repeat = state.GetValue < bool >(2, true);

	bool ret = ImGui::IsKeyPressed(key_index, repeat);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsKeyReleased
	@text	See ImGui.

	@in		number 	key_index

	@out	boolean	released
*/
int MOAIImGui::_IsKeyReleased(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	int key_index = state.GetValue < int >(1, 0);

	bool ret = ImGui::IsKeyReleased(key_index);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsMouseDown
	@text	See ImGui.

	@in		number 	button

	@out	boolean	down
*/
int MOAIImGui::_IsMouseDown(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	int button = state.GetValue < int >(1, 0);

	bool ret = ImGui::IsMouseDown(button);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsMouseClicked
	@text	See ImGui.

	@in		number 	button

	@out	boolean	clicked
*/
int MOAIImGui::_IsMouseClicked(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	int button = state.GetValue < int >(1, 0);
	bool repeat = state.GetValue < bool >(2, false);

	bool ret = ImGui::IsMouseClicked(button, repeat);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsMouseDoubleClicked
	@text	See ImGui.

	@in		number 	button

	@out	boolean	doubleclicked
*/
int MOAIImGui::_IsMouseDoubleClicked(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	int button = state.GetValue < int >(1, 0);

	bool ret = ImGui::IsMouseDoubleClicked(button);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsMouseReleased
	@text	See ImGui.

	@in		number 	button

	@out	boolean	released
*/
int MOAIImGui::_IsMouseReleased(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	int button = state.GetValue < int >(1, 0);

	bool ret = ImGui::IsMouseReleased(button);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsMouseHoveringWindow
	@text	See ImGui.

	@out	boolean	hovering
*/
int MOAIImGui::_IsMouseHoveringWindow(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::IsMouseHoveringWindow();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsMouseHoveringAnyWindow
	@text	See ImGui.

	@out	boolean	hovering
*/
int MOAIImGui::_IsMouseHoveringAnyWindow(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool ret = ImGui::IsMouseHoveringAnyWindow();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsMouseHoveringRect
	@text	See ImGui.

	@in		MOAIImVec2	r_min
	@in		MOAIImVec2	r_max
	@opt	boolean		clip

	@out	boolean		hovering
*/
int MOAIImGui::_IsMouseHoveringRect(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "@@");

	ImVec2 r_min;
	ImVec2* pr_min = &r_min;
	int idx = 1;
	imvec2_getter(state, idx, &pr_min);

	ImVec2 r_max;
	ImVec2* pr_max = &r_max;
	imvec2_getter(state, idx, &pr_max);

	bool clip = state.GetValue < bool >(idx++, 0);

	bool ret = ImGui::IsMouseHoveringRect(*pr_min, *pr_min, clip);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	IsMouseDragging
	@text	See ImGui.

	@opt	number 	button
	@opt	number 	lock_threshold

	@out	boolean	dragging
*/
int MOAIImGui::_IsMouseDragging(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	int button = state.GetValue < int >(1, 0);
	float lock_threshold = state.GetValue < float >(2, -1.0f);

	bool ret = ImGui::IsMouseDragging(button, lock_threshold);
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	GetMousePos
	@text	See ImGui.

	@out	number 	x
	@out	number 	y
*/
int MOAIImGui::_GetMousePos(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImVec2 ret = ImGui::GetMousePos();
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	GetMousePosOnOpeningCurrentPopup
	@text	See ImGui.

	@out	number 	x
	@out	number 	y
*/
int MOAIImGui::_GetMousePosOnOpeningCurrentPopup(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImVec2 ret = ImGui::GetMousePosOnOpeningCurrentPopup();
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	GetMouseDragDelta
	@text	See ImGui.

	@out	number 	x
	@out	number 	y
*/
int MOAIImGui::_GetMouseDragDelta(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	int button = state.GetValue < int >(1, 0);
	float lock_threshold = state.GetValue < float >(2, -1.0f);

	ImVec2 ret = ImGui::GetMouseDragDelta(button, lock_threshold);
	state.Push(ret.x);
	state.Push(ret.y);

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	ResetMouseDragDelta
	@text	See ImGui.

	@opt	number 	button
*/
int MOAIImGui::_ResetMouseDragDelta(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	int button = state.GetValue < int >(1, 0);

	ImGui::ResetMouseDragDelta(button);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	GetMouseCursor
	@text	See ImGui.

	@out	number	mousecursor
*/
int MOAIImGui::_GetMouseCursor(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGuiMouseCursor ret = ImGui::GetMouseCursor();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	SetMouseCursor
	@text	See ImGui.

	@in		number 	type
*/
int MOAIImGui::_SetMouseCursor(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "N");

	int type = state.GetValue < int >(1, 0);

	ImGui::SetMouseCursor(type);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	CaptureKeyboardFromApp
	@text	See ImGui.

	@opt	boolean 	capture
*/
int MOAIImGui::_CaptureKeyboardFromApp(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool capture = state.GetValue < bool >(1, true);

	ImGui::CaptureKeyboardFromApp(capture);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	CaptureMouseFromApp
	@text	See ImGui.

	@opt	boolean 	capture
*/
int MOAIImGui::_CaptureMouseFromApp(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	bool capture = state.GetValue < bool >(1, true);

	ImGui::CaptureMouseFromApp(capture);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	GetClipboardText
	@text	See ImGui.

	@out	string	text
*/
int MOAIImGui::_GetClipboardText(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	cc8* ret = ImGui::GetClipboardText();
	state.Push(ret);

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	SetClipboardText
	@text	See ImGui.

	@in		string 	text
*/
int MOAIImGui::_SetClipboardText(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* text = state.GetValue < cc8* >(1, "");

	ImGui::SetClipboardText(text);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	GetVersion
	@text	See ImGui.

	@out	string	version
*/
int MOAIImGui::_GetVersion(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	cc8* ret = ImGui::GetVersion();
	state.Push(ret);

	return 1;
}
