
#ifndef NODE_HPP
#define NODE_HPP

#include <stdio.h>
#include <iostream>

using namespace std;



/**
 * CLASSE NODE
 */
class Node {

  public:
	Node() {}
	~Node() { delete left; delete right; }
    Node * left;
    Node * right;
    char nodeValue;
    int frequence;
    string code;
	inline bool isLeaf() { return (left == nullptr && right == nullptr); }
    inline const char& getValue() const {return nodeValue;}
	inline friend bool operator <(Node const &n1, Node const &n2) { return n1.frequence < n2.frequence; }

    friend class HuffTree;
};


/**
* Operateur de comparaison pour les Noeuds
* Utile pour les traitements de la priority_queue
*/
struct compare {
	bool operator()(Node *l, Node *r) {
		return l->frequence > r->frequence;
	}
};

#endif