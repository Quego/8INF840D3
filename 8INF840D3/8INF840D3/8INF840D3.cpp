// 8INF840D3.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "AutomatonPlus.cpp"

using namespace std;

void help()
{
	cout << "----------Les commandes possibles sont les suivantes ----------" << endl;
	cout << "- help, ? : affiche la liste des commandes" << endl;
	cout << "- graphe : afficher à l'ecran les noeuds" << endl;
	cout << "- fichier : ecrit les noeuds dans un fichier" << endl;
	cout << "- plus court chemin : calculer le plus court chemin" << endl;
	cout << "- afficher : afficher les plus courts chemins" << endl;
	cout << "- ecrire : ecrire dans un fichier" << endl;
	cout << "- recherche : recherche arrete" << endl;
	cout << "- quitter : quitter le programme" << endl;
}

//afficher à l'ecran les noeuds
template <typename T>
void displayGraphe(AutomatonPlus<T> myAutomatonPlus) {

	cout << myAutomatonPlus;

	
}

//ecrit les noeuds dans un fichier
void fichier() {

}

//calculer le plus court chemin
void pcc() {

}

// afficher les plus courts chemins
void display() {

}

//ecrire dans un fichier
void write() {

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
	cin >> transitionFile;
	cout << "Entrez le nom du fichier contenant les contraintes :" << endl;
	//cin >> constraintFile;
	Automaton<int> myAutomaton = Automaton<int>::Parse("test8.afdC"/*transitionFile*/);
	AutomatonPlus<int> myAutomatonPlus = AutomatonPlus<int>::Parse(/*constraintFile*/"test8_limite.afdC", myAutomaton);

	help();
	while (commande != "quitter") {
		
		cin >> commande;

		if (commande == "help" || commande=="?")
		{
			help();
		}
		else if (commande == "graphe")
		{
			displayGraphe(myAutomatonPlus);
		}
		else if (commande == "fichier")
		{
			fichier();
		}
		else if (commande == "plus court chemin") {
			pcc();
		}
		else if (commande == "afficher") {
			display();
		}
		else if (commande == "ecrire") {
			write();
		}
		else if (commande == "recherche") {
			search();
		}
	}	
	EXIT_SUCCESS;
}

