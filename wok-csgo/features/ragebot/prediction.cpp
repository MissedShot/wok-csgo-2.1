#include "../features.h"

void c_engine_prediction::update() {
	if (interfaces::m_client_state->m_delta_tick <= 0)
		return;

	interfaces::m_prediction->update(
		interfaces::m_client_state->m_delta_tick, true,
		interfaces::m_client_state->m_last_command_ack, interfaces::m_client_state->m_last_outgoing_command + interfaces::m_client_state->m_choked_commands
	);
}

void c_engine_prediction::predict() {
	if (!globals::m_local->is_alive())
		return;

	m_player = globals::m_local;
	*m_random_seed = globals::m_cur_cmd->m_random_seed;

	interfaces::m_prediction->m_in_prediction = true;
	interfaces::m_prediction->m_first_time_predicted = false;

	interfaces::m_global_vars->m_cur_time = TICKS_TO_TIME(globals::m_local->get_tick_base());
	interfaces::m_global_vars->m_frame_time = globals::m_local->get_flags().has(FL_FROZEN) ? 0.f : interfaces::m_global_vars->m_interval_per_tick;

	interfaces::m_move_helper->set_host(globals::m_local);

	interfaces::m_game_movement->start_track_prediction_errors(globals::m_local);

	interfaces::m_game_movement->process_movement(globals::m_local, m_move_data);

	interfaces::m_prediction->finish_move(globals::m_local, globals::m_cur_cmd, m_move_data);

	interfaces::m_game_movement->finish_track_prediction_errors(globals::m_local);

	interfaces::m_move_helper->set_host(nullptr);

	m_player = nullptr;
	*m_random_seed = -1;

	const auto weapon = globals::m_local->get_active_weapon();
	if (!weapon) {
		m_spread = m_inaccuracy = 0.f;
		return;
	}

	weapon->update_accuracy();

	m_spread = weapon->get_spread();

	m_inaccuracy = weapon->get_inaccuracy();
}

void c_engine_prediction::process() {
	m_backup.store();

	m_player = globals::m_local;
	*m_random_seed = globals::m_cur_cmd->m_random_seed;

	interfaces::m_global_vars->m_cur_time = TICKS_TO_TIME(globals::m_local->get_tick_base());
	interfaces::m_global_vars->m_frame_time = interfaces::m_global_vars->m_interval_per_tick;

	interfaces::m_game_movement->start_track_prediction_errors(globals::m_local);

	interfaces::m_prediction->setup_move(globals::m_local, globals::m_cur_cmd, interfaces::m_move_helper, m_move_data);

	predict();
}

void c_engine_prediction::restore() {
	m_player = nullptr;
	*m_random_seed = -1;

	m_backup.restore();
}
