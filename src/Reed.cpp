#include "Reed.h"
#include "ReedParameter.h"

#include "Roam.h"


/* *** Common Function *** */
Reed::Reed( LocalSpace	*pLocalSpace,
		    posInfo_t	*pCurrentPosition
			/* , CreatureFactory *pFactory */)
			: Creature(pLocalSpace, pCurrentPosition)
{
	appearanceFactor_t factor = {	
									NONE,
									ROBUST,
								};

	m_pAppearance		= new Appearance(factor);
	m_pAction			= new Roam(pCurrentPosition, &m_resource);

	m_resource.pEnergy	= new Energy(   REED_INIT_ENERGY,
										REED_ENERGY_CAPACITY);
	m_resource.pHealth	= new Resource( REED_INIT_HEALTH,
										REED_MAX_HEALTH,
										REED_POOR_HEALTH,
										REED_POOR_HEALTH );
	m_resource.pStamina	= new Resource( REED_INIT_STAMINA,
										REED_MAX_STAMINA,
										REED_POOR_STAMINA,
										REED_POOR_STAMINA );
	m_resource.pWaste	= new Resource( REED_INIT_WASTE,
										REED_WASTE_CAPACITY,
										REED_EXCRETED_WASTE,
										REED_EXCRETED_WASTE );

	m_pGrounds			= nullptr;
}


Reed::Reed( Energy		*pInitEnergy,
			LocalSpace	*pLocalSpace,
			posInfo_t	*pCurrentPosition
			/* CreatureFactory *pFactory */)
			: Creature(pLocalSpace, pCurrentPosition)
{
	appearanceFactor_t factor = {	
									NONE,
									ROBUST,
								};

	m_pAppearance		= new Appearance(factor);
	m_pAction			= new Roam(pCurrentPosition, &m_resource);

	m_resource.pEnergy	= pInitEnergy;
	m_resource.pHealth	= new Resource( REED_INIT_HEALTH,
										REED_MAX_HEALTH,
										REED_POOR_HEALTH,
										REED_POOR_HEALTH );
	m_resource.pStamina	= new Resource( REED_INIT_STAMINA,
										REED_MAX_STAMINA,
										REED_POOR_STAMINA,
										REED_POOR_STAMINA );
	m_resource.pWaste	= new Resource( REED_INIT_WASTE,
										REED_WASTE_CAPACITY,
										REED_EXCRETED_WASTE,
										REED_EXCRETED_WASTE );

	m_pGrounds			= nullptr;
}


Reed::~Reed(void)
{
	delete m_pAppearance;
	delete m_pAction;

	delete m_resource.pEnergy;
	delete m_resource.pHealth;
	delete m_resource.pStamina;
	delete m_resource.pWaste;
	
	vector<vector<Ground *>>().swap(*m_pGrounds);
}


void Reed::sense(void)
{
	spaceSize_t size;

	/* search grounds around */
	if (nullptr == m_pGrounds) {
		size.mid			= m_position;
		size.frontLength	= REED_SIGHT_LENGTH;
		size.backLength		= REED_SIGHT_LENGTH;
		size.leftLength		= REED_SIGHT_LENGTH;
		size.rightLength	= REED_SIGHT_LENGTH;

		m_pLocalSpace->getGrounds(size, *m_pGrounds);
	}
}


void Reed::action(void)
{

}


void Reed::reflect(void)
{

}


void Reed::update(void)
{

}


/* *** Common Function *** */