#pragma once

#include "FieldManager.h"


typedef struct {
	unsigned int	horPos;
	unsigned int	verPos;
} windowPos_t;

typedef struct {
	unsigned int	width;
	unsigned int	height;
} windowSize_t;

typedef struct {
	spatialCoord_t	centerPosition;
	spatialCoord_t	viewPosition;
	spatialCoord_t	topDirection;
	windowSize_t	windowSize;
} cameraParam_t;


class Camera
{
public:
	Camera(const cameraParam_t	&init
		, const FieldManager	&fieldConf
		, const spatialArea_t	&subject );
	~Camera(void);

	/* change camera parameter */
	void move(spatialCoord_t diff);
	void rotate(spatialCoord_t dir);

	/* draw graphics */
	void draw(void);

	/* get information for game field */
	const spatialCoord_t get(const windowPos_t &pos);
	const spatialArea_t get(const windowPos_t &leftTop
						, const windowSize_t &size);

private:
	bool exchangePos( const GLint		winHorPos
					, const GLint		winVerPos
					, const GLdouble	modelView[16]
					, const GLdouble	projection[16]
					, const GLint		viewPort[4]
					, spatialCoord_t	&exchangeValue );

	cameraParam_t	m_param;
	FieldManager	m_fieldConf;
	spatialArea_t	m_subject;
	spatialArea_t	m_select;
	
	/* DEBUG */
	GLdouble		m_posX;
	GLdouble		m_posY;
	GLdouble		m_posZ;
};