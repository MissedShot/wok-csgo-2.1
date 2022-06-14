#pragma once

class i_global_vars {
public:
	float m_real_time;
	int   m_frame_count;
	float m_absolute_frame_time;
	float m_absolute_frame_start_time_std_dev;
	float m_cur_time;
	float m_frame_time;
	int   m_max_clients;
	int   m_tick_count;
	float m_interval_per_tick;
	float m_interpolation_amount;
	int   m_sim_ticks_this_frame;
	int   m_network_protocol;
	void* m_save_data;
	bool  m_client;
	bool  m_remote_client;
};