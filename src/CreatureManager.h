#pragma once

#include<vector>
#include<queue>
#include<random>
#include"LocalSpace.h"

using namespace std;

/* structure */
typedef struct {
	unsigned int	lowerXIdx;
	unsigned int	lowerYIdx;
	unsigned int	upperXIdx;
	unsigned int	upperYIdx;
} areaIndex_t;


class CreatureManager : public LocalSpace
{
public:
	CreatureManager(  const unsigned int	initNum
					, spaceSize_t			&pFieldSize
					, const unsigned int	fateSeed );
	~CreatureManager(void);

	/* LocalSpace for Creature */
	unsigned int getCreatures(const spaceSize_t	&size, queue<const Creature *> &pCreatures);
	unsigned int getGrounds(const spaceSize_t &size, vector<vector<Ground *>> &pGrounds);

	/* CreatureFactory */
	bool replicateRequest(Creature *pCreature);
	bool deleteRequest(Creature *pCreature);
	bool updateRequest(void);

	/* for CreatureManager */
	bool initCreateCreatures(void); /* ì¬‚·‚éCreature‚Ì“à–ó‚ğˆø”w’è‚Å‚«‚é‚Æ‚¢‚¢‚©‚à... */
	bool execInteraction(void);
	void drawCreatures(void);

private:
	/* for display (must be separated other class) */
	void drawCreature(void);

	/* utility function */
	bool calcAreaIdx( const spaceSize_t		&size
					,		areaIndex_t		&retArea );
	unsigned int calcLowerIdx(const unsigned int horPos
							, const unsigned int length );
	unsigned int calcUpperIdx(const unsigned int horPos
							, const unsigned int length
							, const unsigned int edgeIdx );

	/* variable */
	vector<Creature *>*			m_pCreatureList;
	unsigned int				m_creatureNum;

	vector<vector<Ground *>>*	m_p2dField;
	unsigned int				m_fieldWidth;
	unsigned int				m_fieldHeight;

	std::vector<Creature *>*	m_pRegisterReq;
	std::vector<Creature *>*	m_pDeleteReq;

	std::mt19937*				m_pFateModule;
};