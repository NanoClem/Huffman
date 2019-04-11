#include "HuffTree.hpp"


// CONSTRUCTEUR
HuffTree::HuffTree()
	:root(nullptr)
{
	root = new Node();
}

// DESTRUCTEUR
HuffTree::~HuffTree()
{}


// AFFICHER TOUS LES NOEUDS DE L'ARBRE
void HuffTree::Viewing()
{
	if (root != nullptr)
		scan(root);
	else
		cout << "L'arbre est vide" << endl;
}


// AFFICHER LE NOEUD SPECIFIE
void HuffTree::scan(Node *pNode)
{
	if (pNode->left)
		scan(pNode->left);

	if (pNode)
		cout << pNode->nodeValue << " : " << pNode->frequence << endl;

	if (pNode->right)
		scan(pNode->right);
}


// CREER UN NOUVEAU NOEUD
Node* HuffTree::createNode(const char val, const int freq)
{
	Node * pTmpNode = new Node;
	pTmpNode->left = pTmpNode->right = nullptr;

	pTmpNode->nodeValue = val;
	pTmpNode->frequence = freq;

	return pTmpNode;

}
