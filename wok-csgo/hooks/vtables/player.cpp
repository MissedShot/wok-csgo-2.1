#include "../hooks.h"

qangle_t* __fastcall hooks::player::eye_angles::fn(c_cs_player* ecx, void* edx) {
	static const auto original = m_player->get_original<T>(index);

	if (ecx != globals::m_local)
		return original(ecx);

	static const auto return_to_anim_state_yaw = SIG("client.dll", "F3 0F 10 55 ? 51 8B 8E ? ? ? ?");
	static const auto return_to_anim_state_pitch = SIG("client.dll", "8B CE F3 0F 10 00 8B 06 F3 0F 11 45 ? FF 90 ? ? ? ? F3 0F 10 55 ?");

	const auto ret = memory::stack_t().ret();
	if (ret == return_to_anim_state_yaw
		|| ret == return_to_anim_state_pitch)
		return &globals::angles::m_anim;

	return original(ecx);
}