#ifndef LAYEDRED_GRAPH_H
#define LAYEDRED_GRAPH_H

#include <vector>

#include "Automaton.h"

template <typename T>
class LayeredGraph : public Automaton<T>
{

public:

	LayeredGraph();

	LayeredGraph(Automaton<T> automaton, int nbLayers);

	vector<vector<std::pair<Node<T>*, int>>> getLayers();

	vector<std::pair<Node<T>*, int>> getLayer(int index);

	void init();

	void setWeight(int positionLayer, int positionState, int weight);

private:

	/** \brief The layers of the LayeredGraph. */
	vector<vector<std::pair<Node<T>*, int>>> m_layers;

	/** \brief The numbers of layer in the LayeredGraph. */
	int m_nbLayers;

	std::pair<Node<T>*, int> start;
};


template<typename T>
inline LayeredGraph<T>::LayeredGraph()
{
}

template<typename T>
inline LayeredGraph<T>::LayeredGraph(Automaton<T> automaton, int nbLayers)
{
	m_nbLayers = nbLayers;


	std::vector<Node<T>*> states = automaton.getStates();
	int nbStates = states.size();
	m_layers = std::vector<std::vector<std::pair<Node<T>*, int>>>();

	for (int i = 0; i < nbLayers; i++) {
		std::vector< std::pair<Node<T>*, int >> layer = std::vector<std::pair<Node<T>*, int>>();
		for (int j = 0; j < nbStates; j++) {
			Node<T>* node = new Node<T>(states.at(j)->getId(), false);

			layer.push_back(make_pair(node, INT32_MAX));
		}
		m_layers.push_back(layer);
	}
	for (int i = 0; i < nbLayers - 1; i++) {
		for (int j = 0; j < nbStates; j++) {
			std::vector<Transition<T>*> transitions = states.at(j)->getTransitions();
			for (int t = 0; t < transitions.size(); t++) {
				m_layers.at(i).at(j).first->addTransition(m_layers.at(i + 1).at(transitions.at(t)->getDestination()->getId() - 1).first, transitions.at(t)->getValue(), transitions.at(t)->getWeight());
			}
		}

		
	}
	start = m_layers.at(0).at(automaton.getInitialState().getId() - 1);
	start.second = 0;
	m_layers.at(0).at(automaton.getInitialState().getId() - 1).second = 0;
}

	

	template<typename T>
inline std::vector<std::vector<std::pair<Node<T>*, int>>> LayeredGraph<T>::getLayers()
{
	return m_layers;
}

template<typename T>
inline std::vector<std::pair<Node<T>*, int>> LayeredGraph<T>::getLayer(int index)
{
	return m_layers[index];
}

template<typename T>
inline void LayeredGraph<T>::init()
{
	for (int i = 0; i < m_nbLayers; i++) {
		for (int j = 0; j < m_layers.at(i).size(); j++) {
			m_layers.at(i).at(j).second = INT_MAX;
		}
	}
	m_layers.at(0).at(start.first->getId() - 1).second = 0;
}

template<typename T>
inline void LayeredGraph<T>::setWeight(int positionLayer, int positionState, int weight)
{
	m_layers.at(positionLayer).at(positionState).second = weight;
}
#endif
