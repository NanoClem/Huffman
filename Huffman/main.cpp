#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <bitset>
#include <map>
#include <queue>
#include <vector>
using namespace std;

#include "Node.hpp"
#include "Huffman.hpp"



/**
 * Affiche les paires cle/valeur de la map des frequences.
 * Pour chaque element, on affiche donc le charactere et sa frequence
 */
void printMap(map<char, int> *mymap)
{
	cout << "MAP DES FREQUENCES \n";
	for (auto& x : *mymap)
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
	Lecture d'un fichier	
	Retourne le contenu du fichier 
 */
string readFile(string filename)
{
	ifstream file(filename.c_str(), ios::in);
	string ret, tmp = "";
	if (file)
	{
		while (getline(file, tmp)) 
		{
			if (file.good())
				ret += '\n';
			ret += tmp;
		}
		file.close();
	}
	else
		cerr << "ERROR : can't open file in reading mode" << endl;
	return ret;
}



/*========================================================
	MAIN
========================================================*/
int main(int argc, char** argv)
{
	// VERIFIER LES ARGUMENTS EN ENTREE
	if (argc != 3) {
		cout << "ERROR  : missing arguments" << endl
			 << "please provide the path of the text to encode and the path of the text to decode" << endl;
		return 1;
	}

	// VARIABLES
	Huffman *huffman    = new Huffman();			// objet Huffman
	string encodedFile  = argv[2];					// fichier txt des donnees encodees
	string freqFile     = "frequences.dat";			// fichier dat du tableau des frequences
	string HuffcodeFile = "huffcode.dat";			// fichier dat du tableau des codes huffman
	

	// MENU DE SELECTION
	bool repeat = false;
	int select;
	
	do {
		cout << "Choose an option :" << endl
			<< "1. Semi-adptative Encoding"				  << endl
			<< "2. Decoding binary file"				  << endl
			<< "3. Type a word and print its binary code" << endl
			<< ">";
		cin >> select;
		cout << endl;

		switch (select) {

			/*======================================================
							ENCODAGE
			======================================================*/
			case 1: 
			{
				// FICHIERS ET MAP DE DONNEES
				string toEncodeFile = argv[1];				// fichier txt des donnees a encoder
				string content = readFile(toEncodeFile);	// contenu non encode du fichier txt des donnees 
				huffman->buildFreqMap(toEncodeFile);		// construction des frequences des caracteres
				huffman->buildHuffmanTree();				// construction de l'arbre de Huffman

				//ENCODAGE DES DONNEES
				huffman->encode(huffman->Root(), "");
				huffman->binStringtoBinary(huffman->getEncodedData(content));
				//huffman->printHuffmanData();

				// ECRITURE DES DONNEES ENCODEES
				//huffman->writeDataFreq(freqFile);											// tableau des frequences
				//huffman->writeDataHuffman(HuffcodeFile);									// tableau des codes huffman
				//huffman->writeEncodedData(encodedFile, huffman->getEncodedData(content));	// donnees encodees

				cout << endl;
				break;
			}


			/*======================================================
							DECODAGE
			======================================================*/
			case 2: 
			{
				// LECTURE DES FREQUENCES ET CONSTRUCTION DE L'ARBRE
				huffman->readDataFreq(freqFile);
				huffman->buildHuffmanTree();

				// DECODAGE
				string decodedMessage = huffman->decode(huffman->Root(), readFile(encodedFile));
				huffman->printHuffmanData();

				cout << endl;

				cout << "DONNEES DECODEES :" << endl
					 << decodedMessage << endl;

				cout << endl;
				break;
			}


			/*======================================================
						CONVERTIR UNE SAISIE EN BINAIRE
			======================================================*/
			case 3: 
			{
				string text;
				cout << "Type your text to cast : ";
				cin >> text;

				for (size_t i = 0; i < text.size(); i++)
					cout << bitset<8>(text.c_str()[i]) << endl;

				cout << endl;
				break;
			}
					

			/*======================================================
							OPTION INCONUE
			======================================================*/
			default:
				cout << "Unknow option, please enter a valid one" << endl;
				repeat = true;
		}
	} while (repeat);

	
	delete huffman;
	system("PAUSE");
	return 0;
}