#include <queue>

#include "Action.h"

/* constant declare */
const unsigned int	ACTION_MAX_NUM		= (10u);


/* protected class */
class ResultStore
{
public:
	ResultStore(unsigned int max) :	m_maxStored(max), m_currStored(0u) {}
	~ResultStore(void) {}

	resultStatus_t ResultStore::add(resultAction_t &detail)
	{
		resultStatus_t status	= EXIST_NEXT_RESULT;

		/* check enable to stored current result */
		if (m_currStored < m_maxStored) {
			m_resultQueue.push(detail);
			m_currStored++;
		}
		else {
			detail.isValid	= false;
		}
		/* check enable to stored next result */
		if (m_currStored < m_maxStored) {
			status = FULL_NEXT_RESULT;
		}
		return status;
	}

	resultStatus_t ResultStore::take(resultAction_t &detail)
	{
		resultStatus_t status	= EMPTY_NEXT_RESULT;

		/* check to exist current result */
		if (false == m_resultQueue.empty()) {
			detail = m_resultQueue.front();
			m_resultQueue.pop();
			m_currStored--;
		}
		else {
			detail.isValid = false;
		}
		/* check to exist next result */
		if (false == m_resultQueue.empty()) {
			status = EXIST_NEXT_RESULT;
		}
		return status;
	}

private:
	unsigned int				m_maxStored;
	unsigned int				m_currStored;

	std::queue<resultAction_t>	m_resultQueue;
};


Action::Action(   const Creature	*pTargetCrearute
				, const Ground		*pTargetGround
				, const posInfo_t	*pMyPosition  
				, const creatureResource_t	*pResource )
{
	m_pMyPosition		= pMyPosition;
	m_pMyResource		= pResource;

	m_pResult			= std::unique_ptr<ResultStore>(new ResultStore(ACTION_MAX_NUM));
}


Action::~Action(void)
{
	/* Nothing */
}

resultStatus_t Action::set(resultAction_t &detail)
{
	return m_pResult->add(detail);
}

resultStatus_t Action::get(resultAction_t &detail)
{
	return m_pResult->take(detail);
}
