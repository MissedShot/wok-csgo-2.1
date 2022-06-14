#pragma once

class i_weapon_system {
public:
	VFUNC(get_cs_weapon_data(short item_definition_index), 2, c_cs_weapon_data*(__thiscall*)(void*, short), item_definition_index)
};