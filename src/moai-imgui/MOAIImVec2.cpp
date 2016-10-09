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

MOAIImVec2& MOAIImVec2::operator=(const MOAIImVec2 &v)
{
	this->mVec2 = v.mVec2;
	return *this;
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
			float x = state.GetField < float>(idx, "x", 0.0f);
			float y = state.GetField < float>(idx, "y", 0.0f);

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
	if (state.IsType(idx, LUA_TNUMBER) && state.IsType(idx + 1, LUA_TNUMBER))
	{
		float x = state.GetValue<float>(idx++, 0.0f);
		float y = state.GetValue<float>(idx++, 0.0f);

		(*out_vec2)->x = x;
		(*out_vec2)->y = y;
		return true;
	}

	return false;
}
