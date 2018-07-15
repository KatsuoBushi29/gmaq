#pragma once

#include <vector>
#include "Creature.h"


class Reed : public Creature
{
public:
	Reed( LocalSpace *pLocalSpace
		, posInfo_t *pCurrentPosition/* , CreatureFactory *pFactory */);
	Reed( Energy *pInitEnergy
		, LocalSpace *pLocalSpace
		, posInfo_t *pCurrentPosition/* , CreatureFactory *pFactory */); /* for replicate */
	~Reed(void);

	void sense(void);
	void action(void);
	void reflect(void);
	void update(void);

private:
	std::vector<std::vector<Ground *>>*	m_pGrounds;
};

