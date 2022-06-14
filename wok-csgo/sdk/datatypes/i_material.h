#pragma once

class i_material {
public:
	virtual const char*	get_name() const = 0;
	virtual const char*	get_texture_group_name() const = 0;

	VFUNC(find_var(const char* name, bool* found, bool complain = true), 11, i_material_var*(__thiscall*)(void*, const char*, bool*, bool), name, found, complain)
	VFUNC(alpha_modulate(float alpha), 27, void(__thiscall*)(void*, float), alpha)
	VFUNC(color_modulate(float red, float green, float blue), 28, void(__thiscall*)(void*, float, float, float), red, green, blue)
	VFUNC(set_flag(int flag, bool value), 29, void(__thiscall*)(void*, int, bool), flag, value)
	VFUNC(is_error_material(), 42, bool(__thiscall*)(void*))
};