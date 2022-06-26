#pragma once

class i_key_values_system {
public:
	VFUNC(register_size(int size), 1, void(__thiscall*)(void*, int), size)
	VFUNC(alloc_key(int size), 2, void* (__thiscall*)(void*, int), size )
	VFUNC(free_key(void* mem), 3, void(__thiscall* )(void*, void*), mem )
	VFUNC(get_symbol(const char* name, bool create = true), 4, int(__thiscall*)(void*, const char*, bool), name, create)
	VFUNC(get_string(int symbol), 5, const char* (__thiscall*)(void*, int), symbol)
	VFUNC(add_key(void* mem, int symbol_name), 6, void(__thiscall*)(void*, void*, int), mem, symbol_name)
	VFUNC(remove_key(void* mem), 7, void(__thiscall*)(void*, void*), mem)
	VFUNC(set_key(const char* name, bool value), 8, void(__thiscall*)(void*, const char*, bool), name, value)
	VFUNC(get_key(const char* name), 9, bool(__thiscall*)(void*, const char*), name)
	VFUNC(get_symbol_sensetive(int& insensitive_symbol, const char* name, bool create = true), 10, int(__thiscall*)(void*, int&, const char*, bool), insensitive_symbol, name, create)
};

class c_key_values {
public:
	~c_key_values();

	VFUNC_SIG(init(const char* key_name), "client.dll", "55 8B EC 51 33 C0 C7 45", void(__thiscall*)(void*, const char*, int, int), key_name, 0, 0)
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
