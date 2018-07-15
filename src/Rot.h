#pragma once

#include "Action.h"


class Rot : public Action
{
public:
	Rot(const posInfo_t*			pMyPosition,
		const creatureResource_t*	pResource
		/* const creatureStatus_t *pStatus : STR,VIT,AGI... */);
	~Rot(void);

	void exec(const Creature* pTargetCrearute, const Ground* pTargetGround);

	void dbgGet(double &red, double &green, double &blue);

private :

};

