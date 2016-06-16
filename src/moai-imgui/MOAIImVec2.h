#ifndef	MOAIIMVEC2_H
#define	MOAIIMVEC2_H

#include <moai-core/headers.h>
#include <imgui.h>


class MOAIImVec2 :
	public MOAILuaObject {
private:
	static int	_getX(lua_State* L);
	static int	_getY(lua_State* L);
	static int	_get(lua_State* L);

	static int	_setX(lua_State* L);
	static int	_setY(lua_State* L);
	static int	_set(lua_State* L);

public:
	DECL_LUA_FACTORY(MOAIImVec2)

	ImVec2 mVec2;

	MOAIImVec2();
	~MOAIImVec2();

	MOAIImVec2& operator=(const MOAIImVec2 &v);

	void RegisterLuaClass(MOAILuaState& state);
	void RegisterLuaFuncs(MOAILuaState& state);
};

#endif
