#include <typeinfo>

#include "Wolf.h"
#include "WolfParameter.h"
/* action */
#include "Rest.h"
#include "Roam.h"
#include "Rot.h"


Wolf::Wolf( LocalSpace	*pLocalSpace
		   , posInfo_t	*pCurrentPosition) :
		Creature(pLocalSpace, pCurrentPosition)
{
	appearanceFactor_t factor = { HAIRY, ROBUST};

	m_pAppearance		= new Appearance(factor);
	m_pAction			= new Roam(m_pTargetCreature, &m_position, &m_resource);

	m_resource.pEnergy	= new Energy(	WOLF_INIT_ENERGY,
										WOLF_ENERGY_CAPACITY );
	m_resource.pHealth	= new Resource( WOLF_INIT_HEALTH,
										WOLF_MAX_HEALTH,
										WOLF_POOR_HEALTH,
										WOLF_POOR_HEALTH);
	m_resource.pStamina	= new Resource( WOLF_INIT_STAMINA,
										WOLF_MAX_STAMINA,
										WOLF_POOR_STAMINA,
										WOLF_POOR_STAMINA);
	m_resource.pWaste	= new Resource( WOLF_INIT_WASTE,
										WOLF_WASTE_CAPACITY,
										WOLF_EXCRETED_WASTE,
										WOLF_EXCRETED_WASTE );

	m_pDstCreatures		= new std::queue<const Creature *>();
	m_pTargetCreature	= nullptr;
}


Wolf::Wolf(	Energy		*pInitEnergy
		   , LocalSpace *pLocalSpace
		   , posInfo_t	*pCurrentPosition ) :
		Creature(pLocalSpace, pCurrentPosition)
{
	appearanceFactor_t factor = { HAIRY, ROBUST};

	m_pAppearance		= new Appearance(factor);
	m_pAction			= new Roam(m_pTargetCreature, &m_position, &m_resource);

	m_resource.pEnergy	= pInitEnergy;
	m_resource.pHealth	= new Resource( WOLF_INIT_HEALTH,
										WOLF_MAX_HEALTH,
										WOLF_POOR_HEALTH,
										WOLF_POOR_HEALTH );
	m_resource.pStamina	= new Resource( WOLF_INIT_STAMINA,
										WOLF_MAX_STAMINA,
										WOLF_POOR_STAMINA,
										WOLF_POOR_STAMINA );
	m_resource.pWaste	= new Resource( WOLF_INIT_WASTE,
										WOLF_WASTE_CAPACITY,
										WOLF_EXCRETED_WASTE,
										WOLF_EXCRETED_WASTE );

	m_pDstCreatures		= new std::queue<const Creature *>();
	m_pTargetCreature	= nullptr;
}


Wolf::~Wolf(void)
{
	delete m_pAppearance;
	delete m_pAction;
	
	delete m_resource.pEnergy;
	delete m_resource.pHealth;
	delete m_resource.pStamina;
	delete m_resource.pWaste;

	delete m_pDstCreatures;

	m_pTargetCreature	= NULL;
}


/* basic cycle function */
void Wolf::sense(void)
{ 
	unsigned int	findNum;
	spaceSize_t		findSpaceInfo;

	if (nullptr == m_pTargetCreature) {
		findSpaceInfo.mid			= m_position;
		findSpaceInfo.frontLength	= WOLF_SIGHT_LENGTH;
		findSpaceInfo.backLength	= WOLF_SIGHT_LENGTH;
		findSpaceInfo.leftLength	= WOLF_SIGHT_LENGTH;
		findSpaceInfo.rightLength	= WOLF_SIGHT_LENGTH;

		findNum = m_pLocalSpace->getCreatures(findSpaceInfo, *m_pDstCreatures);

		//m_pTargetCreature = decideTarget();
	}

	/* ŽÕ•Á•¨ˆ—‚ª•K—v‚©‚à? */
}


void Wolf::action(void)
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


void Wolf::reflect(void)
{
	/* (INJURE) : return effect to other Creature */
	returnInjuredHealth();
	/* (ABSORB_ENERGY) : separate energy for other Creature */
	separateAbsorbedEnergy();
}


void Wolf::update(void)
{
	/* update resouce */
	updateHealth();
	updateStamina();
	updateEnergy();
	updatePosition();
	/* update Action */
	updateAction();
}


void Wolf::toSoil(void)
{
	unsigned int energy	= m_resource.pEnergy->get();
	unsigned int waste	= m_resource.pWaste->getValue();
	affectBody_t affectBody;

	if( WOLF_TOSOIL_VALUE <= (energy + waste)){
		affectBody.toSoil.value = WOLF_TOSOIL_VALUE;
	}
	else{
		affectBody.toSoil.value = (energy + waste);
	}
	this->affected(TOSOIL, affectBody);
}


void Wolf::takeARest(void)
{
	ResourceStatus_t staminaStatus	= m_resource.pStamina->getStatus();
	ResourceStatus_t healthStatus	= m_resource.pHealth->getStatus();

	if( (RESOURCE_POOR == staminaStatus) ||
		(RESOURCE_EMPTY == staminaStatus) ){
		recoverStamina();
	}
	else if(RESOURCE_POOR == healthStatus){
		repairHealth();
	}
}

