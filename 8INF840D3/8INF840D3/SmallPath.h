#pragma once
#ifndef SMALLPATH_H
#define SMALLPATH_H

#include "stdafx.cpp"
#include "Automaton.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>

/** \brief Representation of an automaton. */
template<typename T>
class SmallPath {

public:


	/** \brief Constructor.
	* \param automaton the graph to calculate
	*/
	SmallPath(Automaton<T> automaton);

	void calculateDijkstra(Limit limite, std::string word);

	void relax(Node<T>* currentNode, Node<T>* destinationNode, int weightTransition, int positionWord);

	void display(std::string word);

private:

	/** \brief The automaton. */
	Automaton<T> m_automaton;

	/** \brief The weight associated to nodesId. */
	std::vector<int> m_weights;

	/** \brief A tuple which contains :
	*   - the weight associated to nodeId(=position-1 in vector).
	*   - the previous node to get this weight.
	*	- the index position of the word.
	*/
	std::vector <std::tuple< Node<T>*, int, int>> m_tripleNodeWeightPositionWord;
};

#endif // !SMALLPATH_H

template<typename T>
inline SmallPath<T>::SmallPath(Automaton<T> automaton)
{
	m_automaton = automaton;	
}

/**
 * \brief calculate the smaller path of a word in a graph with Dijkstra Algorithm
 */
template<typename T>
inline void SmallPath<T>::calculateDijkstra(Limit limite, std::string word)
{
	//Algorithme Dijkstra
	//initialisation
	//TODO : Rajouter conditions par rapport aux min Occurences 
	for (int i = 0; i < m_automaton.getStates().size(); ++i) {
		// Représente l'arbre par couche, non parfait, faire une double liste chainée
		m_tripleNodeWeightPositionWord.push_back(std::make_tuple((Node<T>*) NULL, INT_MAX, 0));
	}
	int position = m_automaton.getInitialState().getId() - 1;
	m_tripleNodeWeightPositionWord.at(position) = std::make_tuple((Node<T>*) NULL, 0, 0);
	std::vector<Node<T>*> V = m_automaton.getStates();
	std::vector<Node<T>*> S;
	std::vector<Node<T>*> fileNodes;
	std::vector<Transition<T>*> transitions = m_automaton.getTransitions();
	std::vector<Occurrence> occurrences = limite.getOccurences();
	fileNodes.push_back(m_automaton.getStates().at(position));

	while (!fileNodes.empty()) {
		//Traitement d'un noeud
		int positionWord;
		position = fileNodes.front()->getId()-1;
		int minWeight = INT_MAX;
		for(Node<T>* node : fileNodes){
			std::tuple<Node<T>*, int, int > tupleToFind = m_tripleNodeWeightPositionWord.at(node->getId() - 1);
			if (std::get<1>(tupleToFind) < minWeight) {
				position = node->getId() - 1;
				minWeight = std::get<1>(tupleToFind);
				positionWord = std::get<2>(tupleToFind);
			}
		}
		Node<T>* currentNode = V.at(position);
		auto it = std::find(fileNodes.begin(), fileNodes.end(), currentNode);
		if (it != fileNodes.end()) {
			fileNodes.erase(it);
			S.push_back(currentNode);
		}

		//Verification des transitions
		for (int index = 0; index < currentNode->getTransitions().size(); ++index) {
			Transition<T>* transition = currentNode->getTransitionAt(index);
			if (transition->getValue() == word.at(positionWord)-'0') {
				bool isfinal = false;
				if (positionWord + 1 == word.size() - 1) {
					//Le noeud à la position n pour un mot de taille n+1 doit être final
					auto finalStates = m_automaton.getFinalStates();
					for (auto ite = std::begin(finalStates); ite != std::end(finalStates); ++ite) {
						if (*ite == transition->getDestination()) {
							isfinal = true;
							break;
						}
					}
				}
				if (positionWord + 1 < word.size()-1 || isfinal ) {					
					int currentMaxOccurence = occurrences.at(transition->getValue() - 1).getMax();
					if (currentMaxOccurence > 0) {
						relax(currentNode, transition->getDestination(), transition->getWeight(), positionWord + 1);
						fileNodes.push_back(transition->getDestination());
						occurrences.at(transition->getValue() - 1).setMax(currentMaxOccurence - 1);
					}
				}
				
			}
		}
	}
	// calcul du plus court chemin selon le résultat du noeud final
	int max = INT_MAX;
	bool isFind = false;

	for (Node<T>* finalNode : m_automaton.getFinalStates()) {
		std::tuple<Node<T>*, int, int > tuple = m_tripleNodeWeightPositionWord.at(finalNode->getId()-1);
		if (std::get<0>(tuple) != 0) {
			cout << "Noeud : " << *std::get<0>(tuple) << ", Poids : " << std::get<1>(tuple) << ", Position du mot : " << std::get<2>(tuple) <<  endl;
		}
		if (std::get<0>(tuple) != 0 && std::get<1>(tuple) < max && std::get<2>(tuple)==word.size()-1) {
			max = std::get<1>(tuple);
			isFind = true;
		}
	}
	if (isFind) {
		cout << "Le plus court chemin est de poids :" << max << endl;
	}
	else {
		cout << "le chemin n'a pas ete trouve au sein du graphe" << endl;
	}
}

//Comparaison des chemins
template <typename T>
inline void SmallPath<T>::relax(Node<T>* currentNode, Node<T>* destinationNode, int weightTransition, int positionWord)
{
	std::tuple<Node<T>*, int, int > tupleToFind = m_tripleNodeWeightPositionWord.at(destinationNode->getId() - 1);
	std::tuple<Node<T>*, int, int > tupleCurrent = m_tripleNodeWeightPositionWord.at(currentNode->getId() - 1);
	if (std::get<1>(tupleToFind) > std::get<1>(tupleCurrent) + weightTransition || std::get<2>(tupleToFind)<positionWord) {
		m_tripleNodeWeightPositionWord.at(destinationNode->getId() - 1) = std::make_tuple(currentNode, std::get<1>(tupleCurrent) + weightTransition, positionWord);
		std::tuple<Node<T>*, int, int > tupleToFind = m_tripleNodeWeightPositionWord.at(destinationNode->getId() - 1);
	}
}

template <typename T>
inline void SmallPath<T>::display(std::string word) {

}