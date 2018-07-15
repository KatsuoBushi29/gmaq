#pragma once

#include<vector>
#include"Ground.h"


/* namespace */
using namespace std;

/* virtual define */
class Creature;

/* constant */
#define POS_INFO_DECIMAL	(8u)

/* structure */
typedef struct posInfo
{
	unsigned int	xHorPos;	/* 0-7bit:decimal(POS_INFO_DECIMAL)	*/
	unsigned int	yHorPos;	/* 0-7bit:decimal(POS_INFO_DECIMAL)	*/
} posInfo_t;

typedef struct spaceSize
{
	posInfo_t		mid;
	unsigned int	frontLength;
	unsigned int	backLength;
	unsigned int	leftLength;
	unsigned int	rightLength;
} spaceSize_t;


/* Class Interface */
class LocalSpace
{
public:
	virtual ~LocalSpace(void){};

	virtual unsigned int getCreatures(const spaceSize_t &size, queue<const Creature *> &pCreatures) = 0;
	virtual unsigned int getGrounds(const spaceSize_t &size, vector<vector<Ground *>> &pGrounds) = 0;
};

