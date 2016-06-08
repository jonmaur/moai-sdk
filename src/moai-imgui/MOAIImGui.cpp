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
		{ "Begin",						_Begin },
		{ "End",						_End },
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

//bool          Begin(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0);
int MOAIImGui::_Begin(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "S");

	cc8* name = state.GetValue < cc8* >(1, "MOAIImGui");
	bool open = state.GetValue < bool >(2, true);
	int flags = state.GetValue < ImGuiWindowFlags >(3, 0);

	bool ret = ImGui::Begin(name, &open, flags);

	state.Push(ret);
	state.Push(open);

	return 2;
}

int MOAIImGui::_End(lua_State* L)
{
	MOAI_LUA_SETUP_SINGLE(MOAIImGui, "");

	ImGui::End();

	return 0;
}
