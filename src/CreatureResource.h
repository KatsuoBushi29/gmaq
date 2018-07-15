
#ifndef _DEF_CREATURE_RESOURCE__
#define _DEF_CREATURE_RESOURCE__

#include"Resource.h"
#include"Energy.h"


typedef struct creatureResource
{
	Resource *pHealth;
	Resource *pStamina;
	Resource *pWaste;
	Energy *pEnergy;
} creatureResource_t;


#endif /* _DEF_CREATURE_RESOURCE__ */