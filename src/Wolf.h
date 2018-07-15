#pragma once

#include<queue>
#include"Creature.h"


class Wolf : public Creature
{
public:
	Wolf( LocalSpace *pLocalSpace
		, posInfo_t *pCurrentPosition/* , CreatureFactory *pFactory */);
	Wolf( Energy *pInitEnergy
		, LocalSpace *pLocalSpace
		, posInfo_t *pCurrentPosition/* , CreatureFactory *pFactory */); /* for replicate */
	~Wolf(void);

	/* basic cycle function */
	void sense(void);
	void action(void);
	void reflect(void);
	void update(void);

private:
	void toSoil(void);
	void takeARest(void);
	void procActive(void);
	void procDebility(void);

	/* internal action */
	Creature *decideTarget(void);

	void chaseTarget(void);
	void movePosition(void);
	void replicate(void);
	void takeEnergy(void);
	void recoverStamina(void);
	void repairHealth(void);

	/* internal reflect */
	void separateAbsorbedEnergy(void);
	void returnInjuredHealth(void);

	/* internal update */
	void updateAction(void);

	std::queue<const Creature *>*	m_pDstCreatures;
	Creature*						m_pTargetCreature;
};