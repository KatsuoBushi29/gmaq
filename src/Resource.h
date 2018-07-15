#pragma once

typedef enum
{
	RESOURCE_FULL = 0,
	RESOURCE_RICH,
	RESOURCE_POOR,
	RESOURCE_EMPTY,
} ResourceStatus_t;


class Resource
{
public:
	Resource( unsigned int initValue
			, unsigned int maxValue
			, unsigned int poorThrethold
			, unsigned int richThrethold );
	~Resource(void);

	ResourceStatus_t add(unsigned int value);
	ResourceStatus_t reduce(unsigned int value);
	ResourceStatus_t getStatus(void);
	unsigned int getValue(void);

private:
	void updateStatus(void);

	unsigned int m_value;
	unsigned int m_maxValue;
	unsigned int m_poorThrethold;
	unsigned int m_richThrethold;
	ResourceStatus_t m_status;
};

