#pragma once

#include <memory>

#include "Creature.h"
#include "Ground.h"
#include "CreatureResource.h"
#include "LocalSpace.h"
#include "Affect.h"

/* forward declare */
class ResultStore;


/* result after exec */
typedef struct
{
	bool			isValid;
	affectType_t	type;
	affectBody_t	result;
} resultAction_t;

/* exist result */
typedef enum
{
	EMPTY_NEXT_RESULT,
	EXIST_NEXT_RESULT,
	FULL_NEXT_RESULT,
} resultStatus_t;


class Action
{
public:
	Action(	const posInfo_t*			pMyPosition,
			const creatureResource_t*	pResource	);
	~Action(void);

	/* must be extend */
	virtual void exec(const Creature* pTargetCrearute, const Ground* pTargetGround) = 0; 

	/* common */
	resultStatus_t set(resultAction_t &detail);
	resultStatus_t get(resultAction_t &detail);

	/* debug */
	virtual void dbgGet(double &red, double &green, double &blue) = 0;

protected:
	const posInfo_t*			m_pMyPosition;
	const creatureResource_t*	m_pMyResource;

	std::unique_ptr<ResultStore>	m_pResult;
};

