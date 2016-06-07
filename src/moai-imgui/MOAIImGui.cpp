#include <moai-imgui/MOAIImGui.h>


//----------------------------------------------------------------//
MOAIImGui::MOAIImGui() {

	RTTI_SINGLE(MOAILuaObject)
}

//----------------------------------------------------------------//
MOAIImGui::~MOAIImGui() {
}

void MOAIImGui::RegisterLuaClass(MOAILuaState& state) {

	//state.SetField(-1, "EASE_IN", (u32)ZLInterpolate::kEaseIn);

	luaL_Reg regTable[] = {
		{ "ShowTestWindow",				_ShowTestWindow },
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int MOAIImGui::_ShowTestWindow(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "B");

	bool open = state.GetValue < bool >(1, true);

	ImGui::ShowTestWindow(&open);

	state.Push(open);

	return 1;
}