#if 0 /* TODO : move other class */
void Wolf::procActive(void)
{
	bool			isMovable	= false;
	unsigned int	currHealth	= m_resource.pHealth->getValue();
	unsigned int	currStamina	= m_resource.pStamina->getValue();
	unsigned int	currEnergy	= m_resource.pEnergy->get();

	if( WOLF_EMPTY_STAMINA < currStamina){
		isMovable = true;
		/* Wolf is hungry */
		if( WOLF_POOR_ENERGY > currEnergy){
			if( NULL != m_pTargetCreature){
				const appearanceFactor_t *pFactor
					= m_pTargetCreature->m_pAppearance->getFactor();
				if(Condition_t::DYING != pFactor->condition){
					chaseTarget();
				}
				else{
					takeEnergy();
				}
			}
			else{ /* When wolf can't find target */
				if( false == searchTarget()){
					movePosition();
				}
			}
		}
		else{
			if( (WOLF_ENOUGH_ENERGY < currEnergy) &&
				(WOLF_ENOUGH_HEALTH < currHealth) &&
				(WOLF_ENOUGH_STAMINA < currStamina) ){
				replicate();
			}
			else {
				movePosition();
			}
		}
	}
	return;
}
#endif


void Wolf::procDebility(void)
{
	unsigned int	healthValue	= m_resource.pHealth->getValue();
	affectBody_t	affectDetail;

	if(WOLF_DEBILITY_HEALTH_VALUE > healthValue){
		affectDetail.injured.value = healthValue;	 
	}
	else{
		affectDetail.injured.value = WOLF_DEBILITY_HEALTH_VALUE;
	}
	affectDetail.injured.pCreature = this;
	this->affected(INJURED, affectDetail);
}

#if 0 /* TODO : move other class */
bool Wolf::searchTarget(void)
{
	int	creatureNum		= m_pDstCreatures->size();
	int	currAdvantage	= 0;
	int	maxAdvantage	= 0;
	Creature *pCreature;

	for(int creatureIdx = 0; creatureIdx < creatureNum; creatureIdx++){
		pCreature		= m_pDstCreatures->at(creatureIdx);
		currAdvantage	= pCreature->m_pAppearance->calcAdvantage(*m_pAppearance);
		/* Search Creature had best advantage */
		if(maxAdvantage < currAdvantage){
			maxAdvantage		= currAdvantage;
			m_pTargetCreature	= pCreature; 
		}
	}

	/* Wolf could not search */
	if(WOLF_ADVANTAGE_VALUE > maxAdvantage){
		m_pTargetCreature = nullptr;
		return false;
	}
	return true;
}
#endif


void Wolf::chaseTarget(void)
{
	const posInfo_t	*pTargetPos = m_pTargetCreature->getPosition();
	unsigned int	distance	= 0u;
	unsigned int	rate		= 0u;
	affectBody_t	affectBody;

	distance = ((pTargetPos->xHorPos - m_position.xHorPos)^2) +
				((pTargetPos->yHorPos - m_position.yHorPos)^2);

	/* Wolf can attack to target */
	if((WOLF_ATTACK_RANGE^2) >= distance) {
		/* Need delay for next attack */
		affectBody.injured.value = WOLF_ATTACK_DAMAGE;
		affectBody.injured.pCreature = this;
		m_pTargetCreature->affected(INJURED, affectBody);
	}
	else if((WOLF_CHASE_DISTANCE^2) >= distance) {
		affectBody.move.diffX = /* frame_coef * */(pTargetPos->xHorPos - m_position.xHorPos);
		affectBody.move.diffY = /* frame_coef * */(pTargetPos->yHorPos - m_position.yHorPos);
		this->affected(MOVE, affectBody);
	}
	else {
		/* Convert rate had 8bit decimal point */
		rate = (unsigned int)(sqrt( ((double)(WOLF_CHASE_DISTANCE^2)) / ((double)distance) ) * 256);
		affectBody.move.diffX = ((/* frame_coef * */rate * (pTargetPos->xHorPos - m_position.xHorPos)) >> 8u);
		affectBody.move.diffY = ((/* frame_coef * */rate * (pTargetPos->yHorPos - m_position.yHorPos)) >> 8u);
		this->affected(MOVE, affectBody);
	}
}


void Wolf::movePosition()
{
	affectBody_t	affectDetail;
	/* TODO_takato : must change random walk */
	affectDetail.move.diffX = /* frame_coef * */WOLF_WOLKING_DISTANCE;
	affectDetail.move.diffY = /* frame_coef * */WOLF_WOLKING_DISTANCE;
	this->affected(MOVE, affectDetail);
	/* reduce stamina */
	affectDetail.tired.pCreature	= this;
	affectDetail.tired.value		= WOLF_MOVE_STAMINA_VALUE;
	this->affected(TIRED, affectDetail);
}


