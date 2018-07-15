#include"Creature.h"
#include"LocalSpace.h"

using namespace std;


Creature::Creature(  LocalSpace *pLocalSpace
					, posInfo_t	*pCurrentPosition
				/* -> CreatureFactory *pFactory */)
				: m_pLocalSpace(pLocalSpace)
{
	m_position.xHorPos	= pCurrentPosition->xHorPos;
	m_position.yHorPos	= pCurrentPosition->yHorPos;
	
	m_pAffect			= new Affect();
	m_pGrounds			= nullptr;
}


Creature::~Creature(void)
{
	if (nullptr != m_resource.pEnergy) {
		delete m_resource.pEnergy;
	}
	if (nullptr != m_resource.pHealth) {
		delete m_resource.pHealth;
	}
	if (nullptr != m_resource.pStamina) {
		delete m_resource.pStamina;
	}
	if (nullptr != m_resource.pWaste) {
		delete m_resource.pWaste;
	}

	delete m_pAffect;
}


void Creature::affected(affectType_t type, affectBody_t &pBody)
{
	m_pAffect->add(type, pBody);
}


const posInfo_t *Creature::getPosition(void)
{
	return &(m_position);
}


const creatureResource_t *Creature::getResource(void)
{
	return &(m_resource);
}


void Creature::getColor(double &red, double &green, double &blue)
{
	m_pAction->dbgGet(red, green, blue);
}


void Creature::updateHealth(void)
{
	affectBody_t	repairDetail;
	affectBody_t	injuredDetail;

	/* add health value */
	if (0u < m_pAffect->getNum(REPAIR)) {
		m_pAffect->take(REPAIR, repairDetail);
		m_resource.pHealth->add(repairDetail.repair.value);
		m_pAffect->clear(REPAIR);
	}
	/* reduce health value */
	if (0u < m_pAffect->getNum(INJURED)) {
		m_pAffect->take(INJURED, injuredDetail);
		m_resource.pHealth->reduce(injuredDetail.injured.value);
		m_pAffect->clear(INJURED);
	}
}


void Creature::updateStamina(void)
{
	affectBody_t	recoverDetail;
	affectBody_t	tiredDetail;

	/* add stamina value */
	if (0u < m_pAffect->getNum(RECOVER)) {
		m_pAffect->take(RECOVER, recoverDetail);
		m_resource.pStamina->add(recoverDetail.recover.value);
		/* TODO : 移動平均などから、m_pAffectのメモリサイズを減らすべきかも */
		m_pAffect->clear(RECOVER);
	}
	/* reduce stamina value */
	if (0u < m_pAffect->getNum(TIRED)) {
		m_pAffect->take(TIRED, tiredDetail);
		m_resource.pStamina->reduce(tiredDetail.tired.value);
		/* TODO : 移動平均などから、m_pAffectのメモリサイズを減らすべきかも */
		m_pAffect->clear(TIRED);
	}
}


void Creature::updateEnergy(void)
{
	affectBody_t	takeDetail;
	affectBody_t	absorbDetail;
	affectBody_t	consumeDetail;

	/* add energy value */
	if (0u < m_pAffect->getNum(TAKE_ENERGY)) {
		m_pAffect->take(TAKE_ENERGY, takeDetail);
		m_resource.pEnergy->add(takeDetail.takeEnergy.value);
		m_pAffect->clear(TAKE_ENERGY);
	}
	/* reduce energy value */
	if (0u < m_pAffect->getNum(ABSORB_ENERGY)) {
		m_pAffect->take(ABSORB_ENERGY, absorbDetail);
		m_resource.pEnergy->consume(absorbDetail.absorbed.value);
		m_pAffect->clear(ABSORB_ENERGY);
	}
	/* add waste value */
	if (0u < m_pAffect->getNum(CONSUME_ENERGY)) {
		m_pAffect->take(CONSUME_ENERGY, consumeDetail);
		m_resource.pEnergy->consume(consumeDetail.consume.value);
		m_resource.pWaste->add(consumeDetail.consume.value);
		m_pAffect->clear(CONSUME_ENERGY);
	}
}


void Creature::updatePosition(void)
{
	affectBody_t	moveDetail;

	if (0u < m_pAffect->getNum(MOVE)) {
		m_pAffect->take(MOVE, moveDetail);
		m_position.xHorPos += moveDetail.move.diffX;
		m_position.yHorPos += moveDetail.move.diffY;
		m_pAffect->clear(MOVE);
	}
}
