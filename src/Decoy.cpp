#include "Decoy.h"
#include "DecoyParameter.h"
/* Action */
#include "Roam.h"


Decoy::Decoy( LocalSpace	*pLocalSpace
			, posInfo_t		*pCurrentPosition/* , CreatureFactory *pFactory */) :
		Creature( pLocalSpace, pCurrentPosition)
{
	appearanceFactor_t factor = { NONE, BONY, BAD};

	m_pAppearance		= new Appearance(factor);
	m_pAction			= new Roam(m_pTargetCreature, &m_position, &m_resource);

	m_resource.pEnergy	= new Energy(DECOY_INIT_ENERGY,	DECOY_ENERGY_CAPACITY);
	m_resource.pHealth	= new Resource(DECOY_INIT_HEALTH,	DECOY_MAX_HEALTH,		DECOY_POOR_HEALTH,		DECOY_POOR_HEALTH);
	m_resource.pStamina	= new Resource(DECOY_INIT_STAMINA,	DECOY_MAX_STAMINA,		DECOY_POOR_STAMINA,		DECOY_POOR_STAMINA);
	m_resource.pWaste	= new Resource(DECOY_INIT_WASTE,	DECOY_WASTE_CAPACITY,	DECOY_EXCRETED_WASTE,	DECOY_EXCRETED_WASTE);

	m_pTargetCreature	= NULL;
}


Decoy::~Decoy(void)
{
}


void Decoy::sense(void)
{
	/* Done Nothing */
}


void Decoy::action(void)
{
	resultStatus_t result;
	resultAction_t detail;

	m_pAction->exec();

	do {
		result = m_pAction->get(detail);
		if (true == detail.isValid) {
			m_pAffect->add(detail.type, detail.result);
		}
	} while (EMPTY_NEXT_RESULT != result);
}


void Decoy::reflect(void)
{
	/* Done Nothing */
}


void Decoy::update(void)
{
	/* update resouce */
	updateHealth();
	updateStamina();
	updateEnergy();
	updatePosition();
}
