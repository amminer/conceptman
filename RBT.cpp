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
	  parent(nullptr)	{}

//copy constructor copies data via = AND position in tree
Node::Node(const Node& src)
	: color(src.color),		left(src.left),	right(src.right),
	  parent(src.parent),	data(src.data)	{}

/* 	OPERATORS		*/

// = sets only data, does not copy color or position
Node& Node::operator=(const Node& op2)
{
	if (this != &op2){
		/*
		color = op2.color;
		left = op2.left;
		right = op2.right;
		parent = op2.parent;
		*/
		data = op2.data;
	}
	return *this;
}

ostream& operator<<(ostream& out, const Node& op2) //friend
{
	//temp for testing
	out << "NODE AT " << &op2 << ", COLOR:" << op2.color << ", LEFT:" << op2.left << ", RIGHT:" << op2.right
		<< ", PARENT:" << op2.parent << ", DATA:\n";
	auto it = op2.data.begin();
	auto end = op2.data.end();
	if (it == end)
		out << "NONE (this would not display at all in the full program\n";
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

List Node::get_data(void) const
{
	//TODO test
	return data;
}

List& Node::get_data(void)
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
	//TODO is this the way?
	if (auto m = dynamic_cast<const ModernCpp*>(&new_concept); m){
		shared_ptr<ModernCpp> new_m{new ModernCpp(*m)};
		data.push_front(new_m);
	}
	else if (auto p = dynamic_cast<const PythonLib*>(&new_concept); p){
		shared_ptr<PythonLib> new_p{new PythonLib(*p)};
		data.push_front(new_p);
	}
	else if (auto s = dynamic_cast<const STL*>(&new_concept); s){
		shared_ptr<STL> new_s{new STL(*s)};
		data.push_front(new_s);
	}
}

/*
"defined" in .tpp
remove a concept from the internal list.
template<typename T>
void Node::remove_data(const string& key_name)
{
	shared_ptr<Concept> to_remove{nullptr};
	if (data.empty())
		return;
	to_remove = find_data<T>(key_name);
	if (to_remove){
		if (dynamic_pointer_cast<T>(to_remove)){
			data.remove(to_remove);
		}
	}
}
*/

/*
"defined" in .tpp
template<typename T>
shared_ptr<Concept> Node::find_data(const string& key_name)
{
	shared_ptr<Concept> ret {nullptr};
	if (!data.empty()){
		auto key = ModernCpp(key_name); //don't instantiate unless searching
		ret = find_data<T>(key, data.begin(), data.end());
	}
	return ret;
}
*/

//resets this list to = new_list
void Node::set_data(const List& new_list)
{
	data = new_list;
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

/*
"defined" in .tpp
//This should use iterators instead of returning a pointer, but
//we have not gone over them in class...
//Could also use exception handling, but would rather check a pointer in
//client code than have to code and catch yet another exception
template<typename T>
shared_ptr<Concept> Node::find_data(const Concept& key, L_iterator list, L_iterator end)
{
	if (list == end)
		return nullptr;
	else if (**list == key){
		if (dynamic_pointer_cast<T>(*list)) //type check
			return *list;
		else
			return find_data<T>(key, ++list, end);
	}
	else
		return find_data<T>(key, ++list, end);
}
*/


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

