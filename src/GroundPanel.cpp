
/*- --- header files --- -*/
#include "GroundPanel.h"
#include <gl/freeglut.h>


/*- --- method --- -*/
GroundPanel::GroundPanel(void)
{
	/*- object size -*/
	m_width		= 0.0;
	m_height	= 0.0;
	m_thickness	= 0.0;
	/*- color value -*/
	m_red		= 0;
	m_green		= 0;
	m_blue		= 0;
	m_alpha		= 0;
}


GroundPanel::~GroundPanel(void)
{
}


void GroundPanel::setShape(double width, double height, double thickness)
{
	m_width		= width;
	m_height	= height;
	m_thickness = thickness;
}


void GroundPanel::setColor(float red, float green, float blue, float alpha)
{
	m_red		= red;
	m_green		= green;
	m_blue		= blue;
	m_alpha		= alpha;
}


void GroundPanel::drawObject(double pos_x, double pos_y, double pos_z)
{
	glBegin(GL_QUADS);
	glColor3f( m_red, m_green, m_blue );
	glVertex3d(pos_x			, pos_y				, pos_z            );
	glVertex3d(pos_x + m_width	, pos_y				, pos_z            );
	glVertex3d(pos_x + m_width	, pos_y				, pos_z + m_height );
	glVertex3d(pos_x			, pos_y				, pos_z + m_height );
	glEnd();
}