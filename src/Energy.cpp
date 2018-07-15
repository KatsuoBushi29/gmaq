#include "Energy.h"


Energy::Energy(unsigned int initValue, unsigned int capacity) :
	m_value(initValue), 
	m_capacity(capacity)
{
	m_value = (m_value > m_capacity) ?  m_capacity : m_value;
}


Energy::~Energy(void)
{
}

unsigned int Energy::add(unsigned int value)
{
	unsigned int modValue = 0u;

	if((m_capacity - m_value) < value){
		modValue = value - (m_capacity - m_value);
		m_value  = m_capacity;
	}
	else{
		modValue = 0u;
		m_value += value;
	}
	return modValue;
}

unsigned int Energy::consume(unsigned int value)
{
	unsigned int consumeValues = 0u;

	if(m_value < value){
		consumeValues = m_value;
		m_value       = 0u;
	}
	else{
		consumeValues = value;
		m_value      -= value;
	}
	return consumeValues;
}

unsigned int Energy::get(void)
{
	return m_value;
}