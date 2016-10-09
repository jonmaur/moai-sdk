#ifndef	MOAIIMDRAWLIST_H
#define	MOAIIMDRAWLIST_H

#include <moai-core/headers.h>
#include <imgui.h>


class MOAIImDrawList :
	public MOAILuaObject {
private:
	static int	_PushClipRect(lua_State* L);
	static int	_PushClipRectFullScreen(lua_State* L);
	static int	_PopClipRect(lua_State* L);

	static int	_AddLine(lua_State* L);
	static int	_AddRect(lua_State* L);
	static int	_AddRectFilled(lua_State* L);
	static int	_AddRectFilledMultiColor(lua_State* L);
	static int	_AddQuad(lua_State* L);
	static int	_AddQuadFilled(lua_State* L);
	static int	_AddTriangle(lua_State* L);
	static int	_AddTriangleFilled(lua_State* L);
	static int	_AddCircle(lua_State* L);
	static int	_AddCircleFilled(lua_State* L);
	static int	_AddText(lua_State* L);

	static int	_PathClear(lua_State* L);
	static int	_PathLineTo(lua_State* L);
	static int	_PathLineToMergeDuplicate(lua_State* L);
	static int	_PathFill(lua_State* L);
	static int	_PathStroke(lua_State* L);
	static int	_PathArcTo(lua_State* L);
	static int	_PathArcToFast(lua_State* L);
	static int	_PathBezierCurveTo(lua_State* L);
	static int	_PathRect(lua_State* L);
	
	static int	_ChannelsSplit(lua_State* L);
	static int	_ChannelsMerge(lua_State* L);
	static int	_ChannelsSetCurrent(lua_State* L);

public:
	DECL_LUA_FACTORY(MOAIImDrawList)

	ImDrawList* mDrawList;

	MOAIImDrawList();
	~MOAIImDrawList();

	void RegisterLuaClass(MOAILuaState& state);
	void RegisterLuaFuncs(MOAILuaState& state);
};

#endif
