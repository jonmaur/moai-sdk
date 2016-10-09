#include <moai-imgui/MOAIImDrawList.h>
#include <moai-imgui/MOAIImVec2.h>
#include <moai-imgui/MOAIImVec4.h>


//----------------------------------------------------------------//
MOAIImDrawList::MOAIImDrawList() {

	RTTI_SINGLE(MOAIImDrawList)
}
MOAIImDrawList::~MOAIImDrawList() {
}
//----------------------------------------------------------------//

void MOAIImDrawList::RegisterLuaClass(MOAILuaState& state) {

	MOAILuaObject::RegisterLuaClass(state);
}

void MOAIImDrawList::RegisterLuaFuncs(MOAILuaState& state) {

	MOAILuaObject::RegisterLuaFuncs(state);

	luaL_Reg regTable[] = {
		{ "PushClipRect",					_PushClipRect },
		{ "PushClipRectFullScreen",			_PushClipRectFullScreen },
		{ "PopClipRect",					_PopClipRect },
		{ "AddLine",						_AddLine },
		{ "AddRect",						_AddRect },
		{ "AddRectFilled",					_AddRectFilled },
		{ "AddRectFilledMultiColor",		_AddRectFilledMultiColor },
		{ "AddQuad",						_AddQuad },
		{ "AddQuadFilled",					_AddQuadFilled },
		{ "AddTriangle",					_AddTriangle },
		{ "AddTriangleFilled",				_AddTriangleFilled },
		{ "AddCircle",						_AddCircle },
		{ "AddCircleFilled",				_AddCircleFilled },
		{ "AddText",						_AddText },

		{ "PathClear",						_PathClear },
		{ "PathLineTo",						_PathLineTo },
		{ "PathLineToMergeDuplicate",		_PathLineToMergeDuplicate },
		{ "PathFill",						_PathFill },
		{ "PathStroke",						_PathStroke },
		{ "PathArcTo",						_PathArcTo },
		{ "PathArcToFast",					_PathArcToFast },
		{ "PathBezierCurveTo",				_PathBezierCurveTo },
		{ "PathRect",						_PathRect },

		{ "ChannelsSplit",					_ChannelsSplit },
		{ "ChannelsMerge",					_ChannelsMerge },
		{ "ChannelsSetCurrent",				_ChannelsSetCurrent },
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);

}

