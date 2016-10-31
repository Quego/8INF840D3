#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Transition.h"

/** \brief Representation of a Node. */
template<typename T>
class Node
{
public:

	Node(int id, bool final);

	void addTransition(Transition<T>* transition);

	void addParent(Node<T>* parents);

	int getId() const;
	
	bool isFinal() const;

	std::vector<Node<T>*> getParents();

	std::vector<Transition<T>*> getTransitions();

private:
	
	/** The ID of the node.*/
	int m_id;

	/** Whether the node is a final state or note.*/
	bool m_isFinal;

	/** The parents of the node.*/
	//TODO Usefull?
	std::vector<Node<T>*> m_parents;

	/** The transitions of the ndoe.*/
	std::vector<Transition<T>*> m_transitions;
};


#endif

