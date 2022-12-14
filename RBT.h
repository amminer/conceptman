#pragma once

#include "Concept.h" 		//stores concepts
#include <iostream>
#include <forward_list>		//stores lists of concepts
#include <iterator>			//lists use iterators
#include <algorithm>		//std::max
#include <memory>			//god bless shared_ptr

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
 *	subtrees go along with their parents during rotations.
 */

typedef forward_list<shared_ptr<Concept>> List;
typedef forward_list<shared_ptr<Concept>>::const_iterator L_iterator;

class Node
{
	public:
		Node(void);
		Node(const Node&);
		Node(const Concept&);
		~Node(void);

		Node& operator=(const Node& op2);
		friend ostream& operator<<(ostream& out, const Node& op2);

		void collapse(void);
		void expand(void);	//for display

		bool is_red(void) const;
		bool is_black(void) const;
		Node* get_parent(void) const;
		Node*& get_parent(void);
		Node* get_left(void) const;
		Node*& get_left(void);
		Node* get_right(void) const;
		Node*& get_right(void);
		List get_data(void) const;
		List& get_data(void);
		void set_parent(Node*);
		void set_left(Node*);
		void set_right(Node*);
		void set_data(const List&);
		void add_data(const Concept&);
		bool has_loose_match(const string&) const;
		 //client must specify what type of concept to rm or find
		template<typename T> void remove_data(const string&);
		template<typename T> shared_ptr<Concept> find_data(const string&);

		void recolor(const bool);

	private:
		bool color;		//true=red, false=black
		Node* left;
		Node* right;
		Node* parent;
		bool collapsed;
		List data;

		//void remove_data(Concept&, L_iterator, L_iterator);
		//should this be shared_ptr<T>?
		template<typename T> shared_ptr<Concept>
			find_data(const Concept&, L_iterator, L_iterator) const;
		bool has_loose_match(const string&, L_iterator, L_iterator) const;
};

class RBT
{
	public:
		RBT(void);
		RBT(const RBT& src);
		~RBT(void);

		RBT& operator=(const RBT& op2);
		friend ostream& operator<<(ostream& out, const RBT& op2);

		size_t size(void) const;
		size_t height(void) const;
		void insert(const Concept&);
		void rotate_left(Node*);
		void rotate_right(Node*);
		void display(ostream& = cout) const;
		void remove_all(void);
		bool is_empty(void) const;
		template<typename T> T* find(string&) const;
		Node* find_node(string&) const;
		void expand_matches(const string&);
		void collapse_all(void);

		Node* get_root(void);			//testing


	private:
		Node* root;

		//recursive helpers
		size_t height(Node*) const;
		size_t count_nodes(Node*) const;
		void copy_all(Node*, Node*&);
		void insert(Node*&, Node*&, Node*&);
		void fix_insert(Node*);
		void fix_insert_recursive(Node*);
		void in_order_ostream_dump(ostream& out, const Node* tree) const;
		void remove_all(Node*&);
		template<typename T> T* find(string&, Node*) const;
		Node* find_node(string&, Node*) const;
		void expand_matches(const string&, Node*);
		void collapse_all(Node*);
		Node* find_min(void) const;
		Node* find_min(Node*) const;
		Node* find_max(void) const;
		Node* find_max(Node*) const;
		//Node* find_predecessor(Node*);
		//Node* find_successor(Node*);
};

#include "RBT.tpp" //template function definitions
