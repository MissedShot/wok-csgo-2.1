#include "../hooks.h"

void* __fastcall hooks::key_values_system::alloc_key_values_memory::fn(void* ecx, void* edx, int size) {
	static const auto original = m_key_values->get_original<T>(index);

	static const auto alloc_key_values_engine = SIG("engine.dll", "E8 ? ? ? ? 83 C4 08 84 C0 75 10 FF 75 0C").self_rel32().self_offset(0x4A);
	static const auto alloc_key_values_client = SIG("client.dll", "E8 ? ? ? ? 83 C4 08 84 C0 75 10").self_rel32().self_offset(0x3E);

	const auto ret = memory::stack_t().ret();
	if (ret == alloc_key_values_engine || ret == alloc_key_values_client)
		return nullptr;

	return original(ecx, size);
}