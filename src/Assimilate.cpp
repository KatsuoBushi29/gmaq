#include "Assimilate.h"

const unsigned int	ASS_SPOILED_ENERGY	= (0u);


Assimilate::Assimilate( const posInfo_t*			pMyPosition,
						const creatureResource_t*	pResource )
		: Action(pMyPosition, pResource)
{
}


Assimilate::~Assimilate(void)
{
}


void Assimilate::exec(const Creature* pTargetCrearute, const Ground* pTargetGround)
{
	unsigned int	energy	= pTargetGround->getStoredEnergy();
	resultAction_t	detail;

	if (ASS_SPOILED_ENERGY < energy) {
		detail.isValid	= true;
		detail.result.
		this->set();
	}
	else {
	}
}