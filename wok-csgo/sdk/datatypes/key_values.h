#pragma once

class c_key_values {
public:
	~c_key_values();

	VFUNC_SIG(init(const char* key_name), "client.dll", "55 8B EC 51 33 C0 C7 45", void(__thiscall*)(void*, const char*), key_name)
	VFUNC_SIG(load_from_buffer(const char* resource_name, const char* buf, void* file_sys = nullptr, const char* path_id = nullptr, void* eval_sym_proc = nullptr, void* unk = nullptr), 
		"client.dll", "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89", void(__thiscall*)(void*, const char*, const char*, void*, const char*, void*, void*), resource_name, buf, file_sys, path_id, eval_sym_proc, unk)
	VFUNC_SIG(find_key(const char* name, bool create), "client.dll", "55 8B EC 83 EC 1C 53 8B D9 85 DB", c_key_values*(__thiscall*)(void*, const char*, bool), name, create)

	__forceinline void set_int(const char* name, int value) {
		const auto key = find_key(name, true);
		if (!key)
			return;

		*reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(key) + 0x10) = 2;
		*reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(key) + 0xC) = value;
	}

	__forceinline void set_string(const char* name, const char* a2) {
		const auto key = find_key(name, true);
		if (!key)
			return;

		static const auto set_string_fn = SIG("client.dll", "55 8B EC A1 ? ? ? ? 53 56 57 8B F9 8B 08 8B 01").cast<void(__thiscall*)(void*, const char*)>();

		set_string_fn(key, a2);
	}
};
