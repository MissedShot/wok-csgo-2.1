#pragma once

using create_interface_fn_t = uintptr_t*(__cdecl*)(const char* name, int* code);

class i_app_system {
public:
	virtual bool            connect(create_interface_fn_t factory) = 0;
	virtual void            disconnect() = 0;
	virtual void*			query_interface(const char* name) = 0;
	virtual int				init() = 0;
	virtual void            shutdown() = 0;
	virtual const void*		get_dependencies() = 0;
	virtual int				get_tier() = 0;
	virtual void            reconnect(create_interface_fn_t factory, const char* name) = 0;
	virtual void			pad0() = 0;
	virtual void			pad1() = 0;
};

class i_cvar_system : public i_app_system {
public:
	virtual int				allocate_dll_identifier() = 0;
	virtual void			register_cmd(c_cvar* cvar) = 0;
	virtual void			unregister_cmd(c_cvar* cvar) = 0;

	template <typename... A>
	VFUNC(console_print(const col_t& clr, const char* txt, A... args), 25, void(__cdecl*)(void*, const col_t&, const char*, ...), clr, txt, args...)

	__forceinline c_cvar* find_var(uint32_t hash) {
		for (auto it = m_cmd_list_start; it; it = it->m_next) {
			if (FNV1A_RT(it->m_name) != hash)
				continue;

			return it;
		}

		return nullptr;
	}

	c_utl_vector<change_callback1_t>	m_global_change_callbacks;
	char								pad0[28];
	c_cvar*								m_cmd_list_start;
};
