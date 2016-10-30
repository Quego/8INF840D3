#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Transition.h"

template<typename T>
class Node
{
public:


private:
	
	int id;

	bool isFinal;

	std::vector<Node<T>*> m_parents;

	std::vector<Transition<T>> m_transitions;
};


#endif

