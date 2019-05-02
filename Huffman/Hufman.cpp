#include "Huffman.hpp"
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <queue>
#include <bitset>
#include <iomanip>


/**
 * CONSTRUCTEUR DE CLASSE Huffman
 */
Huffman::Huffman()
	:root(nullptr)
{
	root     = new Node();
	charFreq = new map<char, int>();
}


/**
 * DESTRUCTEUR DE CLASSE Huffman
 */
Huffman::~Huffman()
{
	charFreq->clear();
	delete charFreq;
	delete root;
}


/**
 * Afficher tous les noeuds de l'arbre
 */
void Huffman::Viewing()
{
	if (root != nullptr)
		scan(root);
	else
		cout << "L'arbre est vide" << endl;
}


/**
 * Parcours en profondeur des noeuds
 */
void Huffman::scan(Node *pNode)
{
	if (pNode->left)
		scan(pNode->left);

	if (pNode)
		cout << pNode->nodeValue << " : " << pNode->frequence << endl;

	if (pNode->right)
		scan(pNode->right);
}


/**
 * Creation d'un nouveau noeud
 */
Node* Huffman::createNode(const char val, const int freq)
{
	Node * pTmpNode = new Node;
	pTmpNode->left = pTmpNode->right = nullptr;

	pTmpNode->nodeValue = val;
	pTmpNode->frequence = freq;

	return pTmpNode;
}


/**
 * Construit la map des frequences des characteres
 * du fichier texte en entree.
 */
void Huffman::buildFreqMap(string filename)
{
	ifstream file(filename.c_str(), ios::in);				       // ouverture en mode lecture
	if (file) {												       // si il n'y a pas d'erreur de flags
		char c;
		while (file.good())									       // Tant qu'on est pas à la fin du fichier
		{
			file.get(c);									       // on lit caractere par caractere
			pair<char, int> word(c, 1);							   // nouvelle paire clé/valeur (freq initialisee a 1)
			map<char, int>::iterator search = charFreq->find(c);   // on place un itérateur au caractere (place a la fin s'il n'est pas trouve)

			if (search == charFreq->end())						   // si on a atteint la fin de map (char non existant)
				charFreq->insert(word);							   // on insere la nouvelle donnee
			else
				search->second += 1;							   // s'il est deja dans la map, on incremente sa frequence
		}
		file.close();
	}
	else
		cerr << "ERROR : can't open file in reading mode" << endl;
}



/**
* Construit l'arbre de Huffman.
*/
void Huffman::buildHuffmanTree()
{
	Node *left, *right, *father;								// noeuds temporaires pour la construction de l'arbre
	priority_queue<Node*, vector<Node*>, compare> minHeap;		// Tas minimum des noeuds 
	map<char, int>::iterator it = charFreq->begin();				    // Iterateur de la map des frequences

	// INSERTION DES NOEUDS DANS LE TAS
	while (it != charFreq->end()) {
		minHeap.push(createNode(it->first, it->second));
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
		father = createNode('$', left->frequence + right->frequence);	// Le caratere '$' indique un noeud intermediaire 
		father->left = left;
		father->right = right;
		minHeap.push(father);
	}

	// RACINE DE L'ARBRE
	setRoot(minHeap.top());		// Il ne reste que le noeud racine dans la queue apres l'algo
}


/**
  Encodage Huffman de chaque caractere 
  issu des noeuds de l'arbre
  */
void Huffman::encode(Node *root, string _code) 
{
	if (!root)
		return;

	if (root->isLeaf()) {									// Si on est sur une feuille
		pair<char, string> leaf(root->nodeValue, _code);	// Paire cle/valeur pour insertion
		huffmanCode.insert(leaf);							// Insertion dans la map des codes Huffman
		root->code = _code;									// Affectation du code a l'attribut du noeud
	}
	encode(root->left, _code + '0');						// Conversion des codes en binaire
	encode(root->right, _code + '1');
}


/**
	Decodage du fichier precedemment compresse par
	methode de Huffman.
*/
string Huffman::decode(Node *root, string code)
{
	string ret, tmp = "";
	Node *current   = root;

	// PARCOURS EN PROFONDEUR DE L'ARBRE
	for (size_t i = 0; i < code.size(); i++) 
	{
		if (code[i] == '0') {
			tmp += '0';
			current = current->left;
		}
		else {
			tmp += '1';
			current = current->right;
		}
			
		// FEUILLE TROUVEE
		if(current->isLeaf())
		{
			ret += current->nodeValue;
			current->code = tmp;
			pair<char, string> leaf(current->nodeValue, tmp);
			huffmanCode.insert(leaf);
			tmp = '\0';
			current = root;
		}
	}
	return ret + '\0';
}


