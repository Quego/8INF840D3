// 8INF840D3.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "LayeredGraph.h"
#include "Limit.h"
#include "SmallPath.h"

using namespace std;

void help()
{
	cout << "----------Les commandes possibles sont les suivantes ----------" << endl;
	cout << "- help, ? : affiche la liste des commandes" << endl;
	cout << "- graphe : afficher à l'ecran les noeuds" << endl;
	cout << "- pcc : calculer le plus court chemin" << endl;
	cout << "- afficher : afficher les plus courts chemins" << endl;
	cout << "- recherche : recherche arrete" << endl;
	cout << "- quitter : quitter le programme" << endl;
}

//afficher à l'ecran les noeuds
template <typename T>
void displayGraphe(Automaton<T> myAutomaton) {

	cout << myAutomaton;

	
}

//calculer le plus court chemin
template <typename T>
void pcc(Automaton<T> myAutomaton, Limit limite, SmallPath<T> smPath) {
		std::string word;
		cout << "Entrez un mot de taille " << limite.getWordSize() << " et dont l'alphabet ne depasse pas "<< limite.getAlphabetSize() << " : ";
		cin >> word;
		bool isAlphabetValide = true;
		std::vector<Occurrence> occurrences = limite.getOccurrences();
		for (char letter : word) {
			if (letter - '0' > limite.getAlphabetSize()) {
				isAlphabetValide = false;
				break;
			}
			else {
				occurrences[letter - '0' - 1].setMin(occurrences[letter - '0' - 1].getMin()-1);
				occurrences[letter - '0' - 1].setMax(occurrences[letter - '0' - 1].getMax()-1);
			}
		}
		if (limite.getWordSize() == word.size() && isAlphabetValide) {
			for (int layer = 0; layer < limite.getAlphabetSize(); ++layer) {
				if (occurrences[layer].getMin() > 0 || occurrences[layer].getMax() < 0) {
					isAlphabetValide = false;
					cout << "le nombre d'occurences de la lettre : " << layer+1 << " ne correspond pas aux limites attendues" << endl;
					break;
				}
			}
			if (isAlphabetValide) {
				smPath.calculateDijkstra(/*limite,*/ word);
			}
		}
		else {
			cout << "le mot entre ne correspond pas aux contraintes imposees" << endl;
		}
	
}



// afficher les plus courts chemins
template <typename T>
void display(Automaton<T> myAutomaton, Limit limite, SmallPath<T> smPath) {
	std::string word;
	cout << "Entrez un mot de taille " << limite.getWordSize() << " et dont l'alphabet ne depasse pas " << limite.getAlphabetSize() << " : ";
	cin >> word;
	bool isAlphabetValide = true;
	std::vector<Occurrence> occurrences = limite.getOccurrences();
	for (char letter : word) {
		if (letter - '0' > limite.getAlphabetSize()) {
			isAlphabetValide = false;
			break;
		}
		else {
			occurrences[letter - '0' - 1].setMin(occurrences[letter - '0' - 1].getMin() - 1);
			occurrences[letter - '0' - 1].setMax(occurrences[letter - '0' - 1].getMax() - 1);
		}
	}
	if (limite.getWordSize() == word.size() && isAlphabetValide) {
		for (int layer = 0; layer < limite.getAlphabetSize(); ++layer) {
			if (occurrences[layer].getMin() > 0 || occurrences[layer].getMax() < 0) {
				isAlphabetValide = false;
				cout << "le nombre d'occurences de la lettre : " << layer + 1 << " ne correspond pas aux limites attendues" << endl;
				break;
			}
		}
		if (isAlphabetValide) {
			smPath.calculateDijkstra(/*limite,*/ word);
			smPath.display(word);
		}
	}
	else {
		cout << "le mot entre ne correspond pas aux contraintes imposees" << endl;
	}
}


//recherche arrete
void search() {

}


int main()
{

	string transitionFile;
	string constraintFile;
	string commande;
	cout << "\tPlus court chemin avec contraintes pour graphe par couche" << endl;
	cout << "Entrez le nom du fichier contenant les transitions :" << endl;
	//cin >> transitionFile;
	cout << "Entrez le nom du fichier contenant les contraintes :" << endl;
	//cin >> constraintFile;
	Automaton<int> myAutomaton = Automaton<int>::Parse("test11.afdC"/*transitionFile*/);
	Limit limite = Limit::Parse(/*constraintFile*/"test11limite.afdC");
	LayeredGraph<int> myLayeredGraph = LayeredGraph<int>(myAutomaton, limite.getWordSize() + 1);
	SmallPath<int> smPath(myAutomaton, myLayeredGraph);
	help();
	while (commande != "quitter") {
		
		cin >> commande;

		if (commande == "help" || commande=="?")
		{
			help();
		}
		else if (commande == "graphe")
		{
			displayGraphe(myAutomaton);
		}
		else if (commande == "pcc") {
			pcc(myAutomaton, limite, smPath);
		}
		else if (commande == "afficher") {
			display(myAutomaton, limite, smPath);
		}
		else if (commande == "recherche") {
			search();
		}
	}	
	EXIT_SUCCESS;
}

