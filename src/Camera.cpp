#include <gl/freeglut.h>
#include "Camera.h"


Camera::Camera(const cameraParam_t	&init
			, const FieldManager	&fieldConf
			, const spatialArea_t	&subject )
	: m_param(init)
	, m_fieldConf(fieldConf)
	, m_subject(subject)
{
	/* DEBUG */
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;
}


Camera::~Camera(void)
{
	/* DO_NOTHING */
}


void Camera::move(spatialCoord_t diff)
{
	m_param.centerPosition.xValue	+= diff.xValue;
	m_param.centerPosition.yValue	+= diff.yValue;
	m_param.centerPosition.zValue	+= diff.zValue;
	m_param.viewPosition.xValue		+= diff.xValue;
	m_param.viewPosition.yValue		+= diff.yValue;
	m_param.viewPosition.zValue		+= diff.zValue;
}


void Camera::rotate(spatialCoord_t dir)
{
	/* DONE_NOTHING */
}


void Camera::draw(void)
{
	glBegin(GL_QUADS);

	/* for debug */
	glColor3f( 1.0f, 0.0f, 0.0f );
	glVertex3d(m_posX		, m_posY	, m_posZ		);
	glVertex3d(m_posX + 1.0	, m_posY	, m_posZ		);
	glVertex3d(m_posX + 1.0	, m_posY	, m_posZ + 1.0	);
	glVertex3d(m_posX		, m_posY	, m_posZ + 1.0	);

	glEnd();
}


const spatialCoord_t Camera::get(const windowPos_t &pos)
{
	GLdouble	modelView[16];
	GLdouble	projection[16];
	GLint		viewPort[4];
	GLint		winHorPos;
	GLint		winVerPos;

	/* get matrix */
	glGetDoublev(GL_MODELVIEW_MATRIX,	modelView);
	glGetDoublev(GL_PROJECTION_MATRIX,	projection);
	glGetIntegerv(GL_VIEWPORT,			viewPort);

	/* top position */
	winHorPos	= (GLint)pos.horPos;
	winVerPos	= (GLint)(m_param.windowSize.height - pos.verPos); 
	exchangePos( winHorPos, winVerPos, modelView, projection, viewPort, m_select.top );

	return m_select.top;
}


const spatialArea_t Camera::get(const windowPos_t &leftTop
							, const windowSize_t &size)
{
	GLdouble	modelView[16];
	GLdouble	projection[16];
	GLint		viewPort[4];
	GLint		winHorPos;
	GLint		winVerPos;

	/* get matrix */
	glGetDoublev(GL_MODELVIEW,			modelView);
	glGetDoublev(GL_PROJECTION_MATRIX,	projection);
	glGetIntegerv(GL_VIEWPORT,			viewPort);

	/* top position */
	winHorPos	= (GLint)leftTop.horPos;
	winVerPos	= (GLint)(m_param.windowSize.height - leftTop.verPos);
	exchangePos( winHorPos, winVerPos, modelView, projection, viewPort, m_select.top );

	/* left position */
	winHorPos	= (GLint)leftTop.horPos;
	winVerPos	= (GLint)(m_param.windowSize.height - (leftTop.verPos + size.height));
	exchangePos( winHorPos, winVerPos, modelView, projection, viewPort, m_select.left );

	/* bottom position */
	winHorPos	= (GLint)(leftTop.horPos + size.width);
	winVerPos	= (GLint)(m_param.windowSize.height - (leftTop.verPos + size.height));
	exchangePos( winHorPos, winVerPos, modelView, projection, viewPort, m_select.bottom );

	/* right position */
	winHorPos	= (GLint)(leftTop.horPos + size.width);
	winVerPos	= (GLint)(m_param.windowSize.height - leftTop.verPos);
	exchangePos( winHorPos, winVerPos, modelView, projection, viewPort, m_select.right );

	return m_select;
}


bool Camera::exchangePos( const GLint		winHorPos
						, const GLint		winVerPos
						, const GLdouble	modelView[16]
						, const GLdouble	projection[16]
						, const GLint		viewPort[4]
						, spatialCoord_t	&exchangeValue )
{
	bool		isExchanged;
	GLfloat		depth = 0.0f;

	glReadPixels( winHorPos, winVerPos, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth );
	if (GLU_TRUE == gluUnProject( winHorPos, winVerPos, depth
								, modelView, projection, viewPort
								, &m_posX, &m_posY, &m_posZ )) {
		exchangeValue.xValue	= m_fieldConf.toFieldPosition(m_posX);
		exchangeValue.yValue	= m_fieldConf.toFieldPosition(m_posY);
		exchangeValue.zValue	= m_fieldConf.toFieldPosition(m_posZ);
		isExchanged				= true;
	} else {
		exchangeValue.xValue	= 0u;
		exchangeValue.yValue	= 0u;
		exchangeValue.zValue	= 0u;
		isExchanged				= false;
	}
	return isExchanged;
}