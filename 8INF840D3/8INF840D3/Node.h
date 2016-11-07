#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

/** \brief Representation of a Node. */
template<typename T>
class Node
{
public:

	Node(int id, bool final);


	void addParent(Node<T>* parents);

	int getId() const;
	
	bool isFinal() const;

	std::vector<Node<T>*> getParents();



private:
	
	/** The ID of the node.*/
	int m_id;

	/** Whether the node is a final state or note.*/
	bool m_isFinal;

	/** The parents of the node.*/
	//TODO Usefull?
	std::vector<Node<T>*> m_parents;

};
template<typename T>
std::ostream& operator << (std::ostream& os, Node<T> const& node);


#endif
