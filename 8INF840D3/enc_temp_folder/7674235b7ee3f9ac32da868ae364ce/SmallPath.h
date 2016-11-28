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

	void calculateDijkstra(/*Limit limite,*/ std::string word);

	void relax(Node<T>* currentNode, Node<T>* destinationNode, int weightTransition, int positionWord);

	void display(std::string word);

	void findBetweenNodes(int first, int second, Limit limit);

	std::vector<std::vector<int>> recursifParcours(Node<T>* node, int positionWord, int wordSize, std::vector<std::vector<int>> path);

private:

	/** \brief The automaton. */
	Automaton<T> m_automaton;

	/** \brief A tuple which contains :
	*   - the weight associated to nodeId(=position-1 in vector).
	*   - the previous node to get this weight.
	*	- the index position of the word.
	*/
	LayeredGraph<T> m_layeredGraph;

	std::vector<std::vector<int>> m_displayNode;

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
inline void SmallPath<T>::calculateDijkstra(/*Limit limite,*/ std::string word)
{
	//Algorithme Dijkstra
	//initialisation
	m_layeredGraph.init();
	m_displayNode = std::vector<std::vector<int>> (m_automaton.getStates().size(), std::vector<int>(word.size()));
	int position = m_automaton.getInitialState().getId() - 1;
	std::vector<std::vector<std::pair<Node<T>*, int>>> paireNodeWeight = m_layeredGraph.getLayers();
	std::vector<Node<T>*> V = m_automaton.getStates();
	std::vector<Node<T>*> S;
	std::vector<std::pair<Node<T>*,int>> fileNodes;
	std::vector<Transition<T>*> transitions = m_automaton.getTransitions();
	//std::vector<Occurrence> occurrences = limite.getOccurrences();
	fileNodes.push_back(make_pair(m_automaton.getStates().at(position),0));

	while (!fileNodes.empty()) {
		//Traitement d'un noeud
		std::pair < Node<T>*, int> nodeToRemove;
		int positionWord=0;
		position = fileNodes.front().first->getId();
		int minWeight = INT_MAX;
		for(std::pair<Node<T>*, int> node : fileNodes){
			std::vector<std::pair<Node<T>*, int>> paireToFind = m_layeredGraph.getLayer(node.second);
			if (paireToFind.at(node.first->getId()-1).second <= minWeight) {
				position = node.first->getId() - 1;
				minWeight = paireToFind.at(node.first->getId()-1).second;
				positionWord = node.second;
				nodeToRemove = node;
			}
		}
		Node<T>* currentNode = V.at(position);

		auto it = std::find(fileNodes.begin(), fileNodes.end(), nodeToRemove);
		if (it != fileNodes.end()) {
			fileNodes.erase(it);
			//S.push_back(currentNode);
		}

		//Verification des transitions
		for (unsigned int index = 0; index < currentNode->getTransitions().size(); ++index) {

			Transition<T>* transition = currentNode->getTransitionAt(index);

			if (transition->getValue() == word.at(positionWord)-'0') {

				bool isfinal = false;
				if (positionWord + 1 == word.size()) {

					//Le noeud à la position n pour un mot de taille n+1 doit être final
					auto finalStates = m_automaton.getFinalStates();
					for (auto ite = std::begin(finalStates); ite != std::end(finalStates); ++ite) {
						if (*ite == transition->getDestination()) {
							isfinal = true;
							break;
						}
					}
				}

				if (positionWord + 1 < word.size() || isfinal ) {					
					//int currentMaxOccurence = occurrences.at(transition->getValue() - 1).getMax();
					//if (currentMaxOccurence > 0) {
						relax(currentNode, transition->getDestination(), transition->getWeight(), positionWord+1);
						m_displayNode.at(transition->getDestination()->getId()-1).at(positionWord)=currentNode->getId();


						if (!isfinal) {
							fileNodes.push_back(make_pair(transition->getDestination(), positionWord + 1));
						}
						//occurrences.at(transition->getValue() - 1).setMax(currentMaxOccurence - 1);
					//}
				}
				
			}
		}
	}
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
	if (paireToFind.second > paireCurrent.second + weightTransition) {

		m_layeredGraph.setWeight(positionWord, paireToFind.first->getId()-1, paireCurrent.second + weightTransition);
	}

}

