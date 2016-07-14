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
	static int _ShowMetricsWindow(lua_State* L);

	static int _Begin(lua_State* L);
	static int _End(lua_State* L);
	static int _BeginChild(lua_State* L);
	static int _EndChild(lua_State* L);

	static int _GetContentRegionMax(lua_State* L);
	static int _GetContentRegionAvail(lua_State* L);
	static int _GetContentRegionAvailWidth(lua_State* L);
	static int _GetWindowContentRegionMin(lua_State* L);
	static int _GetWindowContentRegionMax(lua_State* L);
	static int _GetWindowContentRegionWidth(lua_State* L);
	// static int _GetWindowDrawList(lua_State* L);  // skipping, tricky to bind
	static int _GetWindowPos(lua_State* L);
	static int _GetWindowSize(lua_State* L);
	static int _GetWindowWidth(lua_State* L);
	static int _GetWindowHeight(lua_State* L);
	static int _IsWindowCollapsed(lua_State* L);
	static int _SetWindowFontScale(lua_State* L);

	static int _SetNextWindowPos(lua_State* L);
	static int _SetNextWindowPosCenter(lua_State* L);
	static int _SetNextWindowSize(lua_State* L);
	static int _SetNextWindowSizeConstraint(lua_State* L);
	static int _SetNextWindowContentSize(lua_State* L);
	static int _SetNextWindowContentWidth(lua_State* L);
	static int _SetNextWindowCollapsed(lua_State* L);
	static int _SetNextWindowFocus(lua_State* L);
	static int _SetWindowPos(lua_State* L);
	static int _SetWindowSize(lua_State* L);
	static int _SetWindowCollapsed(lua_State* L);
	static int _SetWindowFocus(lua_State* L);
	
	static int _GetScrollX(lua_State* L);
	static int _GetScrollY(lua_State* L);
	static int _GetScrollMaxX(lua_State* L);
	static int _GetScrollMaxY(lua_State* L);
	static int _SetScrollX(lua_State* L);
	static int _SetScrollY(lua_State* L);
	static int _SetScrollHere(lua_State* L);
	static int _SetScrollFromPosY(lua_State* L);
	static int _SetKeyboardFocusHere(lua_State* L);
	// static int _SetStateStorage(lua_State* L);
	// static int _GetStateStorage(lua_State* L);

	static int _Separator(lua_State* L);
	static int _SameLine(lua_State* L);
	static int _NewLine(lua_State* L);
	static int _Spacing(lua_State* L);
	static int _Dummy(lua_State* L);
	static int _Indent(lua_State* L);
	static int _Unindent(lua_State* L);
	static int _BeginGroup(lua_State* L);
	static int _EndGroup(lua_State* L);
	static int _GetCursorPos(lua_State* L);
	static int _GetCursorPosX(lua_State* L);
	static int _GetCursorPosY(lua_State* L);
	static int _SetCursorPos(lua_State* L);
	static int _SetCursorPosX(lua_State* L);
	static int _SetCursorPosY(lua_State* L);
	static int _GetCursorStartPos(lua_State* L);
	static int _GetCursorScreenPos(lua_State* L);
	static int _SetCursorScreenPos(lua_State* L);
	static int _AlignFirstTextHeightToWidgets(lua_State* L);
	static int _GetTextLineHeight(lua_State* L);
	static int _GetTextLineHeightWithSpacing(lua_State* L);
	static int _GetItemsLineHeightWithSpacing(lua_State* L);
	
	static int _Columns(lua_State* L);
	static int _NextColumn(lua_State* L);
	static int _GetColumnIndex(lua_State* L);
	static int _GetColumnOffset(lua_State* L);
	static int _SetColumnOffset(lua_State* L);
	static int _GetColumnWidth(lua_State* L);
	static int _GetColumnsCount(lua_State* L);

	static int _PushID(lua_State* L);
	static int _PopID(lua_State* L);
	static int _GetID(lua_State* L);

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
	static int _InputInt(lua_State* L);
	static int _InputInt2(lua_State* L);
	static int _InputInt3(lua_State* L);
	static int _InputInt4(lua_State* L);

	static int _SliderFloat(lua_State* L);
	static int _SliderFloat2(lua_State* L);
	static int _SliderFloat3(lua_State* L);
	static int _SliderFloat4(lua_State* L);
	static int _SliderAngle(lua_State* L);
	static int _SliderInt(lua_State* L);
	static int _SliderInt2(lua_State* L);
	static int _SliderInt3(lua_State* L);
	static int _SliderInt4(lua_State* L);
	static int _VSliderFloat(lua_State* L);
	static int _VSliderInt(lua_State* L);

	static int _TreeNode(lua_State* L);
	static int _TreeNodeEx(lua_State* L);
	static int _TreePop(lua_State* L);
	static int _TreePush(lua_State* L);
	static int _SetNextTreeNodeOpen(lua_State* L);
	static int _GetTreeNodeToLabelSpacing(lua_State* L);
	static int _CollapsingHeader(lua_State* L);

public:

	DECL_LUA_SINGLETON(MOAIImGui)

		//----------------------------------------------------------------//
							MOAIImGui();
							~MOAIImGui();
		void				RegisterLuaClass(MOAILuaState& state);

};

#endif
