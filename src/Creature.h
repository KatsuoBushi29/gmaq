#pragma once

#include<vector>
#include"Appearance.h"
#include"LocalSpace.h"
#include"Affect.h"
#include"Action.h"
#include"Ground.h"
#include"CreatureResource.h"

/* virtual define */
class LocalSpace;


class Creature
{
public:
	Creature( LocalSpace *pLocalSpace
			, posInfo_t	*pCurrentPosition
		/* ->, CreatureFactory *pFactory */);
	virtual ~Creature(void);

	/* active function */
	virtual void sense(void) = 0;
	virtual void action(void) = 0;
	virtual void reflect(void) = 0;
	virtual void update(void) = 0;

	/* passive function */
	void affected(affectType_t type, affectBody_t &pBody);

	/* get information */
	const posInfo_t *getPosition(void);
	const creatureResource_t *getResource(void);

	/* debug function */
	void getColor(double &red, double &green, double &blue); /* for debug */

	Appearance *m_pAppearance;

protected:
	/* update resource from affect */
	void Creature::updateHealth(void);
	void Creature::updateStamina(void);
	void Creature::updateEnergy(void);

	/* update position from affect */
	void Creature::updatePosition(void);

	/* class */
	LocalSpace*				m_pLocalSpace;
	Affect*					m_pAffect;
	Action*					m_pAction;
	std::vector<Ground *>*	m_pGrounds;

	/* structure */
	posInfo_t			m_position;
	creatureResource_t	m_resource;	
};