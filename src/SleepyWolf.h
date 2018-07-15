#pragma once

#include<vector>
#include"CreatureStatus.h"


class SleepyWolf : public CreatureStatus
{
public:
	SleepyWolf(CreatureResource_t *pResource);
	~SleepyWolf(void);

	void preUpdate(void);
	void update(void);
	void preReflect(void);
	void reflect(void);
	bool isNeedChange(CStatus_t *pNextStatus);

private :
	void recoverStamina(void);
	void repairHealth(void);
};