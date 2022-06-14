#pragma once

struct move_data_t {
	bool            m_first_run_of_functions : 1;
	bool            m_game_code_moved_player : 1;
	bool            m_no_air_control : 1;
	c_base_handle	m_player_handle;
	int				m_impulse_command;
	qangle_t		m_view_angles;
	qangle_t		m_abs_view_angles;
	int				m_buttons;
	int				m_old_buttons;
	vec3_t			m_move;
	float			m_max_speed;
	float			m_client_max_speed;
	vec3_t			m_velocity;
	vec3_t			m_trailing_velocity;
	float				m_trailing_velocity_time;
	qangle_t        m_angles;
	qangle_t		m_old_angles;
	float			m_out_step_height;
	vec3_t			m_out_wish_velocity;
	vec3_t			m_out_jump_velocity;
	vec3_t			m_constraint_center;
	float			m_constraint_radius;
	float			m_constraint_width;
	float			m_constraint_speed_factor;
	bool            m_constraint_past_radius;
	vec3_t			m_abs_origin;
};

class c_base_player;

class i_prediction {
public:
	VFUNC(update(int start_frame, bool valid_frame, int incoming_acknowledged, int outgoing_command), 3, void(__thiscall*)(void*, int, bool, int, int), start_frame, valid_frame, incoming_acknowledged, outgoing_command)
	VFUNC(post_entity_packet_received(), 5, void(__thiscall*)(void*))
	VFUNC(post_network_data_received(int commands_acknowledged), 6, void(__thiscall*)(void*, int), commands_acknowledged)
	VFUNC(set_local_view_angles(const qangle_t& view_angles), 13, void(__thiscall*)(void*, const qangle_t&), view_angles)
	VFUNC(check_moving_on_ground(c_base_player* player, float frame_time), 18, void(__thiscall*)(void*, c_base_player*, double), player, frame_time)
	VFUNC(run_command(c_base_player* player, c_user_cmd* cmd, i_move_helper* move_helper), 19, void(__thiscall*)(void*, c_base_player*, c_user_cmd *, i_move_helper*), player, cmd, move_helper)
	VFUNC(setup_move(c_base_player* player, c_user_cmd* cmd, i_move_helper* move_helper, move_data_t* move_data), 20, void(__thiscall*)(void*, c_base_player*, c_user_cmd*, i_move_helper*, move_data_t*), player, cmd, move_helper, move_data)
	VFUNC(finish_move(c_base_player* player, c_user_cmd* cmd, move_data_t* move_data), 21, void(__thiscall*)(void*, c_base_player*, c_user_cmd*, move_data_t*), player, cmd, move_data)

	char						pad0[8];
	bool						m_in_prediction;
	char						pad1[1];
	bool						m_engine_paused;
	bool						m_old_cl_predict_value;
	int							m_prev_start_frame;
	int							m_incoming_packet_number;
	float						m_last_server_world_time_stamp;
	bool						m_first_time_predicted;
	char						pad2[3];
	int							m_commands_predicted;
	int							m_server_commands_acknowledged;
	bool						m_prev_ack_had_errors;
	char						pad3[4];
	int							m_incoming_acknowledged;
	char						pad4[4];
	c_utl_vector<c_base_handle> m_prediction_handles;
	char						pad5[4];
	i_global_vars				m_saved_globals;
};
