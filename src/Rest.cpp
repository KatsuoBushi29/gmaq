#include "Rest.h"

/*  */
const unsigned int	REST_EMPTY_ENERGY		= (0u);
const unsigned int	REST_CONSUME_ENERGY		= (4u);


Rest::Rest( const posInfo_t*			pMyPosition,
			const creatureResource_t*	pResource )
		: Action(pMyPosition, pResource)
{
}


Rest::~Rest(void)
{
}


void Rest::exec(const Creature* pTargetCrearute, const Ground* pTargetGround)
{
	unsigned int		consumedEnergy	= REST_EMPTY_ENERGY;
	unsigned int		currEnergy		= m_pMyResource->pEnergy->get();
	ResourceStatus_t	staminaStatus	= m_pMyResource->pStamina->getStatus();
	resultAction_t		detail;

	if ((RESOURCE_POOR == staminaStatus) ||
		(RESOURCE_EMPTY == staminaStatus)) {
		/* calculate energy */
		if (REST_CONSUME_ENERGY > currEnergy) {
			consumedEnergy = currEnergy;
		}
		else {
			consumedEnergy = REST_CONSUME_ENERGY;
		}
		/* set result */
		if (REST_EMPTY_ENERGY < consumedEnergy) {
			/* add recover stamina */
			detail.isValid				= true;
			detail.type					= RECOVER;
			detail.result.recover.value	= consumedEnergy;
			this->set(detail);
			/* add consume energy */
			detail.isValid				= true;
			detail.type					= CONSUME_ENERGY;
			detail.result.consume.value	= consumedEnergy;
			this->set(detail);
		}
	}
}


void Rest::dbgGet(double &red, double &green, double &blue)
{
	red		= 0;
	green	= 0;
	blue	= 1.0;
}