void Wolf::replicate(void)
{

}


void Wolf::takeEnergy(void)
{
	affectBody_t affectDetail;

	affectDetail.absorbed.value		= WOLF_TAKED_ENERGY_VALUE;
	affectDetail.absorbed.pCreature	= this;
	m_pTargetCreature->affected(ABSORB_ENERGY, affectDetail);
}


void Wolf::recoverStamina(void)
{
	unsigned int	energyValue	= m_resource.pEnergy->get();
	affectBody_t	affectDetail;

	if(WOLF_RECOVER_STAMINA_VALUE > energyValue){
		affectDetail.recover.value = energyValue;
	}
	else{
		affectDetail.recover.value = WOLF_RECOVER_STAMINA_VALUE;
	}
	affectDetail.injured.pCreature = this;
	this->affected(RECOVER, affectDetail);
	this->affected(CONSUME_ENERGY, affectDetail);
}


void Wolf::repairHealth(void)
{
	unsigned int	energyValue	= m_resource.pEnergy->get();
	affectBody_t	affectDetail;

	if(WOLF_REPAIR_HEALTH_VALUE > energyValue){
		affectDetail.repair.value = energyValue;
	}
	else{
		affectDetail.repair.value = WOLF_REPAIR_HEALTH_VALUE;
	}
	affectDetail.injured.pCreature = this;
	this->affected(REPAIR, affectDetail);
	this->affected(CONSUME_ENERGY, affectDetail);
}


void Wolf::separateAbsorbedEnergy(void)
{
	unsigned int	affectNum		= m_pAffect->getNum(ABSORB_ENERGY);
	unsigned int	currEnergy		= m_resource.pEnergy->get();
	unsigned int	totalEnergy     = 0u;
	unsigned int	currAbsorbed	= 0u;
	unsigned int	totalAbsorbed	= 0u;
	affectBody_t	takeDetail;
	affectBody_t	absorbDetail;

	/* (ABSORB_ENERGY) : separate energy for other Creature */
	if (0u < affectNum){
		totalAbsorbed = m_pAffect->getTotal(ABSORB_ENERGY);
		while (true == m_pAffect->take(ABSORB_ENERGY, absorbDetail)) {
			currAbsorbed	= absorbDetail.absorbed.value;
			/* calc rate(decimal point : 8bit) */
			takeDetail.takeEnergy.value	= (currEnergy * ((currAbsorbed << 8u) / totalAbsorbed) ) >> 8u;
			totalEnergy					+= takeDetail.takeEnergy.value;
			absorbDetail.absorbed.pCreature->affected(TAKE_ENERGY, takeDetail);
		}
		absorbDetail.absorbed.value		= totalEnergy;
		absorbDetail.absorbed.pCreature	= this;
		m_pAffect->add(ABSORB_ENERGY, absorbDetail);
	}
}


void Wolf::returnInjuredHealth(void)
{
	unsigned int	totalDamage	= 0u;
	affectBody_t	injuredDetail;

	if (0u < m_pAffect->getNum(INJURED)){
		while (true == m_pAffect->take(INJURED, injuredDetail)){
			totalDamage += injuredDetail.injured.value;
		}
		injuredDetail.injured.value		= totalDamage;
		injuredDetail.injured.pCreature	= this;
		m_pAffect->add(INJURED, injuredDetail);
	}
}


void Wolf::updateAction(void)
{
	ResourceStatus_t	healthStatus	= m_resource.pHealth->getStatus();
	ResourceStatus_t	staminaStatus	= m_resource.pStamina->getStatus();

	if (RESOURCE_EMPTY == healthStatus) {
		if (typeid(class Rot) != typeid(m_pAction)) {
			delete m_pAction;
			m_pAction = new Rot(m_pTargetCreature, &m_position, &m_resource);
		}
	}
	else if (RESOURCE_EMPTY == staminaStatus) {
		/* energy is not empty */
		if (WOLF_EMPTY_ENERGY < m_resource.pEnergy->get()) {
			if (typeid(class Rest) != typeid(m_pAction)) {
				delete m_pAction;
				m_pAction = new Rest(m_pTargetCreature, &m_position, &m_resource);
			}
		}
		/* energy is empty */
		else {
			if (typeid(class Rot) != typeid(m_pAction)) {
				delete m_pAction;
				m_pAction = new Rot(m_pTargetCreature, &m_position, &m_resource);
			}
		}
	}
	else {
		if ((RESOURCE_RICH == staminaStatus) ||
			(RESOURCE_FULL == staminaStatus)) {
			if (typeid(class Roam) != typeid(m_pAction)) {
				delete m_pAction;
				m_pAction = new Roam(m_pTargetCreature, &m_position, &m_resource);
			}
		}
		else if (WOLF_EMPTY_ENERGY == m_resource.pEnergy->get()) {
			if (typeid(class Roam) != typeid(m_pAction)) {
				delete m_pAction;
				m_pAction = new Roam(m_pTargetCreature, &m_position, &m_resource);
			}
		}
	}
}