#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

#include "Node.hpp"
#include "HuffTree.hpp"


/**
 * Operateur de comparaison pour les Noeuds
 */
struct compare {
	bool operator()(Node *l, Node *r) {
		return l->frequence > r->frequence;
	}
};


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


/**
 * Construit l'arbre de Huffman.
 */
void buildHuffmanTree(HuffTree *ht, map<char,int> fMap) 
{
	Node *left, *right, *father;								// noeuds temporaires pour la construction de l'arbre
	priority_queue<Node*, vector<Node*>, compare> minHeap;		// Tas minimum des noeuds 
	map<char, int>::iterator it = fMap.begin();				    // Iterateur de la map des frequences

	// INSERTION DES NOEUDS DANS LE TAS
	while (it != fMap.end()) {
		minHeap.push(ht->createNode(it->first, it->second));
		it++;
	}

	// CONSTRUCTION
	while (minHeap.size() != 1) {

		// extraction des deux noeuds de frequences les plus basses
		left = minHeap.top();
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();

		// Nouveau noeud pere des deux precedents
		father = ht->createNode('$', left->frequence + right->frequence);
		father->left  = left;
		father->right = right;
		minHeap.push(father);
	}
		
	// RACINE DE L'ARBRE
	ht->setRoot(minHeap.top());		// Il ne reste que le noeud racine dans la queue apres l'algo
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
	printMap(freqMap);

	// CONSTRUCTION DE L'ARBRE D'HUFFMAN
	HuffTree *huffman = new HuffTree();
	buildHuffmanTree(huffman, freqMap);
	huffman->Viewing();

	delete huffman;
	system("pause");
	return 0;
}
