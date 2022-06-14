#pragma once

class i_debug_overlay {
public:
	VFUNC(add_box_overlay(const vec3_t& origin, const vec3_t& mins, const vec3_t& maxs, const qangle_t& rotation, const col_t& clr, float duration), 1,
		void(__thiscall*)(void*, const vec3_t&, const vec3_t&, const vec3_t&, const qangle_t&, int, int, int, int, float), origin, mins, maxs, rotation, clr.r(), clr.g(), clr.b(), clr.a(), duration)
	VFUNC(add_line_overlay(const vec3_t& from, const vec3_t& to, const col_t& clr, bool no_depth_test, float duration), 4,
		void(__thiscall*)(void*, const vec3_t&, const vec3_t&, int, int, int, int, bool, float), from, to, clr.r(), clr.g(), clr.b(), clr.a(), no_depth_test, duration)
	VFUNC(add_capsule_overlay(const vec3_t& mins, const vec3_t& maxs, float& radius, const col_t& clr, float duration, bool ignorez), 23,
		void(__thiscall*)(void*, const vec3_t&, const vec3_t&, float&, int, int, int, int, float, bool, bool), mins, maxs, radius, clr.r(), clr.g(), clr.b(), clr.a(), duration, false, ignorez)
};