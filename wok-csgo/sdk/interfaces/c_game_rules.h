#pragma once

class i_game_rules {
public:
	NETVAR(get_warmup_period(), bool, "CCSGameRulesProxy->m_bWarmupPeriod")
	NETVAR(get_freeze_period(), bool, "CCSGameRulesProxy->m_bFreezePeriod")
	NETVAR(is_valve_ds(), bool, "CCSGameRulesProxy->m_bIsValveDS")
	NETVAR(is_bomb_planted(), bool, "CCSGameRulesProxy->m_bBombPlanted")
};
