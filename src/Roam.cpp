
/*** include header ***/
#include "Roam.h"
#include "IntCos.h"

#include <cstdlib>
#include <queue>

using namespace std;

/*** internal const ***/
/* move range */
/* must be consider to status */
const double		ROAM_MOVE_DISTANCE		= (0.1 * (1u << POS_INFO_DECIMAL));
const unsigned int	ROAM_DST_DISTANCE		= (1u * (1u << POS_INFO_DECIMAL));
const unsigned int	ROAM_RATE_FRACNUM		= (8u);
const unsigned int	ROAM_RATE_FRACVAL		= (1 << ROAM_RATE_FRACNUM);
const unsigned int	ROAM_MOVE_STAMINA		= (1u);


Roam::Roam( const posInfo_t*			pMyPosition,
			const creatureResource_t*	pResource
		/* const creatureStatus_t *pStatus : STR,VIT,AGI... */ ) :
	Action(pMyPosition, pResource)
{
	m_pIntCos			= new IntCos();
	m_pRandom			= new mt19937;

	/* setting init position */
	m_targetPos.xHorPos	= pMyPosition->xHorPos;
	m_targetPos.yHorPos	= pMyPosition->yHorPos;
}


Roam::~Roam(void)
{
	delete m_pIntCos;
	delete m_pRandom;
}


void Roam::exec(const Creature* pTargetCrearute, const Ground* pTargetGround)
{
	if ((m_pMyPosition->xHorPos == m_targetPos.xHorPos) &&
		(m_pMyPosition->yHorPos == m_targetPos.yHorPos) &&
		(ROAM_MOVE_STAMINA <= m_pMyResource->pStamina->getValue())) {
		decideNextPosition();
	}
	calcMoveDistance();
}


void Roam::decideNextPosition(void)
{
	unsigned int	direction	= 0u;
	int				cosVal		= 0;
	int				sinVal		= 0;
	resultAction_t	detail;

	/* decide next position */
	direction	= getDirection();
	cosVal		= m_pIntCos->getValue(direction);
	sinVal		= m_pIntCos->getValue(direction + INTCOS_DEG_270);
	m_targetPos.xHorPos	= m_pMyPosition->xHorPos + (((int)(ROAM_DST_DISTANCE) * cosVal) >> INTCOS_FRAC_BITNUM);
	m_targetPos.yHorPos = m_pMyPosition->yHorPos + (((int)(ROAM_DST_DISTANCE) * sinVal) >> INTCOS_FRAC_BITNUM);
	/* consume stamina */
	detail.isValid				= true;
	detail.type					= TIRED;
	detail.result.consume.value	= ROAM_MOVE_STAMINA;
	this->set(detail);
}


void Roam::calcMoveDistance(void)
{
	double			distance	= 0.00;
	unsigned int	absDiffX	= 0u;
	unsigned int	absDiffY	= 0u;
	int				diffX		= 0;
	int				diffY		= 0;
	int				rate		= (int)ROAM_RATE_FRACVAL;
	resultAction_t	detail;

	/* calc distance for each direction */
	diffX		= (int)(m_targetPos.xHorPos - m_pMyPosition->xHorPos);
	diffY		= (int)(m_targetPos.yHorPos - m_pMyPosition->yHorPos);
	absDiffX	= (unsigned int)abs(diffX);
	absDiffY	= (unsigned int)abs(diffY);
	/* calc rate */
	distance	= sqrt( pow((double)absDiffX, 2.0) + pow((double)absDiffY, 2.0) );
	if (distance > ROAM_MOVE_DISTANCE) {
		rate	= (int)((ROAM_MOVE_DISTANCE / distance) * (double)ROAM_RATE_FRACVAL); 
	}
	/* moving */
	detail.isValid				= true;
	detail.type					= MOVE;
	detail.result.move.diffX	= (unsigned int)((rate * diffX) >> ROAM_RATE_FRACNUM);
	detail.result.move.diffY	= (unsigned int)((rate * diffY) >> ROAM_RATE_FRACNUM);
	this->set(detail);
}


unsigned int Roam::getDirection(void)
{
	return ((*m_pRandom)() % INTCOS_DEG_360);
}


void Roam::dbgGet(double &red, double &green, double &blue)
{
	red		= 0.0;
	green	= 1.0;
	blue	= 1.0;
}