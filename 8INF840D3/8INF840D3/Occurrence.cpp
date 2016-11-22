#include "stdafx.h"
#include "Occurrence.h"

Occurrence::Occurrence()
{
}

Occurrence::Occurrence(int min, int max) :
	m_min(min),
	m_max(max)
{
}

int Occurrence::getMin() const
{
	return m_min;
}

int Occurrence::getMax() const
{
	return m_max;
}

void Occurrence::setMin(int min)
{
	m_min = min;
}

void Occurrence::setMax(int max)
{
	m_max = max;
}
