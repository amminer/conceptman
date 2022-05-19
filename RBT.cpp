/*	Amelia Miner				5/17/2022
 *	cs202, section 003
 *	FILE:		RBT.cpp
 *	PURPOSE:	Defines the node and tree itself for a red-black tree.
 *	1. The root is always black.
 *	2. Null nodes (children of last node with data from root) are black.
 *	3. If a node is red, both of its children are black.
 *	4. Every path from root to null has the same number of black nodes.
 *
 *	Nodes are red on insertion.
 */

/*			CLASS NODE			*/

Node::Node(void)
	: color(true),		left(nullptr),	right(nullptr) //red on insertion
	  parent(nullptr),	data(nullptr)	{}

Node::~Node(void)
{
	if (data)
		delete data;
}

Node::Node(const Node& src)
{
	//TODO
}

/* 	OPERATORS		*/

Node& operator=(const Node& op2)
{
	//TODO
}

ostream& operator<<(ostream& out, const Node& op2) //friend
{
	//TODO
}

/*	PUBLIC METHODS	*/

void Node::get_left(void)
{
	//TODO
}

void Node::get_right(void)
{
	//TODO
}

void Node::get_concept(void)
{
	//TODO
}

void Node::set_left(void)
{
	//TODO
}

void Node::set_right(void)
{
	//TODO
}

void Node::set_concept(void)
{
	//TODO
}

void Node::recolor(void)
{
	color = !color;
}

void Node::rotate_left(void)
{
	//TODO
}

void Node::rotate_right(void)
{
	//TODO
}

/*	PRIVATE METHODS	*/

//TODO

/*			CLASS RBT			*/

RBT::RBT(void)
	: root(nullptr) {}

RBT::RBT(const RBT& src)
{
	//TODO
}

RBT::~RBT(void)
{
	remove_all();
}

/* 	OPERATORS		*/

RBT& operator=(const RBT& op2)
{
	//TODO
}

ostream& operator<<(ostream& out, const BST& op2) //friend
{
	//TODO maybe not
}

/*	PUBLIC METHODS	*/

//TODO

insert(const Concept&) //may require rotation
{
	//TODO the big one
}

void RBT::display(void)
{
	//TODO in-order traversal
}

remove_all(void)
{
	//TODO post-order traversal
}

bool is_empty(void)
{
	//TODO
}

bool contains(string&)
{
	//TODO
}

Concept& find(string&)
{
	//TODO
}

Concept& find_min(void)
{
	//TODO
}

Concept& find_max(void)
{
	//TODO
}


/*	PRIVATE METHODS	*/
//recursive helpers

insert(Node*)
{
	//TODO
}

display(Node*)
{
	//TODO
}

remove_all(Node*)
{
	//TODO
}

bool contains(string&, Node*)
{
	//TODO
}

Node* find(string&, Node*)
{
	//TODO
}

Node* find_min(Node*)
{
	//TODO
}

Node* find_max(Node*)
{
	//TODO
}
