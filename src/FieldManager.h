#pragma once

#include <gl/freeglut.h>

typedef struct {
	int	xValue;
	int	yValue;
	int	zValue;
} spatialCoord_t;

typedef struct {
	spatialCoord_t	left;
	spatialCoord_t	right;
	spatialCoord_t	top;
	spatialCoord_t	bottom;
} spatialArea_t;

typedef enum {
	FIELD_MGR_DIR_X,
	FIELD_MGR_DIR_Y,
	FIELD_MGR_DIR_Z,
} spatialDirection_t;

typedef enum {
	FIELD_MGR_EDGE_LOWER,
	FIELD_MGR_EDGE_UPPER,
} spatialEdge_t;


class FieldManager
{
public:
	FieldManager(spatialCoord_t &pos, spatialCoord_t &size);
	~FieldManager(void);

	unsigned int getCenterPos(spatialDirection_t dir);
	spatialCoord_t getEdgePos(spatialEdge_t type);

	bool isOverSpatial(spatialCoord_t pos);
	unsigned int toFieldPosition(GLdouble posValue);

private:
	bool isOverRange(const unsigned int lower,
					const unsigned int upper,
					const unsigned int point );

	spatialCoord_t	m_upperPos;
	spatialCoord_t	m_lowerPos;
};

