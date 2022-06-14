#pragma once

class i_mem_alloc {
public:
	VFUNC(alloc(uint32_t size), 1, void*(__thiscall*)(void*, uint32_t), size)
	VFUNC(realloc(void* memory, uint32_t size), 3, void*(__thiscall*)(void*, void*, uint32_t), memory, size)
	VFUNC(free(void* memory), 5, void(__thiscall*)(void*, void*), memory)
};