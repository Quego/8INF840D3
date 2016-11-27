#pragma once
#ifndef SMALLPATH_H
#define SMALLPATH_H

#include "stdafx.cpp"
#include "LayeredGraph.h"
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
	SmallPath(Automaton<T> automaton, LayeredGraph<T> layeredGraph);

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
	LayeredGraph<T> m_layeredGraph;

};

#endif // !SMALLPATH_H

template<typename T>
inline SmallPath<T>::SmallPath(Automaton<T> automaton, LayeredGraph<T> layeredGraph)
{
	m_automaton = automaton;
	m_layeredGraph = layeredGraph;
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
	m_layeredGraph.init();
	int position = m_automaton.getInitialState().getId() - 1;
	//m_tripleNodeWeightPositionWord.at(position) = std::make_tuple((Node<T>*) NULL, 0, 0);
	std::vector<std::vector<std::pair<Node<T>*, int>>> paireNodeWeight = m_layeredGraph.getLayers();
	std::vector<Node<T>*> V = m_automaton.getStates();
	std::vector<Node<T>*> S;
	std::vector<std::pair<Node<T>*,int>> fileNodes;
	std::vector<Transition<T>*> transitions = m_automaton.getTransitions();
	std::vector<Occurrence> occurrences = limite.getOccurences();
	fileNodes.push_back(make_pair(m_automaton.getStates().at(position),0));

	while (!fileNodes.empty()) {
		//Traitement d'un noeud
		std::pair < Node<T>*, int> nodeToRemove;
		int positionWord=0;
		position = fileNodes.front().first->getId();
		int minWeight = INT_MAX;
		for(std::pair<Node<T>*, int> node : fileNodes){
			//std::tuple<Node<T>*, int, int > tupleToFind = m_tripleNodeWeightPositionWord.at(node->getId() - 1);
			std::vector<std::pair<Node<T>*, int>> paireToFind = m_layeredGraph.getLayer(node.second);
			std::cout << " Poids : " << paireToFind.at(node.first->getId() - 1).second  << std::endl;
			if (paireToFind.at(node.first->getId()-1).second <= minWeight) {
				position = node.first->getId() - 1;
				minWeight = paireToFind.at(node.first->getId()-1).second;
				positionWord = node.second;
				std::cout << " Position de la lettre : " << node.second << std::endl;

				nodeToRemove = node;
				
			}
		}
		Node<T>* currentNode = V.at(position);
		std::cout << " NoeudTraité : " << *currentNode << std::endl;


		auto it = std::find(fileNodes.begin(), fileNodes.end(), nodeToRemove);
		if (it != fileNodes.end()) {
			//fileNodes.erase(remove_if(fileNodes.begin(), fileNodes.end(), [](pair<string, string> pair) { return pair.second == "ore"; }));

			fileNodes.erase(it);
			S.push_back(currentNode);
		}
		std::cout << "Taille : " << fileNodes.size() << std::endl;

		//Verification des transitions
		for (unsigned int index = 0; index < currentNode->getTransitions().size(); ++index) {
			std::cout << "test 1" << std::endl;

			Transition<T>* transition = currentNode->getTransitionAt(index);

			if (transition->getValue() == word.at(positionWord)-'0') {
				std::cout << "test 2" << std::endl;

				bool isfinal = false;
				if (positionWord + 1 == word.size()) {
					std::cout << "test 3" << std::endl;

					//Le noeud à la position n pour un mot de taille n+1 doit être final
					auto finalStates = m_automaton.getFinalStates();
					for (auto ite = std::begin(finalStates); ite != std::end(finalStates); ++ite) {
						if (*ite == transition->getDestination()) {
							isfinal = true;
							break;
						}
					}
					std::cout << "test 4" << std::endl;

				}
				std::cout << "test 5" << std::endl;

				if (positionWord + 1 < word.size() || isfinal ) {					
					int currentMaxOccurence = occurrences.at(transition->getValue() - 1).getMax();
					if (currentMaxOccurence > 0) {
						relax(currentNode, transition->getDestination(), transition->getWeight(), positionWord+1);
						std::cout << "Valeur Calculee : " << m_layeredGraph.getLayer(positionWord+1).at(transition->getDestination()->getId() - 1).second << std::endl;
						if (!isfinal) {
							fileNodes.push_back(make_pair(transition->getDestination(), positionWord + 1));
						}
						occurrences.at(transition->getValue() - 1).setMax(currentMaxOccurence - 1);
					}
				}
				
			}
		}
	}
	std::cout << "ON SORT!" << std::endl;
	// calcul du plus court chemin selon le résultat du noeud final
	int max = INT_MAX;
	bool isFind = false;

	for (Node<T>* finalNode : m_automaton.getFinalStates()) {
		std::pair<Node<T>*, int> paire = m_layeredGraph.getLayer(word.size()).at(finalNode->getId() - 1);
		if (paire.first != 0) {
			cout << "Noeud : " << *paire.first << ", Poids : " << paire.second << ", Position du mot : " << word.size() <<  endl;
		}
		if (paire.first != 0 && paire.second < max) {
			max = paire.second;
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
	std::pair<Node<T>*, int> paireToFind = m_layeredGraph.getLayer(positionWord).at(destinationNode->getId() - 1);
	std::pair<Node<T>*, int> paireCurrent = m_layeredGraph.getLayer(positionWord - 1).at(currentNode->getId() - 1);
	//std::tuple<Node<T>*, int, int > tupleToFind = m_tripleNodeWeightPositionWord.at(destinationNode->getId() - 1);
	//std::tuple<Node<T>*, int, int > tupleCurrent = m_tripleNodeWeightPositionWord.at(currentNode->getId() - 1);
	std::cout << "Test IMPORTANT : "<< (paireToFind.second > paireCurrent.second + weightTransition) << std::endl;
	if (paireToFind.second > paireCurrent.second + weightTransition) {

		m_layeredGraph.setWeight(positionWord, paireToFind.first->getId()-1, paireCurrent.second + weightTransition);

		//m_tripleNodeWeightPositionWord.at(destinationNode->getId() - 1) = std::make_tuple(currentNode, std::get<1>(tupleCurrent) + weightTransition, positionWord);
		//std::tuple<Node<T>*, int, int > tupleToFind = m_tripleNodeWeightPositionWord.at(destinationNode->getId() - 1);
	}
	else {
		std::cout << "POURQUOI : " << "Poids Actuel : " << paireToFind.second << std::endl;
		std::cout << "Poids Courant + Transition : " << paireCurrent.second <<" , "<<  weightTransition << std::endl;

	}
}

template <typename T>
inline void SmallPath<T>::display(std::string word) {

}