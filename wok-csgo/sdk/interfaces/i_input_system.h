#pragma once

class i_input_system {
public:
	VFUNC(enable_input(bool enable), 11, void(__thiscall*)(void*, bool), enable)
	VFUNC(reset_input_state(), 39, void(__thiscall*)(void*))
};