#pragma once
#include"BST.h"
#include"List.h"
#include "Encoded list.h"
#include <iomanip>

size_t Find_space(List& list, Node* node) {
	size_t index = 0;
	for (size_t i = 0; i < list.GetSize(); i++) {
		if (node->weight >= list[i]->weight) {
			continue;
		}
		else {
			index = i;
			break;
		}
	}
	if (index == 0) {
		index = list.GetSize();
	}
	return index;
}

size_t Max_Size(Encoded_List* list) {
	size_t len = _msize(list) / sizeof(Encoded_List);
	size_t max = 0;
	for (size_t i = 0; i < len; i++) {
		if (list[i].GetSize() > max) {
			max = list[i].GetSize();
		}
	}
	return max;
}


Encoded_List Find_code_sym(char sym, Encoded_List* list) {
	size_t len = _msize(list) / sizeof(Encoded_List);
	for (size_t i = 0; i < len; i++) {
		if (list[i].GetSym() == sym) return list[i];
	}
}



class Huffman_encoder {
private:
	List nodes; // a list that stores nodes with the value of their weights	
	Encoded_List* encoded_list; // character codes are stored in the list items
	std::string expr_to_encode; // the expression to encode
	std::string encoded_expr; // encoded expression that we store for ease of use
public:
	Huffman_encoder();
	~Huffman_encoder();
	Encoded_List* Encode();
	std::string Decode();
	List GetNodes();
	void Parse(std::string in_expr);
	void Print_alphabet();
	void Print_char_codes();
	void Print_encode_expr();
};


Huffman_encoder::Huffman_encoder() {
	nodes = List();
	encoded_list = nullptr;
}


Huffman_encoder::~Huffman_encoder() {
	delete encoded_list;
	nodes.Clear();
	encoded_expr.clear();
	expr_to_encode.clear();
}

List Huffman_encoder::GetNodes() {
	return nodes;
}

void Huffman_encoder::Parse(std::string in_expr) {
	if (!in_expr.length()) {
		throw std::invalid_argument("An empty string cannot be encoded\n");
	}
	
	// init list first symbol
	Node* node = new Node(1, in_expr[0]);
	this->nodes.Push_back(node);

	for (size_t i = 1; i < in_expr.length(); i++) {
		int index = nodes.Contains(in_expr[i]);
		if (index == -1) {
			node = new Node(1, in_expr[i]);
			this->nodes.Push_back(node);
		}
		else {
			this->nodes[index]->weight++;
		}
	}
	this->expr_to_encode = in_expr;
	this->nodes.Sort();
}


Encoded_List* Huffman_encoder::Encode() {
	this->encoded_list = new Encoded_List[nodes.GetSize()];
	if (nodes.GetSize() == 1) {
		// If there is one element, we encode it with one and return
		encoded_list[0].Push_back(1);
		return encoded_list;
	}
	
	while (nodes.GetSize() != 1) {
		Node* newNode = new Node(nodes[0]->weight + nodes[1]->weight, ' ', nodes[0], nodes[1]);
		this->nodes[0]->Parent = newNode;
		this->nodes[1]->Parent = newNode;
		// Removing the two nodes with the lowest weights
		nodes.Pop_Front();
		nodes.Pop_Front();
		// Adding a new node with a weight equal to the sum of the two deleted nodes
		size_t index_set_node = Find_space(nodes, newNode);
		this->nodes.Insert(newNode, index_set_node);
	}

	BST tree = BST(nodes[0]);
	Iterator* iter = tree.create_dft_iterator();	
	size_t num_of_sym = 0;

	// Building binary code
	while (iter->has_next()) {
		Node* node = iter->next();
		if (node != nullptr && node->IsLeaf()) { // if the node is a symbol
			this->encoded_list[num_of_sym].SetSym(node->sym);

			while (node->Parent != nullptr) { // We begin to climb up to the root
				if (node->Parent->LeftNode == node) { // if the left node - add zero
					this->encoded_list[num_of_sym].Push_front(0);
				}
				else { // else add one 
					this->encoded_list[num_of_sym].Push_front(1);
				}
				node = node->Parent;				
			}
			num_of_sym++;
		}
	}
	
	size_t len = _msize(encoded_list) / sizeof(Encoded_List); // number of encoded characters in the list 
															  // (one element of the list array is the character code)

	Encoded_List* new_expr = new Encoded_List[expr_to_encode.length()]; // encoded representation of a list expression
	for (size_t i = 0; i < expr_to_encode.length(); i++) {
		Encoded_List code_sym = Find_code_sym(expr_to_encode[i], encoded_list);
		for (size_t j = 0; j < code_sym.GetSize(); j++) {
			encoded_expr += char(code_sym[j] + '0');
		}
		new_expr[i] = Encoded_List(code_sym);
		encoded_expr += ' ';
	}
	return new_expr;
}


std::string Huffman_encoder::Decode() {
	if (encoded_list == nullptr) throw std::runtime_error("Nothing is encoded\n");
	return expr_to_encode;
}

void Huffman_encoder::Print_alphabet() {
	if(nodes.GetSize() == 0) throw std::runtime_error("Nothing is encoded\n");

	std::cout << "Table of character frequencies:\n";
	for (size_t i = 0; i < nodes.GetSize(); i++) {
		std::cout << nodes[i]->sym << " ";
	}
	std::cout << std::endl;

	for (size_t i = 0; i < nodes.GetSize(); i++) {
		std::cout << nodes[i]->weight << " ";
	}

	std::cout << std::endl << std::endl;
}

void Huffman_encoder::Print_char_codes() {
	if(encoded_list == nullptr) throw std::runtime_error("Nothing is encoded\n");
	std::cout << "Char codes:\n";
	size_t len = _msize(encoded_list) / sizeof(Encoded_List);

	for (size_t i = 0; i < len; i++) {
	std::cout << encoded_list[i].GetSym() << " - ";
		for (size_t j = 0; j < encoded_list[i].GetSize(); j++) {
			std::cout << char(encoded_list[i][j] + '0');
		}
		std::cout << " ; " << std::endl;
	}
	std::cout << std::endl << std::endl;
}

void Huffman_encoder::Print_encode_expr() {
	if (encoded_list == nullptr) throw std::runtime_error("Nothing is encoded\n");
	std::cout << "Encoded expression:\n" << encoded_expr << std::endl;
}