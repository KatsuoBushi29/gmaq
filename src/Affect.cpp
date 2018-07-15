#include "Affect.h"

using namespace std;

/* internal define */
const unsigned int	EXTEND_AFFECT_NUM	= 10u;
const unsigned int	EMPTY_AFFECT_NUM	= 0u;


Affect::Affect(void)
{
	m_pAffectList	= new vector<queue<affectBody_t>>(AFFECT_NUM);
	m_pAffectTotal	= new vector<affectBody_t>(AFFECT_NUM);
	m_pAffectNum	= new vector<unsigned int>(AFFECT_NUM, 0u);
}


Affect::~Affect(void)
{
	delete m_pAffectList;
	delete m_pAffectTotal;
	delete m_pAffectNum;
}


void Affect::add(const affectType_t type, const affectBody_t &detail)
{
	/* update total value */
	switch (type) {
		case INJURED:
			m_pAffectTotal->at(type).injured.value		+= detail.injured.value;
			break;
		case REPAIR:
			m_pAffectTotal->at(type).repair.value		+= detail.repair.value;
			break;
		case TIRED:
			m_pAffectTotal->at(type).tired.value		+= detail.tired.value;
			break;
		case RECOVER:
			m_pAffectTotal->at(type).recover.value		+= detail.recover.value;
			break;
		case ABSORB_ENERGY:
			m_pAffectTotal->at(type).absorbed.value		+= detail.absorbed.value;
			break;
		case TAKE_ENERGY:
			m_pAffectTotal->at(type).takeEnergy.value	+= detail.takeEnergy.value;
			break;
		default : /* for active affect */
			/* DONE_NOTHING */
			break;
	}
	m_pAffectList->at(type).push(detail);
	m_pAffectNum->at(type)++;
}


bool Affect::take(const affectType_t type, affectBody_t &detail)
{
	bool isSuccess	= false;

	if(EMPTY_AFFECT_NUM != m_pAffectNum->at(type)){

		isSuccess	= true;
		detail		= m_pAffectList->at(type).front();

		/* update total value */
		switch (type) {
			case INJURED:
				m_pAffectTotal->at(type).injured.value		-= detail.injured.value;
				break;
			case REPAIR:
				m_pAffectTotal->at(type).repair.value		-= detail.repair.value;
				break;
			case TIRED:
				m_pAffectTotal->at(type).tired.value		-= detail.tired.value;
				break;
			case RECOVER:
				m_pAffectTotal->at(type).recover.value		-= detail.recover.value;
				break;
			case ABSORB_ENERGY:
				m_pAffectTotal->at(type).absorbed.value		-= detail.absorbed.value;
				break;
			case TAKE_ENERGY:
				m_pAffectTotal->at(type).takeEnergy.value	-= detail.takeEnergy.value;
				break;
			default : /* for active affect */
				/* DONE_NOTHING */
				break;
		}
		m_pAffectList->at(type).pop();
		m_pAffectNum->at(type)--;
	}
	return isSuccess;
}


unsigned int Affect::getTotal(const affectType_t type)
{
	unsigned int	totalValue	= 0u;
	unsigned int	totalNum;

	switch (type) {
		case INJURED:
		case REPAIR:
		case TIRED:
		case RECOVER:
		case ABSORB_ENERGY:
		case TAKE_ENERGY:
			totalNum = m_pAffectNum->at(type);
			break;
		default :
			totalNum = EMPTY_AFFECT_NUM;
			break;
	}

	if (EMPTY_AFFECT_NUM != totalNum) {
		/* データ構造から見直した方が良さげ... */
		totalValue	= m_pAffectTotal->at(type).absorbed.value;
	}
	return totalValue;
}


void Affect::clear(const affectType_t type)
{
	m_pAffectNum->at(type) = EMPTY_AFFECT_NUM;
}


unsigned int Affect::getNum(const affectType_t type)
{
	return m_pAffectNum->at(type);
}