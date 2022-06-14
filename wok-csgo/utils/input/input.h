#pragma once

enum e_key_mode {
	ON_KEY,
	TOGGLE,
	AWAY_KEY
};

namespace input {
	void init();

	void undo();

	long __stdcall wnd_proc(HWND hwnd, uint32_t msg, uint32_t w_param, uint32_t l_param);

	template <e_key_mode M>
	__declspec(noinline) static bool get_key(uint32_t key) {
		switch (M) {
		case ON_KEY: return HIWORD(GetKeyState(key)); break;
		case TOGGLE: return LOWORD(GetKeyState(key)); break;
		case AWAY_KEY: return !HIWORD(GetKeyState(key)); break;
		}

		return false;
	}

	extern bool m_blocked;

	extern HWND m_hwnd;
	extern WNDPROC m_original_wnd_proc;
};