#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "stdafx.cpp"
#include "Transition.h"
#include "Node.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

/** \brief Representation of an automaton. */
template<typename T>
class Automaton
{
public:

	/** \brief Constructor.*/
	Automaton();

	/** \brief Constructor.
	* \param alphabetSize The size of the alphabet.
	* \param stateNumber The number of states.
	* \param initialState The initial state 
	* \param finalStateNumber The number of final states.
	* \param finalStates The final states.
	* \param transitionsNumber The number of transitions.
	*/
	Automaton(int alphabetSize, int stateNumber, std::vector<Node<T>*> states, Node<T>* initialState, int finalStateNumber,
		std::vector<Node<T>*> finalStates, int transitionsNumber);

	/** \brief Parse a file into an Automaton
	* \param filename The name of the file to parse
	* \return An Automaton from a file.
	*/
	static Automaton<T> Parse(std::string filename);

	/** \brief Add a transition to the automaton
	* \param transition The transition to add
	*/
	void addTransition(Transition<T>* transition);

	/** \brief transtions getter.
	* \return The transitions of the automaton.
	*/
	std::vector<Transition<T>*> getTransitions();

	/** \brief states getter.
	* \return The states of the automaton.
	*/
	const std::vector<Node<T>*> getStates() const;

	/** \brief initialState getter.
	* \return The inital state of the automaton.
	*/
	const Node<T>& getInitialState() const;

	/** \brief finalState getter.
	* \return The final states of the automaton.
	*/
	const std::vector<Node<T>*> getFinalStates() const;

	/**  \brief operator override */
	template <typename U> friend std::ostream& operator << (std::ostream& f, const Automaton<U>& q);

private:

	/** \brief The size of the alphabet. */
	int m_alphabetSize;

	/** \brief The number of states. */
	int m_stateNumber;

	/** \brief All the states from the automaton. */
	std::vector<Node<T>*> m_states;

	/** \brief The initial state. */
	Node<T>* m_pinitialState;

	/** \brief The number of final states. */
	int m_finalStateNumber;

	/** \brief The final states. */
	std::vector<Node<T>*> m_finalStates;

	/** \brief The number of transitions. */
	int m_transitionsNumber;

	/** The transitions of the node. */
	std::vector<Transition<T>*> m_transitions;

};

