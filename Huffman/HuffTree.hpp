
#include <stdio.h>
#include <iostream>

using namespace std;
#include "Node.hpp"



class HuffTree {

	private:
		Node *root;
		//void insert(Node *);
		void scan(Node *);
		//Node *Search(const char) const;

	public:
	    HuffTree();
		~HuffTree();
		Node* createNode(const char, const int);
		//void Delete(const char);
		void Viewing();
		inline Node *Root() const { return root; }
		inline void setRoot(Node *n) { root = n; }
};