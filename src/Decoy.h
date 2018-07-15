#pragma once

#include "Creature.h"


class Decoy : public Creature
{
public:
	Decoy(LocalSpace *pLocalSpace
		, posInfo_t *pCurrentPosition/* , CreatureFactory *pFactory */);
	~Decoy(void);

	/* active function */
	void sense(void);
	void action(void);
	void reflect(void);
	void update(void);

private:
	Creature*	m_pTargetCreature;
};

