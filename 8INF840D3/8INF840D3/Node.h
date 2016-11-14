#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

template <typename T>
class Transition;

/** \brief Representation of a Node. */
template<typename T>
class Node
{
public:

	/** \brief Constructor.
	* \param id The id of the Node.
	* \param final Whether the Node is a final Node or not.
	*/
	Node(int id, bool final);

	/** \brief id getter.
	* \return The id of the Node.
	*/
	int getId() const;
	
	/** \brief final getter.
	* \return True if the Node is a final Node, false if not.
	*/
	bool isFinal() const;

	/** \brief transtions getter.
	* \return The transitions of the node.
	*/
	std::vector<Transition<T>*> getTransitions();

	/** \brief transtion getter.
	* \param index The wanted index
	* \return The transition at the wanted index of the node.
	*/
	Transition<T>* getTransitionAt(int index);

private:
	
	/** The ID of the node.*/
	int m_id;

	/** Whether the node is a final state or note.*/
	bool m_final;

	/** The transitions of the node.*/
	std::vector<Transition<T>*> m_transitions;

};

template<typename T>
std::ostream& operator << (std::ostream& os, Node<T> const& node);

template<typename T>
inline Node<T>::Node(int id, bool final) :
	m_id(id),
	m_final(final)
{
	m_transitions = std::vector<Transition<T>*> ();
}

template<typename T>
inline int Node<T>::getId() const 
{
	return m_id;
}

template<typename T>
inline bool Node<T>::isFinal() const
{
	return m_final;
}

template<typename T>
inline std::vector<Transition<T>*> Node<T>::getTransitions()
{
	return m_transitions;
}

template<typename T>
inline Transition<T>* Node<T>::getTransitionAt(int index)
{
	return m_transitions.at(index);
}

#endif