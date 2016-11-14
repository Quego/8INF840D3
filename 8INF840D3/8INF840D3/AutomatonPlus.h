#pragma once
#ifndef AUTOMATONPLUS_H
#define AUTOMATONPLUS_H

#include "Automaton.h"
#include "Constraint.h"
#include <map>





template <typename T>
class AutomatonPlus
{
public:
	AutomatonPlus(int alphabetSize, int wordSize, const Node<T>& initalNode, std::vector<Node<T>*> finalNodes, std::vector<Transition<T>*> transitions, std::map<T, Constraint> constraintsValues);
	~AutomatonPlus();

	AutomatonPlus<T> static Parse(std::string filename, Automaton<T>) throw(std::logic_error);

	const Node<T>& getInitialState() const;
	
	const std::vector<Node<T>*>& getFinalStates() const;

	const std::vector<Node<T>>& getNodes() const;

private:
	int m_alphabetSize;
	int m_wordSize;
	Node<T> m_inode;
	std::vector<Node<T>*> m_fnodes;
	std::vector<Transition<T>*> m_transitions;
	std::vector<Node<T>> m_nodes;
	std::map<T, Constraint> m_constraintsValues;


};

template<typename U>
inline std::ostream & operator<<(std::ostream & f, const AutomatonPlus<U>& q)
{
	cout << "Noeuds : ";

	for (Node<U> n : q.getNodes()) {
		f << n << " | " ;
	}
	f << "\nNoeud Initial: " << q.getInitialState() << endl;
	f << "Noeuds finau(x) : ";
	for (Node<U>* finalNode : q.getFinalStates())
		f << *finalNode << " |";
	f << "\n";
	return f;
}

#endif // !AUTOMATONPLUS_H
