#include "../hooks.h"

void __fastcall hooks::surface::lock_cursor::fn(i_surface* ecx, void* edx) {
	static const auto original = m_surface->get_original<T>(index);

	return input::m_blocked ? ecx->unlock_cursor() : original(ecx);
}