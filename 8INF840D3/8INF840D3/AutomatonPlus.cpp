#include "stdafx.h"
#include "AutomatonPlus.h"

template<typename T>
AutomatonPlus<T>::AutomatonPlus(int alphabetSize, int wordSize, const Node<T>& initialNode, std::vector<Node<T>*> finalNodes, std::vector<Transition<T>*> transitions, std::map<T, Constraint> constraintsValues) :
	m_alphabetSize(alphabetSize), m_inode(initialNode), m_wordSize(wordSize), m_fnodes(finalNodes), m_transitions(transitions), m_constraintsValues(constraintsValues){
	

	for (Transition<T>* transition : m_transitions) {
		Node<T> n = *transition->getCurrent();
		if(!(std::find(m_nodes.begin(), m_nodes.end(), n) != m_nodes.end())) {
			m_nodes.push_back(n);
		}
	}
}

template <typename T>
AutomatonPlus<T>::~AutomatonPlus()
{
}

template<typename T>
AutomatonPlus<T> AutomatonPlus<T>::Parse(std::string filename, Automaton<T> automaton) throw(std::logic_error)
{

	std::ifstream file(filename, std::ios::in);
	if (file.is_open())
	{

		int alphabetSize;
		int wordSize;
		std::map<T, Constraint> constraintsValues;
		std::string content;
		
		getline(file, content);
		alphabetSize = std::stoi(content);
		if (alphabetSize != automaton.getAlphabetSize()) {
			throw std::logic_error("Parse : La taille de l'alphabet ne correspond avec celle de l'automate");
		}
		
		getline(file, content);
		wordSize = std::stoi(content);

		std::string content1;
		std::string content2;
		getline(file, content1);
		getline(file, content2);
		for (int index = 0; index < alphabetSize; index++)
		{
			std::string minConstraint = content1.substr(0, content1.find(" "));
			std::string maxConstraint = content2.substr(0, content2.find(" "));
			Constraint constraint = Constraint(std::stoi(minConstraint), std::stoi(maxConstraint));
			constraintsValues[automaton.getTransitions().at(index)->getValue()]= constraint;
			content1.erase(0, minConstraint.size() + 1);
			content2.erase(0, maxConstraint.size() + 1);

		}
		
		return AutomatonPlus<T>(alphabetSize, wordSize, automaton.getInitialState(), automaton.getFinalStates(), automaton.getTransitions(), constraintsValues);
	}
	else
		throw std::logic_error("Parse : le fichier ne peut être lu");
}

template<typename T>
const Node<T>& AutomatonPlus<T>::getInitialState() const
{
	return m_inode;
}

template<typename T>
const std::vector<Node<T>*>& AutomatonPlus<T>::getFinalStates() const
{
	return m_fnodes;
}


template<typename T>
const std::vector<Node<T>>& AutomatonPlus<T>::getNodes() const
{

	return m_nodes;
}


