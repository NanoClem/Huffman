#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

#include "Node.hpp"
#include "HuffTree.hpp"



/**
 * Affiche les paires cle/valeur de la map des frequences.
 * Pour chaque element, on affiche donc le charactere et sa frequence
 */
void printMap(map<char, int> mymap)
{
	cout << "DEBUT AFFICHAGE \n";
	for (auto& x : mymap)
		cout << x.first << " : " << x.second << endl;
	cout << "FIN AFFICHAGE \n";
}


/**
 * Affiche les elements contenus dans la queue en
 * commençant par le plus petit a chaque fois
 */
template<typename T> void printQueue(T& q)
{
	while (!q.empty()) {
		cout << q.top()->frequence << " ";
		q.pop();
	}
	cout << "\n";
}


/**
 * Construit la map des frequences des characteres du tete en entree.
 */
void buildFreqMap(map<char,int>& book, string filename)
{
	ifstream file(filename);

	if (file) {                 // si il n'y a pas d'erreur de flags
		char c;
		while (file.good())									   // Tant qu'on est pas à la fin du fichier
		{
			file.get(c);									   // on lit caractere par caractere
			pair<char, int> word(c, 1);						   // paire clé/valeur
			map<char, int>::iterator search = book.find(c);	   // itérateur pour rechercher le mot passe en paramètre

			if (search == book.end())
				book.insert(word);
			else
				search->second += 1;
		}
	}
	else
		cerr << "ERROR : can't open file in reading mode \n";
}




/*========================================================
	MAIN
========================================================*/
int main(int argc, char** argv)
{
	// VERIFIER LES ARGUMENTS EN ENTREE
	if (argc != 2) {
		cout << "Argument manquant";
		return 0;
	}
	
	// MAP DES FREQUENCES
	map<char,int> freqMap;
	buildFreqMap(freqMap, argv[1]);
	//printMap(freqMap);

	// CONSTRUCTION DE L'ARBRE D'HUFFMAN
	HuffTree *huffman = new HuffTree();
	huffman->buildHuffmanTree(freqMap);
	huffman->Viewing();

	delete huffman;
	system("PAUSE");
	return 0;
}
