#include "common_includes.h"
#include "hooks/hooks.h"
#include "events/events.h"
#include "globals.h"

int __stdcall undo() {
	events::undo();

	hooks::undo();

	input::undo();

	return 1;
}

unsigned long __stdcall init(LPVOID module) {
	do {
		memory::get_all_modules();

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	} while (memory::m_modules.find(FNV1A("serverbrowser.dll")) == memory::m_modules.end());

	globals::m_local = *SIG("client.dll", "8B 0D ? ? ? ? 83 FF FF 74 07").self_offset(0x2).cast<c_local_player*>();

	interfaces::init();

	input::init();

	render::init();

	netvars::init();

	cfg::init();

	hooks::init();

	events::init();

	while (!input::get_key<ON_KEY>(VK_DELETE)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

	undo();

	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(module), 0);
}

int __stdcall DllMain(HMODULE module, unsigned long reason_for_call, void* reserved) {
	if (reason_for_call != DLL_PROCESS_ATTACH)
		return reserved || reason_for_call != DLL_PROCESS_DETACH ? 0 : undo();

	DisableThreadLibraryCalls(module);

	if (const auto thread = CreateThread(0, 0, init, module, 0, 0)) {
		CloseHandle(thread);
	}

	return 1;
}