//4 taille alphabet
//4  nombre d'état
//1  noeud initial
//4  le nombre des états finaux
//1 2 3 4 les états finaux
//10	nombre de transitions
//1 1 2 4  on va de 1 à 2 de coût 4 et en lisant la lettre 1
//1 2 2 3  on va de 2 à 2 de coût 3 et en lisant la lettre 1
template<typename T>
inline Automaton<T> Automaton<T>::Parse(std::string filename)
{
	std::ifstream file(filename, std::ios::in);

	if (file.is_open()) 
	{
		int alphabetSize;
		int stateNumber;
		int initialStateId;
		int finalStateNumber;
		std::vector<int> finalStatesId;
		int transitionsNumber;

		std::string content;

		getline(file, content);
		alphabetSize = std::stoi(content);

		getline(file, content);
		stateNumber = std::stoi(content);

		getline(file, content);
		initialStateId = std::stoi(content);

		getline(file, content);
		finalStateNumber = std::stoi(content);

		getline(file, content);
		for (int index = 0; index < finalStateNumber; index++)
		{
			std::string finalStateId = content.substr(0, content.find(" "));
			finalStatesId.push_back(std::stoi(finalStateId));
			content.erase(0, finalStateId.size() + 1);
		}

		getline(file, content);
		transitionsNumber = std::stoi(content);
		

		//Creation of Nodes
		std::vector<Node <T>*> statesInAutomaton;
		std::vector<Node <T>*> finalStates;
		for (int i = 1; i < stateNumber+1; ++i)
		{
			bool isFinal = false;
			for (int nodeId : finalStatesId) {
				if (i == nodeId) {
					isFinal = true;
				}
			}
			Node<T>* nodeCurrent = new Node<T>(i, isFinal);
			if (isFinal) {
				finalStates.push_back(nodeCurrent);
			}
			statesInAutomaton.push_back(nodeCurrent);
		}

		Node<T>* initialNode = statesInAutomaton.at(initialStateId - 1);

		Automaton<T> parsedAutomaton(alphabetSize, stateNumber, statesInAutomaton, initialNode, finalStateNumber, finalStates, transitionsNumber);

		//Creation of Transitions
		for (int cptTransition = 0; cptTransition < transitionsNumber; ++cptTransition)
		{
			Node<T>* nodeDestination = NULL;
			Node<T>* nodeCurrent = NULL;

			getline(file, content);
			std::string transitionDetail = content.substr(0, content.find(" "));
			T value = std::stoi(transitionDetail);
			content.erase(0, transitionDetail.size()+1);
			transitionDetail = content.substr(0, content.find(" "));
			int idNodeCurrent = std::stoi(transitionDetail);
			content.erase(0, transitionDetail.size()+1);
			transitionDetail = content.substr(0, content.find(" "));
			int idNodeDestination = std::stoi(transitionDetail);
			content.erase(0, transitionDetail.size()+1);
			transitionDetail = content.substr(0, content.find(" "));
			int weight = std::stoi(transitionDetail);
			content.erase(0, transitionDetail.size()+1);
			
			std::vector<Node <T>*>::iterator ite = statesInAutomaton.begin();

			while((nodeDestination == 0 || nodeCurrent == 0) && ite!= statesInAutomaton.end()){
				if ((*ite)->getId() == idNodeCurrent) {
					nodeCurrent = (*ite);
				}
				if ((*ite)->getId() == idNodeDestination) {
					nodeDestination = (*ite);
				}
				++ite;
			}
			if (nodeCurrent != 0 && nodeDestination != 0)
				nodeCurrent->addTransition(nodeDestination, value, weight);
				parsedAutomaton.addTransition(nodeCurrent->getTransitions().back());
		}
		return parsedAutomaton;

	}

	return Automaton<T>();
}

template<typename T>
inline const Node<T>& Automaton<T>::getInitialState() const
{
	return *m_pinitialState;
}

template<typename T>
inline const std::vector<Node<T>*> Automaton<T>::getFinalStates() const
{
	return m_finalStates;
}

template<typename T>
inline Automaton<T>::Automaton()
{
}

template<typename T>
inline Automaton<T>::Automaton(int alphabetSize, int stateNumber, std::vector<Node<T>*> states, Node<T>* initialState, int finalStateNumber, std::vector<Node<T>*> finalStates, int transitionsNumber)
{
	m_alphabetSize = alphabetSize;
	m_stateNumber = stateNumber;
	m_states = states;
	m_pinitialState = initialState;
	m_finalStateNumber = finalStateNumber;
	m_finalStates = finalStates;
	m_transitionsNumber = transitionsNumber;
}


template<typename T>
inline void Automaton<T>::addTransition(Transition<T>* transition)
{
	if (transition != 0) {
		m_transitions.push_back(transition);
	}
}

template<typename T>
inline std::vector<Transition<T>*> Automaton<T>::getTransitions()
{
	return m_transitions;
}

template<typename T>
inline const std::vector<Node<T>*> Automaton<T>::getStates() const
{
	return m_states;
}


template<typename U>
inline std::ostream & operator<<(std::ostream & f, const Automaton<U>& q)
{
	f << "Noeuds: ";
	for (Node<U>* node : q.getStates())
		f << *node << " |";
	f << "\nNoeud Initial: " << q.getInitialState() << endl;
	f << "Noeuds finau(x) : ";
	for (Node<U>* finalNode : q.getFinalStates())
		f << *finalNode << " |";
	f << "\n";
	return f;
}


#endif

