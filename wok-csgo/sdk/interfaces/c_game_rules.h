#pragma once

class i_game_rules {
public:
	NETVAR(m_warmup_period(), bool, "CCSGameRulesProxy->m_bWarmupPeriod")
	NETVAR(m_freeze_period(), bool, "CCSGameRulesProxy->m_bFreezePeriod")
	NETVAR(m_is_valve_ds(), bool, "CCSGameRulesProxy->m_bIsValveDS")
	NETVAR(m_bomb_planted(), bool, "CCSGameRulesProxy->m_bBombPlanted")
};