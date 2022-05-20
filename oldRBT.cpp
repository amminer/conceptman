#include "RBT.h"

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
	: color(true),		left(nullptr),	right(nullptr), //red on insertion
	  parent(nullptr),	data(nullptr)	{}

Node::~Node(void)
{
	if (data)
		delete [] data;
}

//copy constructor copies data via = AND position in tree TODO right way?
Node::Node(const Node& src)
	: color(true),		left(nullptr),	right(nullptr),
	  parent(nullptr),	data(nullptr)
{
	//TODO test
	*this = src;
}

/* 	OPERATORS		*/

// = sets only data
Node& Node::operator=(const Node& op2)
{
	//TODO test
	if (this != &op2){
		if (data)
			delete data;
		data = new List;
		data = op2.data;
	}
	return *this;
}

ostream& operator<<(ostream& out, const Node& op2) //friend
{
	//TODO
	//temp for testing
	out << "NODE AT " << &op2 << ", COLOR:" << op2.color << ", LEFT:" << op2.left << ", RIGHT:" << op2.right
		<< ", PARENT:" << op2.parent << ", DATA:\n";
	L_iterator it = op2.data->begin();
	L_iterator end = op2.data->end();
	while (it != end){
		out << **it << '\n';
		++it;
	}
	return out;
}

/*	PUBLIC METHODS	*/

Node* Node::get_left(void) const
{
	//TODO test
	return left;
}

Node*& Node::get_left(void)
{
	//TODO test
	return left;
}

Node* Node::get_right(void) const
{
	//TODO test
	return right;
}

Node*& Node::get_right(void)
{
	//TODO test
	return right;
}

List* Node::get_data(void) const
{
	//TODO test
	return data;
}

List*& Node::get_data(void)
{
	//TODO test
	return data;
}

void Node::set_left(Node* new_left)
{
	//TODO test
	left = new_left;
}

void Node::set_right(Node* new_right)
{
	//TODO test
	right = new_right;
}

//add a concept to the internal list
void Node::add_data(const Concept& new_concept)
{
	//TODO test
	ModernCpp* new_m;
	PythonLib* new_p;
	STL* new_s;
	if (!data)
		data = new List();
	if (auto m = dynamic_cast<const ModernCpp*>(&new_concept); m){
		new_m = new ModernCpp(*m);
		data->push_front(new_m);
	}
	else if (auto p = dynamic_cast<const PythonLib*>(&new_concept); p){
		new_p = new PythonLib(*p);
		data->push_front(new_p);
	}
	else if (auto s = dynamic_cast<const STL*>(&new_concept); s){
		new_s = new STL(*s);
		data->push_front(new_s);
	}
}

//remove a concept from the internal list;
//returns whether found/removed
void Node::remove_data(const Concept& key)
{
	//TODO test
	Concept* to_remove {nullptr};
	if (!data)
		return;
	to_remove = find_data(key);
	if (to_remove)
		data->remove(to_remove);
}

Concept* Node::find_data(const Concept& key)
{
	//TODO test
	Concept* ret {nullptr};
	if (data)
		ret = find_data(key, data->begin(), data->end());
	return ret;
}

//resets this list to = new_list
void Node::set_data(const List& new_list)
{
	//TODO test
	if (data)
		delete data;
	data = new List(new_list);
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

Concept* Node::find_data(const Concept& key, L_iterator list, L_iterator end)
{
	//TODO test
	if (**list == key){
		return *list;
	}
	else if (list == end)
		return nullptr;
	else
		return find_data(key, ++list, end);
}


/*			CLASS RBT			*/

RBT::RBT(void)
	: root(nullptr) {}

RBT::RBT(const RBT& src)
{
	*this = src;
}

RBT::~RBT(void)
{
	if (root)
		remove_all(root);
}

/* 	OPERATORS		*/

RBT& RBT::operator=(const RBT& op2)
{
	//TODO test
	if (this != &op2){
		if (root)
			remove_all(root);
		copy_all(op2.root, root);
	}
	return *this;
}
void RBT::remove_all(Node* rem_root)
{
	//TODO test
	Node* rem_left = rem_root->get_left();
	Node* rem_right = rem_root->get_right();
	if (rem_left)
		remove_all(rem_left);
	if (rem_right)
		remove_all(rem_right);
	delete rem_root;
	rem_root = nullptr;
	return;
}

ostream& operator<<(ostream& out, const RBT& op2) //friend
{
	//TODO maybe not
}

/*	PUBLIC METHODS	*/

//TODO

void RBT::insert(const Concept&) //may require rotation
{
	//TODO the big one
}

void RBT::display(void)
{
	//TODO in-order traversal
}

bool RBT::is_empty(void)
{
	//TODO
}

bool RBT::contains(string&)
{
	//TODO
}

Concept& RBT::find(string&)
{
	//TODO
}

Concept& RBT::find_min(void)
{
	//TODO
}

Concept& RBT::find_max(void)
{
	//TODO
}

Node*& RBT::get_root(void)
{
	return root;
}

/*	PRIVATE METHODS	*/
//recursive helpers

void RBT::insert(Node*)
{
	//TODO
}

void RBT::display(Node*)
{
	//TODO
}

//DEST MUST BE NULL ON INITIAL CALL
void RBT::copy_all(Node* src, Node*& dest)
{
	//TODO test
	Node* clone_left = src->get_left();
	Node* clone_right = src->get_right();
	dest = new Node(*src); //copy constr to copy position 
	if (clone_left)
		copy_all(clone_left, dest->get_left());
	if (clone_right)
		copy_all(clone_right, dest->get_right());
	return;
}

bool RBT::contains(string&, Node*)
{
	//TODO
}

Node* RBT::find(string&, Node*)
{
	//TODO
}

Node* RBT::find_min(Node*)
{
	//TODO
}

Node* RBT::find_max(Node*)
{
	//TODO
}
