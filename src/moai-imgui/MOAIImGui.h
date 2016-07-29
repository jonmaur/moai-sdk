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

	// static int _PushFont(lua_State* L);
	// static int _PopFont(lua_State* L);
	// static int _PushStyleColor(lua_State* L);
	// static int _PopStyleColor(lua_State* L);
	// static int _PushStyleVar(lua_State* L);
	// static int _PushStyleVar(lua_State* L);
	// static int _PopStyleVar(lua_State* L);
	// static int _GetFont(lua_State* L);
	// static int _GetFontSize(lua_State* L);
	// static int _GetFontTexUvWhitePixel(lua_State* L);
	// static int _GetColorU32(lua_State* L);
	// static int _GetColorU32(lua_State* L);

	// static int _PushItemWidth(lua_State* L);
	// static int _PopItemWidth(lua_State* L);
	// static int _CalcItemWidth(lua_State* L);
	// static int _PushTextWrapPos(lua_State* L);
	// static int _PopTextWrapPos(lua_State* L);
	// static int _PushAllowKeyboardFocus(lua_State* L);
	// static int _PopAllowKeyboardFocus(lua_State* L);
	// static int _PushButtonRepeat(lua_State* L);
	// static int _PopButtonRepeat(lua_State* L);

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
	static int _PlotLines(lua_State* L);
	static int _PlotHistogram(lua_State* L);
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

	static int _Selectable(lua_State* L);
	static int _ListBox(lua_State* L);
	static int _ListBoxHeader(lua_State* L);
	static int _ListBoxFooter(lua_State* L);
	
	static int _Value(lua_State* L);
	static int _ValueColor(lua_State* L);

	static int _SetTooltip(lua_State* L);
	static int _BeginTooltip(lua_State* L);
	static int _EndTooltip(lua_State* L);

	static int _BeginMainMenuBar(lua_State* L);
	static int _EndMainMenuBar(lua_State* L);
	static int _BeginMenuBar(lua_State* L);
	static int _EndMenuBar(lua_State* L);
	static int _BeginMenu(lua_State* L);
	static int _EndMenu(lua_State* L);
	static int _MenuItem(lua_State* L);
	
	static int _OpenPopup(lua_State* L);
	static int _BeginPopup(lua_State* L);
	static int _BeginPopupModal(lua_State* L);
	static int _BeginPopupContextItem(lua_State* L);
	static int _BeginPopupContextWindow(lua_State* L);
	static int _BeginPopupContextVoid(lua_State* L);
	static int _EndPopup(lua_State* L);
	static int _CloseCurrentPopup(lua_State* L);

	static int _LogToTTY(lua_State* L);
	static int _LogToFile(lua_State* L);
	static int _LogToClipboard(lua_State* L);
	static int _LogFinish(lua_State* L);
	static int _LogButtons(lua_State* L);
	static int _LogText(lua_State* L);
	
	static int _PushClipRect(lua_State* L);
	static int _PopClipRect(lua_State* L);

	static int _IsItemHovered(lua_State* L);
	static int _IsItemHoveredRect(lua_State* L);
	static int _IsItemActive(lua_State* L);
	
	static int _IsItemClicked(lua_State* L);
	static int _IsItemVisible(lua_State* L);
	static int _IsAnyItemHovered(lua_State* L);
	static int _IsAnyItemActive(lua_State* L);
	static int _GetItemRectMin(lua_State* L);
	static int _GetItemRectMax(lua_State* L);
	static int _GetItemRectSize(lua_State* L);
	static int _SetItemAllowOverlap(lua_State* L);
	static int _IsWindowHovered(lua_State* L);
	static int _IsWindowFocused(lua_State* L);
	static int _IsRootWindowFocused(lua_State* L);
	static int _IsRootWindowOrAnyChildFocused(lua_State* L);
	static int _IsRootWindowOrAnyChildHovered(lua_State* L);
	static int _IsRectVisible(lua_State* L);
	static int _IsPosHoveringAnyWindow(lua_State* L);
	static int _GetTime(lua_State* L);
	static int _GetFrameCount(lua_State* L);
	static int _GetStyleColName(lua_State* L);
	static int _CalcItemRectClosestPoint(lua_State* L);
	static int _CalcTextSize(lua_State* L);
	// static int _CalcListClipping(lua_State* L);
	
	static int _BeginChildFrame(lua_State* L);
	static int _EndChildFrame(lua_State* L);
	
	static int _ColorConvertU32ToFloat4(lua_State* L);
	static int _ColorConvertFloat4ToU32(lua_State* L);
	static int _ColorConvertRGBtoHSV(lua_State* L);
	static int _ColorConvertHSVtoRGB(lua_State* L);
	
	static int _GetKeyIndex(lua_State* L);
	static int _IsKeyDown(lua_State* L);
	static int _IsKeyPressed(lua_State* L);
	static int _IsKeyReleased(lua_State* L);
	static int _IsMouseDown(lua_State* L);
	static int _IsMouseClicked(lua_State* L);
	static int _IsMouseDoubleClicked(lua_State* L);
	static int _IsMouseReleased(lua_State* L);
	static int _IsMouseHoveringWindow(lua_State* L);
	static int _IsMouseHoveringAnyWindow(lua_State* L);
	static int _IsMouseHoveringRect(lua_State* L);
	static int _IsMouseDragging(lua_State* L);
	static int _GetMousePos(lua_State* L);
	static int _GetMousePosOnOpeningCurrentPopup(lua_State* L);
	static int _GetMouseDragDelta(lua_State* L);
	static int _ResetMouseDragDelta(lua_State* L);
	static int _GetMouseCursor(lua_State* L);
	static int _SetMouseCursor(lua_State* L);
	static int _CaptureKeyboardFromApp(lua_State* L);
	static int _CaptureMouseFromApp(lua_State* L);

	static int _GetClipboardText(lua_State* L);
	static int _SetClipboardText(lua_State* L);
	
	static int _GetVersion(lua_State* L);

public:

	DECL_LUA_SINGLETON(MOAIImGui)

		//----------------------------------------------------------------//
							MOAIImGui();
							~MOAIImGui();
		void				RegisterLuaClass(MOAILuaState& state);

};

#endif
