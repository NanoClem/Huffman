#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP


#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <map>
#include <vector>

using namespace std;
#include "Node.hpp"


class Huffman {

private:
	Node *root;
	map<char, int> *charFreq;
	map<char, string> huffmanCode;
	void scan(Node *);

public:
	Huffman();
	~Huffman();
	Node* createNode(const char, const int);
	void Viewing();
	void buildFreqMap(string filename);
	void buildHuffmanTree();
	void encode(Node *root, string code);
	string decode(Node *root, string code);

	// AFFICHAGE
	void printCharFrequences() const;
	void printHuffmanCode() const;
	void printHuffmanData();

	// LECTURE DES DONNEES
	void readDataFreq(string filename);

	// ECRITURE DES DONNEES
	void writeDataFreq(string filename);
	void writeDataHuffman(string filename);
	void writeEncodedData(string filename, vector<int> *hexCode);

	// GETTERS & SETTERS
	string getEncodedData(string message);
	int getNbBytes() const;
	inline Node *Root() const { return root; }
	inline map<char, int> *getFreqMap() const { return charFreq; }
	inline map<char, string> getCodeMap() const { return huffmanCode; }
	inline void setRoot(Node *n) { root = n; }
};

#endif


