#pragma once

class i_client_networkable;
using create_client_class_fn = i_client_networkable*(__cdecl*)(int, int);
using create_event_fn = i_client_networkable*(__cdecl*)();

struct client_class_t {
	create_client_class_fn	m_create_fn;
	create_event_fn			m_create_event_fn;
	const char*					m_network_name;
	recv_table_t*				m_recv_table;
	client_class_t*			m_next;
	e_class_id					m_class_id;
};