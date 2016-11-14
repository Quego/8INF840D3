#ifndef TRANSITION_H
#define TRANSITION_H

#include <vector>
#include "Node.cpp"

/** \brief Representation of a Transition. */
template<typename T>
class Transition
{
public:

	/** \brief Constructor.
	* \param current The current node.
	* \param destination The destination node.
	* \param value The value of the Transition.
 	* \param weight The weight of the Transition.
	*/
	Transition(Node<T>* current, Node<T>* destination, T value, int weight);

	/** \brief Current node getter.
	* \return The current node.
	*/
	Node<T>* getCurrent() const;

	/** \brief Destination node getter. 
	* \return The destination node.
	*/
	Node<T>* getDestination() const;

	/** \brief Weight getter.
	* \return The weight.
	*/
	int getWeight() const;

	/** \brief value getter.
	* \return The value.
	*/
	T getValue() const;

private:

	/** \brief The current Node. */
	//TODO Usefull?
	Node<T>* m_current;

	/** \brief The destination Node. */
	Node<T>* m_destination;

	/** \brief The value of the Transition. */
	T m_value;

	/** \brief The weight of the Transition. */
	int m_weight;

};

template <typename T>
inline 	Transition<T>::Transition(Node<T>* current, Node<T>* destination, T value, int weight) :
	m_current(current),
	m_destination(destination),
	m_value(value),
	m_weight(weight)
{}

template <typename T>
inline Node<T>* Transition<T>::getCurrent() const
{
	return m_current;
}

template <typename T>
inline Node<T>* Transition<T>::getDestination() const
{
	return m_destination;
}

template <typename T>
inline T Transition<T>::getValue() const
{
	return m_value;
}

template <typename T>
inline int Transition<T>::getWeight() const
{
	return m_weight
}

#endif