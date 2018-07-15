#pragma once

/*- include header -*/
#include "Action.h"
#include <random>


/*- forward declaration -*/
class IntCos;


class Roam : public Action
{
public:
	Roam( const posInfo_t*			pMyPosition
		, const creatureResource_t*	pResource );
	~Roam(void);

	void exec(const Creature* pTargetCrearute, const Ground* pTargetGround);

	void dbgGet(double &red, double &green, double &blue);

private:
	void decideNextPosition(void);
	void calcMoveDistance(void);
	unsigned int getDirection(void);

	IntCos			*m_pIntCos;
	std::mt19937	*m_pRandom;
	posInfo_t		m_targetPos;
};