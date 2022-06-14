#include "../hooks.h"

void __fastcall hooks::panel::paint_traverse::fn(void* ecx, void* edx, uint32_t id, bool force_repaint, bool allow_force) {
	static const auto original = m_panel->get_original<T>(index);

	original(ecx, id, force_repaint, allow_force);

	{
		static auto draw_panel_id = 0u;

		if (!draw_panel_id) {
			if (FNV1A_RT(interfaces::m_panel->get_name(id)) != FNV1A("MatSystemTopPanel"))
				return;

			draw_panel_id = id;
		}

		if (id != draw_panel_id)
			return;
	}

	render::begin();
}