#pragma once

#include "Concept.h"
#include <iostream>
#include <forward_list>
#include <iterator>
#include <memory>

using namespace std;

/*	Amelia Miner				5/17/2022
 *	cs202, section 003
 *	FILE:		RBT.h
 *	PURPOSE:	Declares the node and tree itself for a red-black tree.
 *	1. The root is always black.
 *	2. Null nodes (children of last node with data from root) are black.
 *	3. If a node is red, both of its children are black.
 *	4. Every path from root to null has the same number of black nodes.
 *
 *	Black nodes can have either color of either child.
 *	All operations are identical except insertion and deletion;
 *	Insertion (or deletion, not required for this asgmt) can necessitate
 * a rotation about a node (w or y being the node calling the rotate function
 * in the examples below, respectively).
 *
 *	left rotation:		w					y
 *					a__/ \__y    -->	w__/ \__z
 *					    x__/ \__z	a__/ \__x   
 *
 *	right rotation:		y					w
 *					w__/ \__z    -->	a__/ \__y
 *				a__/ \__x					x__/ \__z
 *
 *	For n nodes, the height of the tree has the relationship:
 *		n >= 2^(h/2) - 1
 */

typedef forward_list<shared_ptr<Concept>> List;
typedef forward_list<shared_ptr<Concept>>::iterator L_iterator;

class Node
{
	public:
		Node(void);
		Node(const Node& src);

		Node& operator=(const Node& op2);
		friend ostream& operator<<(ostream& out, const Node& op2);

		Node* get_left(void) const;
		Node*& get_left(void);
		Node* get_right(void) const;
		Node*& get_right(void);
		List get_data(void) const;
		List& get_data(void);
		void set_left(Node*);
		void set_right(Node*);
		void set_data(const List&);
		void add_data(const Concept&);
		 //client must specify what type of concept to rm or find
		template<typename T> void remove_data(const string&);
		template<typename T> shared_ptr<Concept> find_data(const string&);

		void recolor(void);
		void rotate_left(void);
		void rotate_right(void);

	private:
		bool color;		//true=red, false=black
		Node* left;
		Node* right;
		Node* parent;
		List data;

		//void remove_data(Concept&, L_iterator, L_iterator);
		template<typename T> shared_ptr<Concept> find_data(const Concept&, L_iterator, L_iterator);
};

class RBT
{
	public:
		RBT(void);
		RBT(const RBT& src);
		~RBT(void);

		RBT& operator=(const RBT& op2);
		friend ostream& operator<<(ostream& out, const RBT& op2); //maybe?

		void insert(const Concept&); //may require rotation
		void display(void);		//TODO
		void remove_all(void);	//TODO

		bool is_empty(void);		//TODO
		bool contains(string&);		//TODO
		Concept& find(string&);		//TODO
		Concept& find_min(void);	//TODO
		Concept& find_max(void);	//TODO

	private:
		Node* root;

		//recursive helpers
		void copy_all(Node*, Node*&);
		void insert(Node*);					//TODO
		void display(Node*);					//TODO
		void remove_all(Node*);				//TODO
		bool contains(string&, Node*);	//TODO
		Node* find(string&, Node*);		//TODO
		Node* find_min(Node*);			//TODO
		Node* find_max(Node*);			//TODO
};

#include "RBT.tpp" //template function definition
