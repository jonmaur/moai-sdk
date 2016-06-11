#include <moai-imgui/MOAIImVec2.h>



int	MOAIImVec2::_getX(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec2, "U")
	
	state.Push(self->mVec2.x);

	return 1;
}

int	MOAIImVec2::_getY(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec2, "U")

	state.Push(self->mVec2.y);

	return 1;
}

int	MOAIImVec2::_get(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec2, "U")

	state.Push(self->mVec2.x);
	state.Push(self->mVec2.y);

	return 2;
}

int	MOAIImVec2::_setX(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec2, "UN")

	self->mVec2.x = state.GetValue < float >(2, 0.0f);

	return 0;
}

int	MOAIImVec2::_setY(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec2, "UN")

	self->mVec2.y = state.GetValue < float >(2, 0.0f);

	return 0;
}

int	MOAIImVec2::_set(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec2, "UN")

	self->mVec2.x = state.GetValue < float >(2, 0.0f);
	self->mVec2.y = state.GetValue < float >(3, self->mVec2.x);

	return 0;
}
//----------------------------------------------------------------//
MOAIImVec2::MOAIImVec2() {
	mVec2.x = mVec2.y = 0.0f;

	RTTI_SINGLE(MOAIImVec2)
}

//----------------------------------------------------------------//
MOAIImVec2::~MOAIImVec2() {
}


void MOAIImVec2::RegisterLuaClass(MOAILuaState& state) {

	MOAILuaObject::RegisterLuaClass(state);
}

void MOAIImVec2::RegisterLuaFuncs(MOAILuaState& state) {

	MOAILuaObject::RegisterLuaFuncs(state);

	luaL_Reg regTable[] = {
		{ "getX",						_getX },
		{ "getY",						_getY },
		{ "get",						_get  },
		{ "setX",						_setX },
		{ "setY",						_setY },
		{ "set",						_set  },
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);

}