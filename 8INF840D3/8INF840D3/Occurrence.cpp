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
