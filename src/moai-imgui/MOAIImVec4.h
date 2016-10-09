#ifndef	MOAIIMVEC4_H
#define	MOAIIMVEC4_H

#include <moai-core/headers.h>
#include <imgui.h>


class MOAIImVec4 :
	public MOAILuaObject {
private:
	static int	_getX(lua_State* L);
	static int	_getY(lua_State* L);
	static int	_getZ(lua_State* L);
	static int	_getW(lua_State* L);
	static int	_get(lua_State* L);

	static int	_setX(lua_State* L);
	static int	_setY(lua_State* L);
	static int	_setZ(lua_State* L);
	static int	_setW(lua_State* L);
	static int	_set(lua_State* L);

public:
	DECL_LUA_FACTORY(MOAIImVec4)

	ImVec4 mVec4;

	MOAIImVec4();
	~MOAIImVec4();

	MOAIImVec4& operator=(const MOAIImVec4 &v);

	void RegisterLuaClass(MOAILuaState& state);
	void RegisterLuaFuncs(MOAILuaState& state);
};

bool imvec4_getter(MOAILuaState& state, int& idx, ImVec4** out_vec4);

#endif
