
#include <stdio.h>
#include <iostream>
#include <map>
#include <queue>

using namespace std;
#include "Node.hpp"


class HuffTree {

	private:
		Node *root;
		void scan(Node *);

	public:
	    HuffTree();
		~HuffTree();
		Node* createNode(const char, const int);
		void buildHuffmanTree(map<char, int> fMap);
		void Viewing();
		inline Node *Root() const { return root; }
		inline void setRoot(Node *n) { root = n; }
};