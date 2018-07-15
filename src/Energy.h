#pragma once

class Energy
{
public:
	Energy(unsigned int initValue, unsigned int capacity);
	~Energy(void);

	unsigned int add(unsigned int value);
	unsigned int consume(unsigned int value);
	unsigned int get(void);

private:
	unsigned int m_value;
	unsigned int m_capacity;
};

