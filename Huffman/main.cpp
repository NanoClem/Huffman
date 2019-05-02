#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <bitset>
#include <map>
#include <vector>
#include <queue>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

#include "Node.hpp"
#include "Huffman.hpp"


/**
 * Affiche les elements contenus dans la queue en
 * commen�ant par le plus petit a chaque fois
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
	Lecture d'un fichier texte ou binaire
	Retourne le contenu du fichier en format string
 */
string readTextFile(string filename)
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


/**
	Lecture d'un fichier binaire octet par octet
	Retourne le contenu du fichier en format string
 */
vector<unsigned char> *readBinaryFile(string filename)
{
	ifstream file(filename.c_str(), ios::binary | ios::in);
	vector<unsigned char> *ret = new vector<unsigned char>();
	char tmp = 0;
	
	if (file)
	{
		while (file) {
			file.get(tmp);
			ret->push_back(static_cast<unsigned char>(tmp));
		}
	}
	else
		cerr << "ERROR : can't open file in reading mode" << endl;

	return ret;
}


/**
	Conversion d'une chaine binaire en octet
 */
unsigned char binaryStringToByte(char *code)
{
	unsigned char res = 0;
	char *c = code;

	while (*c)
	{
		// VERIFICATION : la chaine ne doit contenir que des '0' et des '1'
		if (*c < '0' || *c >'1') {
			cerr << "La chaine ne doit contenir que des '0' ou des '1'" << endl;
			break;
		}
		res <<= 1;		// decalage des bits	

		if (*c == '1')
			res |= 1;

		c++;
	}

	return res;
}


/**
	Convertis un octet en chaine str
*/
string byteToBinaryString(unsigned char _byte)
{
	return bitset<8>(_byte).to_string();
}


/**
	 Prepare les donnes string sous forme hexadecimale
	 La fonction decoupe le message par paquets de huit et les convertis en octet
	 Si le decoupage laisse une chaine de moins de huit caracteres, la comble et renseigne
	 dans "fitOffset" le nombre de bit a combler
 */
vector<unsigned char> *prepareData(string message)
{
	vector<unsigned char> *res = new vector<unsigned char>();
	char *tmpChar = nullptr;
	int tmpSize = 0;
	string tmp = "";

	// SEPARATION OCTET PAR OCTET
	for (size_t i = 0; i < message.length(); i+=8)
	{
		tmp = message.substr(i, 8);
		if (tmp.length() != 8) {							// si le code n'est pas sur 8 bits
			tmpSize = tmp.length() + (8 - tmp.length());	// nombre de cases a remplir
			tmp.resize(tmpSize, '0');						// remplissage avec des '0'
		}
		tmpChar = (char*)tmp.c_str();
		res->push_back(binaryStringToByte(tmpChar));		// conversion en octet
	}

	return res;
}


