#include "interfaces.h"

namespace interfaces {
	void init() {
		m_client_dll = get<i_base_client_dll*>(FNV1A("client.dll"), FNV1A("VClient018"));
		m_engine = get<i_engine_client*>(FNV1A("engine.dll"), FNV1A("VEngineClient014"));
		m_entity_list = get<i_client_entity_list*>(FNV1A("client.dll"), FNV1A("VClientEntityList003"));

		m_client_mode = **memory::get_vfunc<memory::address_t>(m_client_dll, 10).self_offset(0x5).cast<i_client_mode***>();
		m_global_vars = **memory::get_vfunc<memory::address_t>(m_client_dll, 11).self_offset(0xA).cast<i_global_vars***>();
		m_client_state = **memory::get_vfunc<memory::address_t>(m_engine, 12).self_offset(0x10).cast<i_client_state***>();

		m_mem_alloc = *EXPORT("tier0.dll", "g_pMemAlloc").cast<i_mem_alloc**>();

		m_model_info = get<i_model_info*>(FNV1A("engine.dll"), FNV1A("VModelInfoClient004"));
		m_surface = get<i_surface*>(FNV1A("vguimatsurface.dll"), FNV1A("VGUI_Surface031"));

		m_input = *SIG("client.dll", "B9 ? ? ? ? 8B 40 38 FF D0 84 C0 0F 85").self_offset(0x1).cast<i_input**>();
		m_move_helper = **SIG("client.dll", "8B 0D ? ? ? ? 8B 45 ? 51 8B D4 89 02 8B 01").self_offset(0x2).cast<i_move_helper***>();

		m_prediction = get<i_prediction*>(FNV1A("client.dll"), FNV1A("VClientPrediction001"));
		m_game_movement = get<i_game_movement*>(FNV1A("client.dll"), FNV1A("GameMovement001"));
		m_debug_overlay = get<i_debug_overlay*>(FNV1A("engine.dll"), FNV1A("VDebugOverlay004"));
		m_cvar_system = get<i_cvar_system*>(FNV1A("vstdlib.dll"), FNV1A("VEngineCvar007"));
		m_event_manager = get<i_game_event_manager*>(FNV1A("engine.dll"), FNV1A("GAMEEVENTSMANAGER002"));
		m_trace_system = get<i_engine_trace*>(FNV1A("engine.dll"), FNV1A("EngineTraceClient004"));
		m_surface_data = get<i_surface_data*>(FNV1A("vphysics.dll"), FNV1A("VPhysicsSurfaceProps001"));
		m_input_system = get<i_input_system*>(FNV1A("inputsystem.dll"), FNV1A("InputSystemVersion001"));

		m_game_rules = *SIG("client.dll", "A1 ? ? ? ? 85 C0 0F 84 ? ? ? ? 80 B8 ? ? ? ? ? 74 7A").self_offset(0x1).cast<i_game_rules***>();

		m_game_types = get<i_game_types*>(FNV1A("matchmaking.dll"), FNV1A("VENGINE_GAMETYPES_VERSION002"));
		m_model_cache = get<i_mdl_cache*>(FNV1A("datacache.dll"), FNV1A("MDLCache004"));
		m_model_render = get<i_model_render*>(FNV1A("engine.dll"), FNV1A("VEngineModel016"));
		m_material_system = get<i_material_system*>(FNV1A("materialsystem.dll"), FNV1A("VMaterialSystem080"));

		m_glow_manager = *SIG("client.dll", "0F 11 05 ? ? ? ? 83 C8 01").self_offset(0x3).cast<i_glow_object_manager**>();
		m_beams = *SIG("client.dll", "B9 ? ? ? ? A1 ? ? ? ? FF 10 A1 ? ? ? ? B9").self_offset(0x1).cast<i_view_render_beams**>();
		m_weapon_system = *SIG("client.dll", "8B 35 ? ? ? ? FF 10 0F B7 C0").self_offset(0x2).cast<i_weapon_system**>();
		m_player_resource = *SIG("client.dll", "8B 3D ? ? ? ? 85 FF 0F 84 ? ? ? ? 81 C7").self_offset(0x2).cast<i_cs_player_resource***>();

		m_localize = get<i_localize*>(FNV1A("localize.dll"), FNV1A("Localize_001"));
		m_panel = get<i_panel*>(FNV1A("vgui2.dll"), FNV1A("VGUI_Panel009"));
		m_render_view = get<i_render_view*>(FNV1A("engine.dll"), FNV1A("VEngineRenderView014"));

		if (const auto shader_device = get<uintptr_t**>(FNV1A("shaderapidx9.dll"), FNV1A("ShaderDevice001"))) {
			if (const auto device_table = shader_device[0]) {
				if (const auto shutdown_device = device_table[37]) {
					m_d3d_device = **reinterpret_cast<IDirect3DDevice9***>(shutdown_device + 0x2);
				}
			}
		}
	}

	i_base_client_dll*		m_client_dll = nullptr;
	i_engine_client*		m_engine = nullptr;
	i_client_entity_list*	m_entity_list = nullptr;
	i_client_mode*			m_client_mode = nullptr;
	i_global_vars*			m_global_vars = nullptr;
	i_client_state*			m_client_state = nullptr;
	i_mem_alloc*			m_mem_alloc = nullptr;
	i_model_info*			m_model_info = nullptr;
	i_surface*				m_surface = nullptr;
	i_input*				m_input = nullptr;
	i_move_helper*			m_move_helper = nullptr;
	i_prediction*			m_prediction = nullptr;
	i_game_movement*		m_game_movement = nullptr;
	i_debug_overlay*		m_debug_overlay = nullptr;
	i_cvar_system*			m_cvar_system = nullptr;
	i_game_event_manager*	m_event_manager = nullptr;
	i_engine_trace*			m_trace_system = nullptr;
	i_surface_data*			m_surface_data = nullptr;
	i_input_system*			m_input_system = nullptr;
	i_game_rules**			m_game_rules = nullptr;
	i_game_types*			m_game_types = nullptr;
	i_mdl_cache*			m_model_cache = nullptr;
	i_model_render*			m_model_render = nullptr;
	i_material_system*		m_material_system = nullptr;
	i_glow_object_manager*	m_glow_manager = nullptr;
	i_view_render_beams*	m_beams = nullptr;
	i_weapon_system*		m_weapon_system = nullptr;
	i_cs_player_resource**	m_player_resource = nullptr;
	i_localize*				m_localize = nullptr;
	i_panel*				m_panel = nullptr;
	i_render_view*			m_render_view = nullptr;

	IDirect3DDevice9*		m_d3d_device = nullptr;
}
