
#include <iostream>
#include "Appearance.h"


Appearance::Appearance(appearanceFactor_t &factor)
{
	this->updateFactor(factor);
}


Appearance::~Appearance(void)
{
}


int Appearance::calcAdvantage(Appearance &appearance)
{
	int	diff	= 0;
	const appearanceFactor_t *pDstFactor = appearance.getFactor();

	diff += (m_factor.hairiness	- pDstFactor->hairiness);
	diff += (m_factor.physique	- pDstFactor->physique);
	diff += (m_factor.condition	- pDstFactor->condition);

	return diff;
}


const appearanceFactor_t *Appearance::getFactor(void)
{
	return &(m_factor);
}


void Appearance::updateFactor(appearanceFactor_t &factor)
{
	memcpy( &m_factor, &factor, sizeof(appearanceFactor_t));
}
