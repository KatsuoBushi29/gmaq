
#pragma once

/*- --- header files --- -*/


/*- --- class define --- -*/
class GroundPanel
{

public:
	GroundPanel();
	virtual ~GroundPanel(void);

	void setShape(double width, double height, double thickness);
	void setColor(float red, float green, float blue, float alpha);
	void drawObject(double pos_x, double pos_y, double pos_z);

private:
	/*- object size -*/
	double m_width;
	double m_height;
	double m_thickness;
	/*- color value -*/
	float m_red;
	float m_green;
	float m_blue;
	float m_alpha;
};

