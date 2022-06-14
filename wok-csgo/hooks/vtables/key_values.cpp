#include "../hooks.h"

void* __fastcall hooks::key_values_system::alloc_key_values_memory::fn(void* ecx, void* edx, int size) {
	static const auto original = m_key_values->get_original<T>(index);

	static const auto alloc_key_values_engine = SIG("engine.dll", "FF 52 04 85 C0 74 0C 56").self_offset(0x3);
	static const auto alloc_key_values_client = SIG("client.dll", "FF 52 04 85 C0 74 0C 56").self_offset(0x3);

	const auto ret = memory::stack_t().ret();
	if (ret == alloc_key_values_engine || ret == alloc_key_values_client)
		return nullptr;

	return original(ecx, size);
}