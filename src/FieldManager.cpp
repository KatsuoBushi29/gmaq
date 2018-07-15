#include "FieldManager.h"

#define FIELD_MNG_DECIMAL_POINT	(8u)


FieldManager::FieldManager(spatialCoord_t &pos, spatialCoord_t &size)
	: m_lowerPos(pos)
{
	/* setting spatial space */
	m_upperPos.xValue	= m_lowerPos.xValue + size.xValue;
	m_upperPos.yValue	= m_lowerPos.yValue + size.yValue;
	m_upperPos.zValue	= m_lowerPos.zValue + size.zValue;
}


FieldManager::~FieldManager(void)
{
	/* DO_NOTHING */
}


unsigned int FieldManager::getCenterPos(spatialDirection_t dir)
{
	unsigned int pos;

	switch (dir) {
	case FIELD_MGR_DIR_X:
		pos = (m_upperPos.xValue - m_lowerPos.xValue) >> 1u;
		break;
	case FIELD_MGR_DIR_Y:
		pos = (m_upperPos.yValue - m_lowerPos.yValue) >> 1u;
		break;
	case FIELD_MGR_DIR_Z:
		pos = (m_upperPos.zValue - m_lowerPos.zValue) >> 1u;
		break;
	default :
		/* ILLEGAL_ARGUMENT */
		break;
	}
	return pos;
}


spatialCoord_t FieldManager::getEdgePos(spatialEdge_t type)
{
	spatialCoord_t pos;

	switch (type) {
	case FIELD_MGR_EDGE_LOWER:
		pos = m_lowerPos;
		break;
	case FIELD_MGR_EDGE_UPPER:
		pos = m_upperPos; 
		break;
	default :
		/* ILLEGAL_TYPE */
		break;
	}
	return pos;
}


bool FieldManager::isOverSpatial(spatialCoord_t pos)
{
	/* over */
	if (isOverRange(m_lowerPos.xValue, m_upperPos.xValue, pos.xValue) == true){
		return true;
	}
	if (isOverRange(m_lowerPos.yValue, m_upperPos.yValue, pos.yValue) == true){
		return true;
	}
	if (isOverRange(m_lowerPos.zValue, m_upperPos.zValue, pos.zValue) == true){
		return true;
	}
	/* not over */
	return false;
}


bool FieldManager::isOverRange( const unsigned int lower,
								const unsigned int upper,
								const unsigned int point )
{
	bool	isOver = false;

	if (lower <= upper){
		if ((point < lower) || (upper < point)) {
			isOver = true;
		}
	}
	else {
		/* illegal argument */
	}
	return isOver;
}


unsigned int FieldManager::toFieldPosition(GLdouble posValue)
{
	return (unsigned int)(posValue * ((GLdouble)(1u << FIELD_MNG_DECIMAL_POINT)));
}