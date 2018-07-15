#pragma once

#include <vector>
#include <queue>

using namespace std;

/* virtual define */
class Creature;


/* passive affect */
typedef struct
{
	unsigned int	value;
	Creature		*pCreature;
} passiveAffect_t;

/* active affect */
typedef struct
{
	unsigned int	value;
} activeAffect_t;


typedef struct
{
	unsigned int	diffX;
	unsigned int	diffY;
} movement_t;

/* affect type */
typedef enum
{
	/* for health */
	INJURED = 0,
	REPAIR,
	/* for stamina */
	TIRED,
	RECOVER,
	/* for energy */
	ABSORB_ENERGY,
	TAKE_ENERGY,
	CONSUME_ENERGY,
	TOSOIL,
	/* other */
	MOVE,
	AFFECT_NUM,
} affectType_t;

typedef union
{
	/* for health */
	passiveAffect_t	injured;
	passiveAffect_t	repair;
	/* for stamina */
	passiveAffect_t tired;
	passiveAffect_t	recover;
	/* for energy */
	passiveAffect_t	absorbed;
	passiveAffect_t	takeEnergy;
	activeAffect_t	consume;
	activeAffect_t	toSoil;
	/* for other */
	movement_t		move;
} affectBody_t;


class Affect
{
public:
	Affect(void);
	~Affect(void);

	void add(const affectType_t type, const affectBody_t &detail);
	bool take(const affectType_t type, affectBody_t &detail);
	void clear(const affectType_t type);

	unsigned int getTotal(const affectType_t type);
	unsigned int getNum(const affectType_t type);
	
private:
	vector<queue<affectBody_t>>*	m_pAffectList;
	vector<affectBody_t>*			m_pAffectTotal;
	vector<unsigned int>*			m_pAffectNum;
};