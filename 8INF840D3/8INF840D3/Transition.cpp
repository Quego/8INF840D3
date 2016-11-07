#include "stdafx.h"
#include "Transition.h"


template<typename T>
Transition<T>::Transition(Node<T>* current, Node<T>* destination, T value, int weight) :
	m_current(current),
	m_destination(destination),
	m_value(value),
	m_weight(weight)
{
}

template<typename T>
Node<T>* Transition<T>::getCurrent() const
{
	return m_current;
}

template<typename T>
Node<T>* Transition<T>::getDestination() const
{
	return m_destination;
}

template<typename T>
int Transition<T>::getWeight() const
{
	return m_weight;
}

template<typename T>
T Transition<T>::getValue() const
{
	return m_value;
}