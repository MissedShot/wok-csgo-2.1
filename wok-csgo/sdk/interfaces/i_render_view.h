#pragma once

class i_render_view {
public:
	VFUNC(set_blend(float value), 4, void(__thiscall*)(void*, float), value)
	VFUNC(set_clr(float* value), 6, void(__thiscall*)(void*, float*), value)
};