template <typename T>
inline void SmallPath<T>::display(std::string word) {
	int finalId;
	bool isFind = false;
	int max = INT_MAX;
	for (Node<T>* finalNode : m_automaton.getFinalStates()) {
		std::pair<Node<T>*, int> paire = m_layeredGraph.getLayer(word.size()).at(finalNode->getId() - 1);
		if (paire.first != 0) {
			cout << "Noeud : " << *paire.first << ", Poids : " << paire.second << ", Position du mot : " << word.size() << endl;
		}
		if (paire.first != 0 && paire.second < max) {
			max = paire.second;
			finalId = paire.first->getId();
			isFind = true;
			break;
		}
		
	}
	if (isFind) {
		std::vector<int> toDisplay;
		int positionWord = word.size()-1;
		toDisplay.push_back(finalId);
		while (positionWord>=0) {
			finalId = m_displayNode.at(finalId-1).at(positionWord);
			toDisplay.push_back(finalId);
			--positionWord;
		}
		std::cout << "Le chemin est : ";
		for (int i = toDisplay.size()-1 ; i >= 0; --i) {
			std::cout << toDisplay.at(i) << " - ";
		}
		std::cout << "\n";
	}
}

template<typename T>
inline void SmallPath<T>::findBetweenNodes(int first, int second, Limit limite)
{
	//Algorithme Dijkstra
	//initialisation
	m_layeredGraph.init();
	m_displayNode = std::vector<std::vector<int>>(m_automaton.getStates().size(), std::vector<int>(limite.getWordSize()));
	int position = m_automaton.getInitialState().getId() - 1;
	std::vector<std::vector<std::pair<Node<T>*, int>>> paireNodeWeight = m_layeredGraph.getLayers();
	std::vector<Node<T>*> V = m_automaton.getStates();
	std::vector<Node<T>*> S;
	std::vector<std::pair<Node<T>*, int>> fileNodes;
	std::vector<Transition<T>*> transitions = m_automaton.getTransitions();
	std::vector<Occurrence> occurrences = limite.getOccurrences();
	fileNodes.push_back(make_pair(m_automaton.getStates().at(position), 0));
	std::vector<std::vector<int>> path;
	std::vector<std::vector<int>> pathFinded;

	std::vector<int> singlePath;
	singlePath.push_back(m_automaton.getInitialState().getId());
	path.push_back(singlePath);
	for (int i = 0; i < m_automaton.getStates().at(m_automaton.getInitialState().getId()-1)->getTransitions().size(); ++i) {
		Transition<T>* transition = m_automaton.getStates().at(m_automaton.getInitialState().getId() - 1)->getTransitionAt(i);
		std::vector<std::vector<int>> pathToFind;
		pathToFind = recursifParcours(transition->getDestination(), 1, limite.getWordSize(), path);
		std::cout << "Parcours : " << m_automaton.getStates().at(m_automaton.getInitialState().getId() - 1)->getTransitions().size() << endl;

		for (std::vector<int> mulPath : pathToFind) {
			pathFinded.push_back(mulPath);
		}
	}
	std::cout << "Parcours : " << endl;
	for (std::vector<int> mulPath : pathFinded) {
		for (int nodeId : mulPath) {
			std::cout << nodeId << " - ";
		}
		std::cout << "\n";
	}
}

template<typename T>
inline std::vector<std::vector<int>> SmallPath<T>::recursifParcours(Node<T>* node, int positionWord, int wordSize, std::vector<std::vector<int>> path)
{
	std::cout << "positionWord : " << positionWord << endl;

	std::vector < std::vector<int>> pathToReturn;
	for (int i=0; i < path.size(); ++i) {
		path.at(i).push_back(node->getId());
		std::cout << "Node : " << node->getId() << std::endl;
	}
	if (positionWord < wordSize-1) {
		
		for (Transition<T>* transition : node->getTransitions()) {
			std::vector<std::vector<int>> pathToFind;
			pathToFind = recursifParcours(transition->getDestination(), positionWord + 1, wordSize, path);
			for (std::vector<int> mulPath : pathToFind) {
				pathToReturn.push_back(mulPath);
			}
		}
		return pathToReturn;
	}
	return path;
}
