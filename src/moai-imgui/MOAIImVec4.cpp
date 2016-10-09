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

MOAIImVec4& MOAIImVec4::operator=(const MOAIImVec4 &v)
{
	this->mVec4 = v.mVec4;
	return *this;
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
			float x = state.GetField < float>(idx, "x", 0.0f);
			float y = state.GetField < float>(idx, "y", 0.0f);
			float z = state.GetField < float>(idx, "z", 0.0f);
			float w = state.GetField < float>(idx, "w", 0.0f);

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
	if (state.IsType(idx, LUA_TNUMBER) && state.IsType(idx + 1, LUA_TNUMBER) && state.IsType(idx + 2, LUA_TNUMBER) && state.IsType(idx + 3, LUA_TNUMBER))
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
