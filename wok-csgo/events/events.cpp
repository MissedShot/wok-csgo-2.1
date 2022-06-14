#include "events.h"

#define ADD_CALLBACK(name, fn) m_callbacks[FNV1A(name)] = fn; interfaces::m_event_manager->add_listener(&m_listener, _(name), false);

namespace events {
	void c_listener::fire_game_event(i_game_event* event) { m_callbacks.at(FNV1A_RT(event->get_name()))(event); }

	void init() {
		ADD_CALLBACK("player_hurt", player_hurt);
	}

	void undo() { interfaces::m_event_manager->remove_listener(&m_listener); }

	c_listener m_listener;

	std::unordered_map<uint32_t, std::function<void(i_game_event*)>> m_callbacks;
}