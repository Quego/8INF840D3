#ifndef Automaton_H
#define Automaton_H

#include "stdafx.h"
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

	Automaton(int alphabetSize, int stateNumber, Node<T*> initialState, int finalStateNumber,
		Node<T> finalStates[], int transitionsNumber);
	
	static Automaton<T> Parse(std::string filename);

private:

	/** \brief The size of the alphabet. */
	int m_alphabetSize;

	/** \brief The number of states. */
	int m_stateNumber;

	/** \brief The initial state .*/
	Node<T>* m_pinitialState;

	/** \brief The number of final states. */
	int m_finalStateNumber;

	/** \brief The final states.*/
	std::vector<Node<T>> m_finalStates;

	/** \brief The number of transitions. */
	int m_transitionsNumber;

};

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

	}

	return Automaton<T>();
	// Taille de l'alphabet
	// Nombre d'etats
	// Noeud initial
	// Nombres des noeuds finaux
	// Les etats finaux 
	// Nombre de transitions
	// Les transitions
}

template<typename T>
inline Automaton<T>::Automaton()
{
}

template<typename T>
inline Automaton<T>::Automaton(int alphabetSize, int stateNumber, Node<T*> initialState, int finalStateNumber, Node<T> finalStates[], int transitionsNumber)
{
}


#endif