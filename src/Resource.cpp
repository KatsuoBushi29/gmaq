#include "Resource.h"


Resource::Resource(  unsigned int initValue
				   , unsigned int maxValue
				   , unsigned int poorThrethold
				   , unsigned int richThrethold ) :
					m_value(initValue),
					m_maxValue(maxValue),
					m_poorThrethold(poorThrethold),
					m_richThrethold(richThrethold),
					m_status(RESOURCE_EMPTY)
{
	/* clip parameter */
	if(m_value > m_maxValue){
		m_value = m_maxValue;
	}
	if(m_poorThrethold > m_richThrethold){
		m_poorThrethold = m_richThrethold;
	}
	this->updateStatus();
}


Resource::~Resource(void)
{
}


ResourceStatus_t Resource::add(unsigned int value)
{
	if(value > (m_maxValue - m_value)){
		m_value  = m_maxValue;
	}
	else{
		m_value += value;
	}
	this->updateStatus();
	return m_status;
}


ResourceStatus_t Resource::reduce(unsigned int value)
{
	if(m_value > value){
		m_value -= value;
	}
	else{
		m_value  = 0u;
	}
	this->updateStatus();
	return m_status;
}


ResourceStatus_t Resource::getStatus(void)
{
	return m_status;
}


unsigned int Resource::getValue(void)
{
	return m_value;
}


void Resource::updateStatus(void)
{
	unsigned int threthold = 0u;

	switch(m_status){
	case RESOURCE_POOR:
	case RESOURCE_EMPTY:
		threthold = m_richThrethold;
		break;
	case RESOURCE_RICH:
	case RESOURCE_FULL:
		threthold = m_poorThrethold;
		break;
	default :
		/* ILLEGAL_STATUS */
		break;
	}

	if(threthold >= m_value){
		m_status = RESOURCE_POOR;
		if(0u == m_value){
			m_status = RESOURCE_EMPTY;
		}
	}
	else{
		m_status = RESOURCE_RICH;
		if(m_maxValue == m_value){
			m_status = RESOURCE_FULL;
		}
	}
}