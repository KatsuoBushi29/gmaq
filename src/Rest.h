#pragma once

#include "Action.h"


class Rest : public Action
{
public:
	Rest( const posInfo_t*			pMyPosition
		, const creatureResource_t*	pResource );
	~Rest(void);

 	void exec(const Creature* pTargetCrearute, const Ground* pTargetGround);

	/* for debug */
	void dbgGet(double &red, double &green, double &blue);

private:
};

