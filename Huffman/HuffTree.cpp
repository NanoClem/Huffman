#include "HuffTree.hpp"


/**
 * CONSTRUCTEUR DE CLASSE HuffTree
 */
HuffTree::HuffTree()
	:root(nullptr)
{
	root = new Node();
}

/**
 * DESTRUCTEUR DE CLASSE HuffTree
 */
HuffTree::~HuffTree()
{}


/**
 * Afficher tous les noeuds de l'arbre
 */
void HuffTree::Viewing()
{
	if (root != nullptr)
		scan(root);
	else
		cout << "L'arbre est vide" << endl;
}


/**
 * Afficher un noeud
 */
void HuffTree::scan(Node *pNode)
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
Node* HuffTree::createNode(const char val, const int freq)
{
	Node * pTmpNode = new Node;
	pTmpNode->left = pTmpNode->right = nullptr;

	pTmpNode->nodeValue = val;
	pTmpNode->frequence = freq;

	return pTmpNode;
}


/**
* Construit l'arbre de Huffman.
*/
void HuffTree::buildHuffmanTree(map<char, int> fMap)
{
	Node *left, *right, *father;								// noeuds temporaires pour la construction de l'arbre
	priority_queue<Node*, vector<Node*>, compare> minHeap;		// Tas minimum des noeuds 
	map<char, int>::iterator it = fMap.begin();				    // Iterateur de la map des frequences

	// INSERTION DES NOEUDS DANS LE TAS
	while (it != fMap.end()) {
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
		father = createNode('$', left->frequence + right->frequence);
		father->left = left;
		father->right = right;
		minHeap.push(father);
	}

	// RACINE DE L'ARBRE
	setRoot(minHeap.top());		// Il ne reste que le noeud racine dans la queue apres l'algo
}
