#include "Ground.h"

/* parameter of energy */
#define	ENERGY_CAPACITY		0x00000100u	/* 256	*/
#define	INIT_ENERGY			0x00000080u	/* 128	*/

/* capacity for Creature on Ground */
const unsigned int	PUT_CREATURE_MAX_NUM	= (0x00000010u);	/* 16	*/
const unsigned int	PUT_CREATURE_EMPTY_NUM	= (0x00000000u);	/* 0	*/
const unsigned int	PUT_CREATURE_INIT_IDX	= (0x00000000u);	/* 0	*/


Ground::Ground(void)
{
	/* initialize creature information */
	m_creaturesNum	= PUT_CREATURE_EMPTY_NUM;
	m_putIndex		= PUT_CREATURE_INIT_IDX;
	m_pCreatures	= new std::vector<const Creature *>(PUT_CREATURE_MAX_NUM, nullptr);

	m_pEnergy		= new Energy(INIT_ENERGY, ENERGY_CAPACITY);
}


Ground::~Ground(void)
{
	delete m_pCreatures;
	delete m_pEnergy;
}


bool Ground::put(const Creature &pCreature)
{
	bool isSuccess = false;

	if(PUT_CREATURE_MAX_NUM > m_creaturesNum) {
		m_pCreatures->at(m_putIndex) = &pCreature;
		m_creaturesNum++;

		/* search empty index */
		if(PUT_CREATURE_MAX_NUM > m_creaturesNum) {	
			for(unsigned int index = PUT_CREATURE_INIT_IDX; index < PUT_CREATURE_MAX_NUM; index++) {
				if(nullptr == m_pCreatures->at(index)) {
					m_putIndex = index;
					break;
				}
			}
		}

		isSuccess = true;
	}
	return isSuccess;
}


bool Ground::remove(const Creature &pCreature)
{
	bool isSuccess = false;

	if(0u < m_creaturesNum) {

		/* search creature index */
		for(unsigned int index = PUT_CREATURE_INIT_IDX; index < PUT_CREATURE_MAX_NUM; index++) {
			if(&pCreature == m_pCreatures->at(index)) {
				m_putIndex				= index;
				m_pCreatures->at(index) = nullptr;
				m_creaturesNum--;
				isSuccess;
				break;
			}
		}

	}
	return isSuccess;
}


bool Ground::moved(const Creature &pCreature, Ground &pDstGround)
{
	bool isSuccess = false;

	if(true == this->remove(pCreature)) {
		if(true == pDstGround.put(pCreature)) {
			isSuccess = true;
		}
	}

	return isSuccess;
}


unsigned int Ground::refer(std::queue<const Creature *> &pCreatures)
{
	unsigned int findNum = PUT_CREATURE_EMPTY_NUM;

	if (PUT_CREATURE_EMPTY_NUM < m_creaturesNum) {
		for (unsigned int index = PUT_CREATURE_INIT_IDX;
			((index < PUT_CREATURE_MAX_NUM) || (findNum < m_creaturesNum)); index++) {
			if (nullptr != m_pCreatures->at(index)) {
				pCreatures.push(m_pCreatures->at(index));
				findNum++;
			}
		}
	}
	return findNum;
}


unsigned int Ground::getStoredEnergy(void) const
{
	return m_pEnergy->get();
}


unsigned int Ground::stored(unsigned int energy)
{
	return m_pEnergy->add(energy);
}


unsigned int Ground::spoiled(unsigned int energy)
{
	return m_pEnergy->consume(energy);
}
