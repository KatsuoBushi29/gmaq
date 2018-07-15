#pragma once

#include<vector>

#define INTCOS_FRAC_BITNUM		(10u)
#define INTCOS_DEG_90			(90u)
#define INTCOS_DEG_180			(180u)
#define INTCOS_DEG_270			(270u)
#define INTCOS_DEG_360			(360u)


class IntCos
{
public:
	IntCos(void);
	~IntCos(void);

	int getValue(unsigned int deg);

private:
	std::vector<int>	*m_pCosTbl;
};

