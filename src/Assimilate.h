#pragma once

#include "Action.h"


class Assimilate : public Action
{
public:
	Assimilate( const posInfo_t*			pMyPosition,
				const creatureResource_t*	pResource );
	~Assimilate(void);

	void exec(const Creature* pTargetCrearute, const Ground* pTargetGround);

private:
	
};

