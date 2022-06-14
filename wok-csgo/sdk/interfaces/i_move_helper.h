#pragma once

class c_base_player;

class i_move_helper {
public:
	VFUNC(set_host(c_base_player* player), 1, void(__thiscall*)(void*, c_base_player*), player)
	VFUNC(process_impacts(), 4, void(__thiscall*)(void*))
};