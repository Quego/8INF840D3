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
};

#endif