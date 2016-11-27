#ifndef LAYEDRED_GRAPH_H
#define LAYEDRED_GRAPH_H

#include <vector>

#include "Automaton.h"

template <typename T>
class LayeredGraph : public Automaton<T>
{

public:
	LayeredGraph(Automaton<T> automaton, int nbLayers);

	std::vector<std::vector<Node<T>*>> getLayers();

	std::vector<Node<T>*> getLayer(int index);

private:

	/** \brief The layers of the LayeredGraph. */
	vector<vector<Node<T>*>> m_layers;

	/** \brief The numbers of layer in the LayeredGraph. */
	int m_nbLayers;

	Node<T>* start;
	Node<T>* final;
};

#endif

template<typename T>
inline LayeredGraph<T>::LayeredGraph(Automaton<T> automaton, int nbLayers)
{
	m_nbLayers(nbLayers);
	

	std::vector<Node<T>*> states = automaton.getStates();
	int nbStates = states.size();
	m_layers = std::vector<std::vector<Node<T>*>>();

	for (int i = 0; i < nbLayers; i++) {
		std::vector<Node<T>*> layer = std::vector<Node<T>*>();
		for (int j = 0; j < nbStates; j++) {
			Node<T>* node = new Node<T>(states.at(j)->getId(), false);

			layer.push_back(node);
		}
		m_layers.push_back(layer);
	}

	for (int j = 0; j < nbStates; j++) {
		for (int i = 0; i < nbLayers - 1; i++) {
			std::vector<Transition<T>*> transitions = states.at(i)->getTransitions();
			for (int j = 0; j < transitions.size(); j++) {
				m_layers.at(i).at(j)->addTransition(m_layers.at(i + 1).at(destId - 1), transitions.at(j)->getValue(), transitions.at(j)->get_weight);
			}		
		}
		start = m_layers.at(0).at(automaton.getInitialState()->getId());

		std::vector<Node<T>*> finalStates = automaton.getFinalStates().size();
		int nbFinal = finalStates.size();

		for (int i = 0; i < nbFinal; i++)
			m_layers.at(nbLayers).at(finalStates.at(i)->getId())->setFinal(true);
}




	std::vector<Vertex<T>*> layer = std::vector<Node<T>*>();
}

template<typename T>
inline std::vector<std::vector<Node<T>*>> LayeredGraph<T>::getLayers()
{
	return m_layers;
}

template<typename T>
inline std::vector<Node<T>*> LayeredGraph<T>::getLayer(int index)
{
	return m_layers[index];
}