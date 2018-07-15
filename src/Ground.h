#pragma once

#include<vector>
#include<queue>
#include "Energy.h"
#include "Affect.h"

/* virtual class */
class Creature;


class Ground
{
public:
	Ground(void);
	~Ground(void);

	/* for Creature */
	bool				put(const Creature &pCreature);
	bool				remove(const Creature &pCreature);
	bool				moved(const Creature &pCreatue, Ground &pDstGround);
	unsigned int		refer(std::queue<const Creature *> &pCreatures);

	/* for Energy */
	unsigned int		getStoredEnergy(void) const; 
	unsigned int		stored(unsigned int energy);
	unsigned int		spoiled(unsigned int energy);

private:
	unsigned int					m_creaturesNum;
	unsigned int					m_putIndex;
	std::vector<const Creature *>	*m_pCreatures;

	Energy *m_pEnergy;
	
};

