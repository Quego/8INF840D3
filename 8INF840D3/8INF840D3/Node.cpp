#include "stdafx.h"
#include "Node.h"



template<typename T>
Node<T>::Node(int id, bool final)
{
	m_id = id;
	m_isFinal = final;
}

template<typename T>
Node<T>::Node(const Node<T> &node)
{
	m_id = node.getId();
	m_isFinal = node.isFinal();
}

template<typename T>
void Node<T>::addParent(Node<T>* parents)
{
	if (parents != 0) {
		m_parents.push_back(parents);
	}
	
}

template<typename T>
int Node<T>::getId() const
{
	return m_id;
}

template<typename T>
bool Node<T>::isFinal() const
{
	return m_isFinal;
}

template<typename T>
std::vector<Node<T>*> Node<T>::getParents()
{
	return m_parents;
}

template<typename T>
bool Node<T>::operator==(const Node<T>& node)
{
	if (m_id == node.getId() && m_isFinal == node.isFinal())
		return true;
	return false;
}

template<typename T>
inline std::ostream & operator<<(std::ostream & os, Node<T> const & node)
{
	os << node.getId();
	return os;
}