//----------------------------------------------------------------//
/**	@lua	PushClipRect
	@text	See ImGui.

	@in		ImVec2 clip_rect_min
	@in		ImVec2 clip_rect_max
	@opt	boolean intersect_with_current_clip_rect
*/
int	MOAIImDrawList::_PushClipRect(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	ImVec2 v2;
	ImVec2* pv2 = &v2;
	imvec2_getter(state, idx, &pv2);

	bool intersect_with_current_clip_rect = state.GetValue < bool >(idx++, false);

	self->mDrawList->PushClipRect(*pv, *pv2, intersect_with_current_clip_rect);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	PushClipRectFullScreen
	@text	See ImGui.
*/
int	MOAIImDrawList::_PushClipRectFullScreen(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U")
	
	self->mDrawList->PushClipRectFullScreen();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	PopClipRect
	@text	See ImGui.
*/
int	MOAIImDrawList::_PopClipRect(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U")
	
	self->mDrawList->PopClipRect();

	return 0;
}


//----------------------------------------------------------------//
/**	@lua	AddLine
	@text	See ImGui.

	@in		ImVec2 a
	@in		ImVec2 b
	@opt	number col
	@opt	number thickness
*/
int	MOAIImDrawList::_AddLine(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	ImVec2 v2;
	ImVec2* pv2 = &v2;
	imvec2_getter(state, idx, &pv2);

	unsigned int col = state.GetValue < unsigned int >(idx++, 0xFFFFFFFF);
	float thickness = state.GetValue < float >(idx++, 1.0f);

	self->mDrawList->AddLine(*pv, *pv2, col, thickness);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	AddRect
	@text	See ImGui.

	@in		ImVec2 a
	@in		ImVec2 b
	@opt	number col
	@opt	number rounding
	@opt	number rounding_corners
	@opt	number thickness
*/
int	MOAIImDrawList::_AddRect(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	ImVec2 v2;
	ImVec2* pv2 = &v2;
	imvec2_getter(state, idx, &pv2);

	u32 col = state.GetValue < u32 >(idx++, 0xFFFFFFFF);
	float rounding = state.GetValue < float >(idx++, 0.0f);
	int rounding_corners = state.GetValue < int >(idx++, 0x0F);
	float thickness = state.GetValue < float >(idx++, 1.0f);

	self->mDrawList->AddRect(*pv, *pv2, col, rounding, rounding_corners, thickness);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	AddRectFilled
	@text	See ImGui.

	@in		ImVec2 a
	@in		ImVec2 b
	@opt	number col
	@opt	number rounding
	@opt	number rounding_corners
*/
int	MOAIImDrawList::_AddRectFilled(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	ImVec2 v2;
	ImVec2* pv2 = &v2;
	imvec2_getter(state, idx, &pv2);

	unsigned int col = state.GetValue < unsigned int >(idx++, 0xFFFFFFFF);
	float rounding = state.GetValue < float >(idx++, 0.0f);
	int rounding_corners = state.GetValue < int >(idx++, 0x0F);

	self->mDrawList->AddRectFilled(*pv, *pv2, col, rounding, rounding_corners);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	AddRectFilledMultiColor
	@text	See ImGui.

	@in		ImVec2 a
	@in		ImVec2 b
	@opt	number col_upr_left
	@opt	number col_upr_right
	@opt	number col_bot_right
	@opt	number col_bot_left
*/
int	MOAIImDrawList::_AddRectFilledMultiColor(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	ImVec2 v2;
	ImVec2* pv2 = &v2;
	imvec2_getter(state, idx, &pv2);

	unsigned int col_upr_left = state.GetValue < unsigned int >(idx++, 0xFFFFFFFF);
	unsigned int col_upr_right = state.GetValue < unsigned int >(idx++, 0xFFFFFFFF);
	unsigned int col_bot_right = state.GetValue < unsigned int >(idx++, 0xFFFFFFFF);
	unsigned int col_bot_left = state.GetValue < unsigned int >(idx++, 0xFFFFFFFF);

	self->mDrawList->AddRectFilledMultiColor(*pv, *pv2, col_upr_left, col_upr_right, col_bot_right, col_bot_left);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	AddQuad
	@text	See ImGui.

	@in		ImVec2 a
	@in		ImVec2 b
	@in		ImVec2 c
	@in		ImVec2 d
	@opt	number col
	@opt	number thickness
*/
int	MOAIImDrawList::_AddQuad(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	ImVec2 v2;
	ImVec2* pv2 = &v2;
	imvec2_getter(state, idx, &pv2);

	ImVec2 v3;
	ImVec2* pv3 = &v3;
	imvec2_getter(state, idx, &pv3);

	ImVec2 v4;
	ImVec2* pv4 = &v4;
	imvec2_getter(state, idx, &pv4);

	unsigned int col = state.GetValue < unsigned int >(idx++, 0xFFFFFFFF);
	float thickness = state.GetValue < float >(idx++, 1.0f);

	self->mDrawList->AddQuad(*pv, *pv2, *pv3, *pv4, col, thickness);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	AddQuadFilled
	@text	See ImGui.

	@in		ImVec2 a
	@in		ImVec2 b
	@in		ImVec2 c
	@in		ImVec2 d
	@opt	number col
*/
int	MOAIImDrawList::_AddQuadFilled(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	ImVec2 v2;
	ImVec2* pv2 = &v2;
	imvec2_getter(state, idx, &pv2);

	ImVec2 v3;
	ImVec2* pv3 = &v3;
	imvec2_getter(state, idx, &pv3);

	ImVec2 v4;
	ImVec2* pv4 = &v4;
	imvec2_getter(state, idx, &pv4);

	unsigned int col = state.GetValue < unsigned int >(idx++, 0xFFFFFFFF);

	self->mDrawList->AddQuadFilled(*pv, *pv2, *pv3, *pv4, col);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	AddTriangle
	@text	See ImGui.

	@in		ImVec2 a
	@in		ImVec2 b
	@in		ImVec2 c
	@opt	number col
	@opt	number thickness
*/
int	MOAIImDrawList::_AddTriangle(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	ImVec2 v2;
	ImVec2* pv2 = &v2;
	imvec2_getter(state, idx, &pv2);

	ImVec2 v3;
	ImVec2* pv3 = &v3;
	imvec2_getter(state, idx, &pv3);

	unsigned int col = state.GetValue < unsigned int >(idx++, 0xFFFFFFFF);
	float thickness = state.GetValue < float >(idx++, 1.0f);

	self->mDrawList->AddTriangle(*pv, *pv2, *pv3, col, thickness);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	AddTriangleFilled
	@text	See ImGui.

	@in		ImVec2 a
	@in		ImVec2 b
	@in		ImVec2 c
	@opt	number col
*/
int	MOAIImDrawList::_AddTriangleFilled(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	ImVec2 v2;
	ImVec2* pv2 = &v2;
	imvec2_getter(state, idx, &pv2);

	ImVec2 v3;
	ImVec2* pv3 = &v3;
	imvec2_getter(state, idx, &pv3);

	unsigned int col = state.GetValue < unsigned int >(idx++, 0xFFFFFFFF);

	self->mDrawList->AddTriangleFilled(*pv, *pv2, *pv3, col);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	AddCircle
	@text	See ImGui.

	@in		ImVec2 centre
	@in		number radius
	@opt	number col
	@opt	number num_segments
	@opt	number thickness
*/
int	MOAIImDrawList::_AddCircle(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	float radius = state.GetValue < float >(idx++, 0.0f);
	unsigned int col = state.GetValue < unsigned int >(idx++, 0xFFFFFFFF);
	int num_segments = state.GetValue < int >(idx++, 12);
	float thickness = state.GetValue < float >(idx++, 1.0f);

	self->mDrawList->AddCircle(*pv, radius, col, num_segments, thickness);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	AddCircleFilled
	@text	See ImGui.

	@in		ImVec2 centre
	@in		number radius
	@opt	number col
	@opt	number num_segments
*/
int	MOAIImDrawList::_AddCircleFilled(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	float radius = state.GetValue < float >(idx++, 0.0f);
	unsigned int col = state.GetValue < unsigned int >(idx++, 0xFFFFFFFF);
	int num_segments = state.GetValue < int >(idx++, 12);

	self->mDrawList->AddCircleFilled(*pv, radius, col, num_segments);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	AddText
	@text	See ImGui.

	@in		ImVec2 pos
	@opt	number col
	@opt	string txt
*/
int	MOAIImDrawList::_AddText(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	unsigned int col = state.GetValue < unsigned int >(idx++, 0xFFFFFFFF);
	cc8* txt = state.GetValue < cc8* >(idx++, "");

	self->mDrawList->AddText(*pv, col, txt);

	return 0;
}

// void  AddText(const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL, float wrap_width = 0.0f, const ImVec4* cpu_fine_clip_rect = NULL);
// void  AddPolyline(const ImVec2* points, const int num_points, ImU32 col, bool closed, float thickness, bool anti_aliased);
// void  AddConvexPolyFilled(const ImVec2* points, const int num_points, ImU32 col, bool anti_aliased);
// void  AddBezierCurve(const ImVec2& pos0, const ImVec2& cp0, const ImVec2& cp1, const ImVec2& pos1, ImU32 col, float thickness, int num_segments = 0);

//----------------------------------------------------------------//
/**	@lua	PathClear
	@text	See ImGui.
*/
int	MOAIImDrawList::_PathClear(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U")

	self->mDrawList->PathClear();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	PathLineTo
	@text	See ImGui.

	@in		ImVec2 pos
*/
int	MOAIImDrawList::_PathLineTo(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	self->mDrawList->PathLineTo(*pv);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	PathLineToMergeDuplicate
	@text	See ImGui.

	@in		ImVec2 pos
*/
int	MOAIImDrawList::_PathLineToMergeDuplicate(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	self->mDrawList->PathLineToMergeDuplicate(*pv);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	PathFill
	@text	See ImGui.

	@opt	number col
*/
int	MOAIImDrawList::_PathFill(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U")
	
	unsigned int col = state.GetValue < unsigned int >(2, 0xFFFFFFFF);

	self->mDrawList->PathFill(col);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	PathStroke
	@text	See ImGui.

	@opt	number col
	@opt	boolean closed
	@opt	number thickness
*/
int	MOAIImDrawList::_PathStroke(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U")
	
	int idx = 2;
	unsigned int col = state.GetValue < unsigned int >(idx++, 0xFFFFFFFF);
	bool closed = state.GetValue < bool >(idx++, false);
	float thickness = state.GetValue < float >(idx++, 1.0f);

	self->mDrawList->PathStroke(col, closed, thickness);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	PathArcTo
	@text	See ImGui.

	@in		ImVec2 centre
	@in 	number radius
	@in 	number a_min
	@in 	number a_max
	@opt	number num_segments
*/
int	MOAIImDrawList::_PathArcTo(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	float radius = state.GetValue < float >(idx++, 0.0f);
	float a_min = state.GetValue < float >(idx++, 0.0f);
	float a_max = state.GetValue < float >(idx++, 0.0f);
	int num_segments = state.GetValue < int >(idx++, 10);

	self->mDrawList->PathArcTo(*pv, radius, a_min, a_max, num_segments);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	PathArcToFast
	@text	See ImGui.

	@in		ImVec2 centre
	@in 	number radius
	@in 	number a_min_of_12
	@in 	number a_max_of_12
*/
int	MOAIImDrawList::_PathArcToFast(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	float radius = state.GetValue < float >(idx++, 0.0f);
	int a_min_of_12 = state.GetValue < int >(idx++, 0);
	int a_max_of_12 = state.GetValue < int >(idx++, 0);

	self->mDrawList->PathArcToFast(*pv, radius, a_min_of_12, a_max_of_12);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	PathBezierCurveTo
	@text	See ImGui.

	@in		ImVec2 p1
	@in 	ImVec2 p2
	@in 	ImVec2 p3
	@opt	number num_segments
*/
int	MOAIImDrawList::_PathBezierCurveTo(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	ImVec2 v2;
	ImVec2* pv2 = &v2;
	imvec2_getter(state, idx, &pv2);

	ImVec2 v3;
	ImVec2* pv3 = &v3;
	imvec2_getter(state, idx, &pv3);

	int num_segments = state.GetValue < int >(idx++, 10);

	self->mDrawList->PathBezierCurveTo(*pv, *pv2, *pv3, num_segments);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	PathRect
	@text	See ImGui.

	@in		ImVec2 rect_min
	@in 	ImVec2 rect_max
	@opt 	number rounding
	@opt	number rounding_corners
*/
int	MOAIImDrawList::_PathRect(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U@@@")
	
	ImVec2 v;
	ImVec2* pv = &v;
	int idx = 2;
	imvec2_getter(state, idx, &pv);

	ImVec2 v2;
	ImVec2* pv2 = &v2;
	imvec2_getter(state, idx, &pv2);

	float rounding = state.GetValue < float >(idx++, 0.0f);
	int rounding_corners = state.GetValue < int >(idx++, 0x0F);

	self->mDrawList->PathRect(*pv, *pv2, rounding, rounding_corners);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	ChannelsSplit
	@text	See ImGui.

	@in		number channels_count
*/
int	MOAIImDrawList::_ChannelsSplit(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "UN")
	
	int idx = 2;
	int channels_count = state.GetValue < int >(idx++, 0);

	self->mDrawList->ChannelsSplit(channels_count);

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	ChannelsMerge
	@text	See ImGui.
*/
int	MOAIImDrawList::_ChannelsMerge(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "U")
	
	self->mDrawList->ChannelsMerge();

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	ChannelsSetCurrent
	@text	See ImGui.

	@in		number channel_index
*/
int	MOAIImDrawList::_ChannelsSetCurrent(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImDrawList, "UN")
	
	int idx = 2;
	int channel_index = state.GetValue < int >(idx++, 0);

	self->mDrawList->ChannelsSetCurrent(channel_index);

	return 0;
}
