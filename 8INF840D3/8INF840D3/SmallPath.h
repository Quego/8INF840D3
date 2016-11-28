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

	void calculateDijkstra(std::string word);

	void relax(Node<T>* currentNode, Node<T>* destinationNode, int weightTransition, int positionWord);

	void display(std::string word);

	void findBetweenNodes(int first, int second, Limit limit);

	void verify(std::vector<std::pair<std::vector<int>, int>> pathFinded, int first, int second, Limit limit);


	std::vector<std::pair<std::vector<int>, int>> recursifParcours(Node<T>* node, int positionWord, int wordSize, int weight, std::vector<std::pair<std::vector<int>, int>> path);

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
inline void SmallPath<T>::calculateDijkstra(std::string word)
{
	//Algorithme Dijkstra
	//initialisation
	m_layeredGraph.init();
	m_displayNode = std::vector<std::vector<int>> (m_automaton.getStates().size(), std::vector<int>(word.size()));
	int position = m_automaton.getInitialState().getId() - 1;
	std::vector<std::vector<std::pair<Node<T>*, int>>> paireNodeWeight = m_layeredGraph.getLayers();
	std::vector<Node<T>*> V = m_automaton.getStates();
	std::vector<std::pair<Node<T>*,int>> fileNodes;
	std::vector<Transition<T>*> transitions = m_automaton.getTransitions();
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
						relax(currentNode, transition->getDestination(), transition->getWeight(), positionWord+1);
						m_displayNode.at(transition->getDestination()->getId()-1).at(positionWord)=currentNode->getId();


						if (!isfinal) {
							fileNodes.push_back(make_pair(transition->getDestination(), positionWord + 1));
						}
				}
				
			}
		}
	}
	// calcul du plus court chemin selon le résultat du noeud final
	int max = INT_MAX;
	bool isFind = false;

	for (Node<T>* finalNode : m_automaton.getFinalStates()) {
		std::pair<Node<T>*, int> paire = m_layeredGraph.getLayer(word.size()).at(finalNode->getId() - 1);
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
	//initialisation
	m_displayNode = std::vector<std::vector<int>>(m_automaton.getStates().size(), std::vector<int>(limite.getWordSize()));
	int position = m_automaton.getInitialState().getId() - 1;
	std::vector<std::vector<std::pair<Node<T>*, int>>> paireNodeWeight = m_layeredGraph.getLayers();
	std::vector<std::pair<std::vector<int>,int>> path;
	std::vector<std::pair<std::vector<int>, int>> pathFinded;

	std::vector<int> singlePath;
	singlePath.push_back(m_automaton.getInitialState().getId());
	path.push_back(make_pair(singlePath,0));
	for (int i = 0; i < m_automaton.getStates().at(position)->getTransitions().size(); ++i) {
		Transition<T>* transition = m_automaton.getStates().at(position)->getTransitionAt(i);
		std::vector<std::pair<std::vector<int>, int>> pathToFind;
		pathToFind = recursifParcours(transition->getDestination(), 1, limite.getWordSize(), transition->getWeight(), path);
		for (std::pair<std::vector<int>, int> mulPath : pathToFind) {
			pathFinded.push_back(mulPath);
		}
	}
	verify(pathFinded, first, second, limite);
	
}

template<typename T>
inline void SmallPath<T>::verify(std::vector<std::pair<std::vector<int>, int>> pathFinded, int first, int second, Limit limit)
{
	std::vector<std::pair<std::vector<int>, int>> truePath;
	std::vector<std::pair<std::vector<int>, int>> reallyTruePath;

	//Verification de la presence de l'arete
	for (std::pair<std::vector<int>, int> mulPath : pathFinded) {
		for (int i = 0; i < mulPath.first.size() - 1; ++i) {
			if (mulPath.first.at(i) == first && mulPath.first.at(i + 1) == second) {
				truePath.push_back(mulPath);
				break;
			}
		}
	}

	//Verification des contraintes sur le chemin
	for (std::pair<std::vector<int>, int> mulPath : truePath) {
		std::vector<Occurrence> occurrences = limit.getOccurrences();
		for (int i = 0; i < mulPath.first.size() - 1; ++i) {
			Transition<T>* transition = m_automaton.getStates().at(mulPath.first.at(i) - 1)->getTransition(mulPath.first.at(i), mulPath.first.at(i + 1));
			occurrences.at(transition->getValue() - 1).setMin(occurrences.at(transition->getValue() - 1).getMin() - 1);
			occurrences.at(transition->getValue() - 1).setMax(occurrences.at(transition->getValue() - 1).getMax() - 1);
		}
		bool isAlphabetValide = true;
		for (int layer = 0; layer < limit.getAlphabetSize(); ++layer) {
			if (occurrences.at(layer).getMin() > 0 || occurrences.at(layer).getMax() < 0) {
				isAlphabetValide = false;
				break;
			}
		}
		if (isAlphabetValide) {
			reallyTruePath.push_back(mulPath);
		}
	}

	if (!reallyTruePath.empty()) {
		std::cout << "Parcours : " << std::endl;
		for (std::pair<std::vector<int>, int> mulPath : reallyTruePath) {
			for (int nodeId : mulPath.first) {
				std::cout << nodeId << " - ";
			}
			std::cout << "Poids : " << mulPath.second << std::endl;
		}
	}
	else {
		std::cout << "Le chemin n'est pas trouve" << std::endl;
	}
}

template<typename T>
inline std::vector<std::pair<std::vector<int>, int>> SmallPath<T>::recursifParcours(Node<T>* node, int positionWord, int wordSize, int weight, std::vector<std::pair<std::vector<int>, int>> path)
{

	std::vector<std::pair<std::vector<int>, int>> pathToReturn;
	for (int i=0; i < path.size(); ++i) {
		path.at(i).first.push_back(node->getId());
		path.at(i).second += weight;
	}
	if (positionWord < wordSize) {
		
		for (Transition<T>* transition : node->getTransitions()) {
			std::vector<std::pair<std::vector<int>, int>> pathToFind;
			pathToFind = recursifParcours(transition->getDestination(), positionWord + 1, wordSize, transition->getWeight(), path);
			for (std::pair<std::vector<int>, int> mulPath : pathToFind) {
				pathToReturn.push_back(mulPath);
			}
		}
		return pathToReturn;
	}
	return path;
}
