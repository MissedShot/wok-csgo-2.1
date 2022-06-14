#include "../hooks.h"

bool __fastcall hooks::renderable::setup_bones::fn(i_client_renderable* ecx, void* edx, matrix3x4_t* bones, int max_bones, int mask, float time) {
	static const auto original = m_renderable->get_original<T>(index);

	return original(ecx, bones, max_bones, mask, time);
}