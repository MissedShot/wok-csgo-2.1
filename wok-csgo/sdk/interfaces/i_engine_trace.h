#pragma once

class i_engine_trace {
public:
	virtual int	get_point_contents(const vec3_t& pos, bit_flag_t<int> mask = MASK_ALL, i_handle_entity** entity = 0) = 0;
	virtual int	get_point_contents_world_only(const vec3_t& pos, bit_flag_t<int> mask = MASK_ALL) = 0;
	virtual int	get_point_contents_collideable(i_collideable* collideable, const vec3_t& pos) = 0;
	virtual void clip_ray_to_entity(const ray_t& ray, bit_flag_t<uint32_t> mask, i_handle_entity* entity, c_game_trace* trace) = 0;
	virtual void clip_ray_to_collideable(const ray_t& ray, bit_flag_t<uint32_t> mask, i_collideable* collideable, c_game_trace* trace) = 0;
	virtual void trace_ray(const ray_t& ray, bit_flag_t<uint32_t> mask, i_trace_filter* filter, c_game_trace* trace) = 0;
};