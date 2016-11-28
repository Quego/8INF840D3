#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Transition.h"

using namespace std;

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

	void setFinal(bool isFinal);

	/** \brief transtions getter.
	* \return The transitions of the node.
	*/
	std::vector<Transition<T>*> getTransitions();

	/** \brief transtion getter.
	* \param index The wanted index
	* \return The transition at the wanted index of the node.
	*/
	Transition<T>* getTransitionAt(int index);

	Transition<T>* getTransition(int currentId, int destinationId);

	/** \brief Add a transition to the Node
	* \param destination The destination node.
	* \param value The value of the Transition.
	* \param weight The weight of the Transition.
	*/
	void addTransition(Node<T>* destination, T value, int weight);

	/** \brief Add a transition to the automaton
	* \param transition The transition to add
	*/
	void addTransition(Transition<T>* transition);

	/** \brief find the next Node with the wanted value on the transition.
	* \param value The wanted value on the transition
	* \return The next Node with the wanted value on the transition, nullptr if there is no node for this value
	*/
	Node<T>* nodeOn(T value);

private:
	
	/** The ID of the node.*/
	int m_id;

	/** Whether the node is a final state or note.*/
	bool m_final;

	/** The transitions of the node.*/
	std::vector<Transition<T>*> m_transitions;

};

template<typename T>
std::ostream& operator << (std::ostream& os, Node<T> const& node)
{
	os << node.getId();
	return os;
}


template<typename T>
inline Node<T>::Node(int id, bool final) :
	m_id(id),
	m_final(final)
{
	m_transitions = std::vector<Transition<T>*>();
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
inline void Node<T>::setFinal(bool isFinal)
{
	m_final = isFinal;
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

template<typename T>
inline Transition<T>* Node<T>::getTransition(int currentId, int destinationId)
{
	for (Transition<T>* transition : m_transitions) {
		if (transition->getCurrent()->getId() == currentId && transition->getDestination()->getId() == destinationId) {
			return transition;
		}
	}
	return nullptr;
}

template<typename T>
inline void Node<T>::addTransition(Node<T>* destination, T value, int weight)
{
	Transition<T>* transition = new Transition<T>(this, destination, value, weight);
	m_transitions.push_back(transition);
}

template<typename T>
inline void Node<T>::addTransition(Transition<T>* transition)
{
	m_transitions.push_back(transition);
}

template<typename T>
inline Node<T>* Node<T>::nodeOn(T value)
{
	for (unsigned int index = 0; index < m_transitions.size(); index++)
	{
		if (m_transitions.at(index)->getValue() == value)
			return m_transitions.at(index)->getDestination();
	}
	return nullptr;
}
#endif