/**
	Retourne les donnees encode selon
	la methode de Huffman
*/
string Huffman::getEncodedData(string message)
{
	string encodedData = "";
	for (auto i : message)
		encodedData += huffmanCode[i];
		
	return encodedData;
}


/**
	Retourne la taille du fichier en bits
	apres encodage de Huffman
 */
int Huffman::getNbBytes() const
{
	return 0;
}


/**
	Affichage des differentes frequences associes 
	aux caracteres
 */
void Huffman::printCharFrequences() const
{
	cout << "TABLEAU DES FREQUENCES" << endl;
	for (auto& it : *charFreq)
		cout << it.first << " : " << it.second << endl;
	cout << "FIN AFFICHAGE" << endl;
}


/**
 * Affichage des differents codes associes aux feuilles
 * de l'arbre de Huffman
 */
void Huffman::printHuffmanCode() const
{
	cout << "TABLEAU DES CODES HUFFMAN" << endl;
	for (auto& it : huffmanCode)
		cout << it.first << " : " << it.second << endl;
	cout << "FIN AFFICHAGE" << endl;
}


/**
	Affichage des donnees de chaque caractere
	(frequences et code huffman)
 */
void Huffman::printHuffmanData()
{
	map<char, string>::iterator itCode = huffmanCode.begin();
	map<char, int>::iterator itFreq    = charFreq->begin();

	cout << "DONNEES HUFFMAN" << endl;
	cout << "CHAR" << "      " << "FREQ" << "      " << "CODE" << endl;
	while (itFreq != charFreq->end()) {
		cout << itFreq->first << "        " << itFreq->second << "        " << itCode->second << endl;
		itFreq++;
		itCode++;
	}
		
	cout << "FIN AFFICHAGE" << endl;
}


/**
	Lecture des donnees associees aux frequences
	des caracteres dans la map
 */
void Huffman::readDataFreq(string filename)
{
	int size, freq;
	char charT;
	string line;
	ifstream file(filename.c_str(), ios::binary);

	if (file)
	{
		charFreq->clear();			// vider la map des frequences
		getline(file, line);		// on recupere la premiere ligne contenant le nombre de char
		size  = stoi(line);			// nombre de char ou taille de la map

	 	while (getline(file, line))					// le curseur est donc place apres la premiere ligne
		{
			charT = line[0];						// caractere

			// CAS DU LINE FEED
			if (int(charT) == 10 || int(charT) == 13) {		// si LF ou CRLF (selon l'OS)
				charT = char(10);							// le char est ramene egal a LF (ascii 10)
				getline(file, line);						// on passe a la ligne suivante, contenant la freq du lf
				freq = stoi(line.substr(1));				// freq du lf, se trouvant apres le premier char de la ligne
			}
			// CAS NORMAL
			else
				freq = stoi(line.substr(2));				// frequence du caractere, se trouvant apres le deuxieme char de la ligne

			pair<char, int> data(charT, freq);				// paire cle/valeur pour insertion
			charFreq->insert(data);							// insertion des donnees
		}
	}
	else
		cerr << "ERROR : can't open file in reading mode" << endl;
}


/**
	Ecrit dans un fichier les donnees relatives
	aux frequences des caracteres
 */
void Huffman::writeDataFreq(string filename)
{
	ofstream file(filename.c_str(), ios::out | ios::trunc);		// ouverture en mode ecriture, ecrase le contenu a chaque ouverture si le fichier existe
	if (file)
	{
		file << charFreq->size() << endl;						// ecriture du nombre total de caracteres

		map<char, int>::iterator it = charFreq->begin();
		while (it != charFreq->end()) 
		{
			file << it->first << " " << it->second << endl;	    // ecriture des caracteres et de leur frequence
			it++;
		}
		file.close();
	}
	else
		cerr << "ERROR : can't open file in writing mode" << endl;
}


/**
	Ecrit dans un fichier le tableau des codes
	huffman des caracteres
 */
void Huffman::writeDataHuffman(string filename)
{
	ofstream file(filename.c_str(), ios::out | ios::trunc);		// ouverture en mode ecriture, ecrase le contenu a chaque ouverture si le fichier existe
	if (file)
	{
		map<char, string>::iterator it = huffmanCode.begin();
		while (it != huffmanCode.end()) {
			file << it->first << " " << it->second << endl;	    // ecriture des caracteres et de leur frequence
			it++;
		}
		file.close();
	}
	else
		cerr << "ERROR : can't open file in writing mode" << endl;
}


/**
	Ecrit dans un fichier binaire les donnes encodees
 */
void Huffman::writeEncodedData(string filename, vector<int> *hexCode)
{
	ofstream file(filename.c_str(), ios::binary | ios::out);

	if (file) {
		file.write((char*)&hexCode[0], hexCode->size()*sizeof(int));
		file.close();
	}
	else
		cerr << "ERROR : can't open file in writing mode" << endl;
}