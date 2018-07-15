#include "IntCos.h"

#define _USE_MATH_DEFINES
#include <math.h>

/*  */
const int		INTCOS_DEG_MAXNUM	= (90 + 1);	/* 0 ~ 90 */


IntCos::IntCos(void)
{
	double rad = M_PI / 180;

	m_pCosTbl = new std::vector<int>(INTCOS_DEG_MAXNUM, 0u);

	/* calculate  */
	for (unsigned int deg = 0; deg < INTCOS_DEG_MAXNUM; deg++) {
		m_pCosTbl->at(deg) = (int)( cos(((double)deg) * rad) * ((double)(1u << INTCOS_FRAC_BITNUM)) );
	}
}


IntCos::~IntCos(void)
{

}


int IntCos::getValue(unsigned int deg)
{
	int coef	= 0;

	deg %= INTCOS_DEG_360;
	/* degree : 0 ~ 89 */
	if (INTCOS_DEG_90 > deg) {
		coef	= 1;
	/* degree : 90 ~ 179 */
	} else if (INTCOS_DEG_180 > deg) {
		coef	= -1;
		deg		= INTCOS_DEG_180 - deg;
	/* degree : 180 ~ 269 */
	} else if (INTCOS_DEG_270 > deg) {
		coef	= -1;
		deg		= deg - INTCOS_DEG_180;
	/* degree : 270 ~ 359 */
	} else {
		coef	= 1;
		deg		= INTCOS_DEG_360 - deg;
	}
	return (coef * m_pCosTbl->at(deg));
}
