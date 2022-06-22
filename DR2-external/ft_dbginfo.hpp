#pragma once
#include "osmium/Cheat/Feature/feature.hpp"

class ft_dbginfo : public feature
{

public:

	void on_first_activation() override {}

	void on_enable() override {}

	void on_disable() override;

	void on_render() override;

	void tick() override {}

private:

	uint32_t m_iCurrentOption = 1;
	bool m_bMaxAttributes = false;
	bool m_bWeaponPatch = false;
	bool m_bZombieAttack = false;
	bool m_bZombieFreeze = false;
	bool m_bRevealNotebook = false;
	bool m_bUnlockCards = false;
	bool m_bFreezeTime = false;
	bool m_bTimeHook = false;
};
