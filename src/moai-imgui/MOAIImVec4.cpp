#include <moai-imgui/MOAIImVec4.h>



int	MOAIImVec4::_getX(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec4, "U")
	
	state.Push(self->mVec4.x);

	return 1;
}

int	MOAIImVec4::_getY(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec4, "U")

	state.Push(self->mVec4.y);

	return 1;
}

int	MOAIImVec4::_getZ(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec4, "U")

	state.Push(self->mVec4.z);

	return 1;
}

int	MOAIImVec4::_getW(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec4, "U")

	state.Push(self->mVec4.w);

	return 1;
}

int	MOAIImVec4::_get(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec4, "U")

	state.Push(self->mVec4.x);
	state.Push(self->mVec4.y);
	state.Push(self->mVec4.z);
	state.Push(self->mVec4.w);

	return 4;
}

int	MOAIImVec4::_setX(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec4, "UN")

	self->mVec4.x = state.GetValue < float >(2, 0.0f);

	return 0;
}

int	MOAIImVec4::_setY(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec4, "UN")

	self->mVec4.y = state.GetValue < float >(2, 0.0f);

	return 0;
}

int	MOAIImVec4::_setZ(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec4, "UN")

	self->mVec4.z = state.GetValue < float >(2, 0.0f);

	return 0;
}

int	MOAIImVec4::_setW(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec4, "UN")

	self->mVec4.w = state.GetValue < float >(2, 0.0f);

	return 0;
}

int	MOAIImVec4::_set(lua_State* L) {
	MOAI_LUA_SETUP(MOAIImVec4, "UN")

	self->mVec4.x = state.GetValue < float >(2, 0.0f);
	self->mVec4.y = state.GetValue < float >(3, self->mVec4.x);
	self->mVec4.z = state.GetValue < float >(4, self->mVec4.x);
	self->mVec4.w = state.GetValue < float >(5, self->mVec4.x);

	return 0;
}
//----------------------------------------------------------------//
MOAIImVec4::MOAIImVec4() {
	mVec4.x = mVec4.y = mVec4.z = mVec4.w = 0.0f;

	RTTI_SINGLE(MOAIImVec4)
}

//----------------------------------------------------------------//
MOAIImVec4::~MOAIImVec4() {
}


void MOAIImVec4::RegisterLuaClass(MOAILuaState& state) {

	MOAILuaObject::RegisterLuaClass(state);
}

void MOAIImVec4::RegisterLuaFuncs(MOAILuaState& state) {

	MOAILuaObject::RegisterLuaFuncs(state);

	luaL_Reg regTable[] = {
		{ "getX",						_getX },
		{ "getY",						_getY },
		{ "getZ",						_getZ },
		{ "getW",						_getW },
		{ "get",						_get  },
		{ "setX",						_setX },
		{ "setY",						_setY },
		{ "setZ",						_setZ },
		{ "setW",						_setW },
		{ "set",						_set  },
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);

}