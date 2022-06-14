#pragma once

class i_localize {
public:
	VFUNC(find(const char* token_name), 11, wchar_t*(__thiscall*)(void*, const char*), token_name)
	VFUNC(find_safe(const char* token_name), 12, wchar_t*(__thiscall*)(void*, const char*), token_name)
};