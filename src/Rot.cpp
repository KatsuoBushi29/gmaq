#include "Rot.h"

/*** Internal const ***/
const unsigned int	ROT_EMPTY_VALUE			= (0u);
const unsigned int	ROT_TOSOIL_VALUE		= (4u);


Rot::Rot( const posInfo_t*			pMyPosition
		, const creatureResource_t*	pResource
		/* const creatureStatus_t *pStatus : STR,VIT,AGI... */) :
	Action(pMyPosition, pResource)
{
	
}


Rot::~Rot(void)
{

}


void Rot::exec(const Creature* pTargetCrearute, const Ground* pTargetGround)
{
	unsigned int	currValue	= ROT_EMPTY_VALUE;
	resultAction_t	detail;

	/* drop ENERGY to Ground */
	if (ROT_EMPTY_VALUE < m_pMyResource->pEnergy->get()) {
		currValue = m_pMyResource->pEnergy->get();
	/* drop WASTE to Ground */
	} else if (ROT_EMPTY_VALUE < m_pMyResource->pWaste->getValue()) {
		currValue = m_pMyResource->pWaste->getValue();
	} else {
		/* Both resource is empty, do nothing */
		return;
	}
	/* calculatie value */
	detail.isValid	= true;
	detail.type	= TOSOIL;
	if (ROT_TOSOIL_VALUE < currValue) {
		detail.result.toSoil.value = currValue;
	} else {
		detail.result.toSoil.value = ROT_TOSOIL_VALUE;
	}
	this->set(detail);
}


void Rot::dbgGet(double &red, double &green, double &blue)
{
	red		= 0.8;
	green	= 0;
	blue	= 0;
}