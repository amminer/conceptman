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

enum Color {black, red};

class Node
{
	public:
		Node(void);
		~Node(void);

		void get_left(void);
		void get_right(void);
		void get_concept(void);
		void set_left(void);
		void set_right(void);
		void set_concept(void);

		recolor(void);
		rotate_left(void);	//TODO members of Node or RBT?
		rotate_right(void);	//TODO members of Node or RBT?
	private:
		Node* left;
		Node* right;
		Color color;
		Concept data;
}

class RBT
{
	public:
		RBT(void);
		~RBT(void);

		insert(//TODO	; //may require rotation
		display(void);		//TODO
		remove_all(void);	//TODO

		bool is_empty(void);		//TODO
		bool contains(string&);		//TODO
		Concept& find(string&);		//TODO
		Concept& find_min(void);	//TODO
		Concept& find_max(void);	//TODO

	private:
		Node* root;

		insert(Node*);		//TODO
		display(Node*);		//TODO
		remove_all(Node*);	//TODO

		bool contains(string&, Node*);	//TODO
		Node* find(string&, Node*);		//TODO
		Node* find_min(Node*);			//TODO
		Node* find_max(Node*);			//TODO
}