/**
	Retourne la taille d'un fichier en octets
	#WARNING : tellg() a parfois un comportement al�atoire
*/
long getRealNbBytes(string filename)
{
	ifstream file(filename.c_str(), ios::binary | ios::in);		// ouverture en mode lecture binaire (fonctionne aussi sur les txt)
	file.seekg(0, ios_base::end);								// on se place a la fin du fichier
	int ret = file.tellg();										// recuperer la position (taille du fichier)

	file.seekg(0, ios::beg);
	file.close();

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
			 << "please provide the path of the text to encode and the path of frequences file" << endl;
		return 1;
	}

	// VARIABLES
	Huffman *huffman    = new Huffman();			// objet Huffman
	string encodedFile  = "encoded_text.bin";		// fichier txt des donnees encodees
	string freqFile     = argv[2];					// fichier dat du tableau des frequences
	string HuffcodeFile = "huffcode.dat";			// fichier dat du tableau des codes huffman
	

	// MENU DE SELECTION
	bool repeat = false;
	int select;
	
	do {
		cout << "Choose an option :" << endl
			<< "1. Semi-adptative Encoding"				  << endl
			<< "2. Static Encoding"						  << endl
			<< "3. Decoding binary file"				  << endl
			<< "4. EXIT"								  << endl
			<< endl <<  ">";
		cin >> select;
		cout << endl;

		switch (select) {

			/*======================================================
						ENCODAGE SEMI-ADAPTATIF
			======================================================*/
			case 1: 
			{
				// FICHIERS ET MAP DE DONNEES
				string toEncodeFile = argv[1];					// fichier txt des donnees a encoder
				string content = readTextFile(toEncodeFile);	// contenu non encode du fichier txt des donnees 
				huffman->buildFreqMap(toEncodeFile);			// construction des frequences des caracteres
				huffman->buildHuffmanTree();					// construction de l'arbre de Huffman

				//ENCODAGE DES DONNEES
				huffman->encode(huffman->Root(), "");
				vector<unsigned char> *data = prepareData(huffman->getEncodedData(content));
				huffman->printHuffmanData();

				cout << "NOMBRE D'OCTETS AVANT COMPRESSION : "		<< getRealNbBytes(toEncodeFile) << endl;
				cout << "NOMBRE D'OCTETS REEL APRES COMPRESSION : " << getRealNbBytes(encodedFile)  << endl;	// nb octet apres compression 

				//// ECRITURE DES DONNEES ENCODEES
				huffman->writeDataFreq(freqFile);				// tableau des frequences
				huffman->writeDataHuffman(HuffcodeFile);		// tableau des codes huffman
				huffman->writeEncodedData(encodedFile, data);	// donnees encodees

				cout << endl;
				delete data;
				repeat = true;
				break;
			}


			/*======================================================
						ENCODAGE STATIQUE
			======================================================*/
			case 2:
			{
				// FICHIERS ET MAP DE DONNEES
				string toEncodeFile = argv[1];					// fichier txt des donnees a encoder
				string content = readTextFile(toEncodeFile);	// contenu non encode du fichier txt
				huffman->readDataFreq(freqFile);				// lecture des frequences depuis le fichier des donnees
				huffman->buildHuffmanTree();					// construction de l'arbre de Huffman

				//ENCODAGE DES DONNEES
				huffman->encode(huffman->Root(), "");
				vector<unsigned char> *data = prepareData(huffman->getEncodedData(content));

				//ECRITURE DES DONNEES ENCODEES
				huffman->writeDataHuffman(HuffcodeFile);		// ecritures du tableau des fr�quences et des codes huffman
				huffman->writeEncodedData(encodedFile, data);	// ecriture des donnees encodees

				//RESULTATS
				huffman->printHuffmanData();
				cout << endl;
				cout << "NOMBRE D'OCTETS AVANT COMPRESSION : "		<< getRealNbBytes(toEncodeFile) << endl;
				cout << "NOMBRE D'OCTETS REEL APRES COMPRESSION : " << getRealNbBytes(encodedFile)  << endl;	// nb octet apres compression 

				cout << endl;
				delete data;
				repeat = true;
				break;
			}


			/*======================================================
							DECODAGE
			======================================================*/
			case 3: 
			{
				//LECTURE DES FREQUENCES ET CONSTRUCTION DE L'ARBRE
				huffman->readDataFreq(freqFile);
				huffman->buildHuffmanTree();

				vector<unsigned char> *encodedData = readBinaryFile(encodedFile);
				vector<unsigned char>::iterator it = encodedData->begin();
				string binaryMessage = "";

				while (it != encodedData->end()) {
					binaryMessage += byteToBinaryString(*it);
					it++;
				}

				// DECODAGE
				string decodedMessage = huffman->decode(huffman->Root(), binaryMessage);

				huffman->printHuffmanData();
				cout << endl;

				cout << "DONNEES DECODEES :" << endl
					 << decodedMessage << endl;

				cout << endl;
				delete encodedData;
				repeat = true;
				break;
			}


			/*======================================================
									EXIT
			======================================================*/
			case 4:
				repeat = false;
				break;
					

			/*======================================================
							OPTION INCONUE
			======================================================*/
			default:
				cout << "Unknow option, please enter a valid one" << endl;
				repeat = true;
				break;
		}
	} while (repeat);

	
	delete huffman;
	system("PAUSE");
	return 0;
}