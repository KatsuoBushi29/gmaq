#pragma once

#include "Affect.h"


class ICreature
{
public:
	ICreature(void);
	virtual ~ICreature(void) {}

	/* *** Get information *** */
	/* for CreatureResource */
	virtual unsigned int		getHealth(void)		= 0;
	virtual unsigned int		getStamina(void)	= 0;
	virtual unsigned int		getEnergy(void)		= 0;
	virtual unsigned int		getWaste(void)		= 0;
	/* for position */
	virtual const posInfo_t*	getPosition(void)	= 0;

	/* *** Set information *** */
	/* for Affect */
	virtual void				addAffect(const affectType_t type, affectBody_t &detail)	= 0;

};

