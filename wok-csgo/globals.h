#pragma once
#include "common_includes.h"
#include "sdk/interfaces.h"
#include "singleton.h"
#include "menu/menu.h"

namespace globals {
	namespace angles {
		extern qangle_t		m_view;
		extern qangle_t		m_anim;
	}

	extern c_local_player	m_local;
	extern c_user_cmd*		m_cur_cmd;
	extern bool				m_packet;
}