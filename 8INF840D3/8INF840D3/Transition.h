#ifndef TRANSITION_H
#define TRANSITION_H

#include <vector>

template<typename T>
class Node;

template<typename T>
class Transition
{
public:


private:
	T m_value;

	int m_weight;

	Node<T>* m_destination;

};

#endif
