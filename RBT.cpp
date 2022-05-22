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
	  parent(nullptr),	collapsed(true)	{}

//copy constructor copies data via = AND position in tree
Node::Node(const Node& src)
	: color(src.color),		left(src.left),		right(src.right),
	  parent(src.parent),	collapsed(true),	data(src.data)		{}

//inits a node to a singleton list containing src
Node::Node(const Concept& src)
	: color(true),		left(nullptr),	right(nullptr), //red on insertion
	  parent(nullptr),	collapsed(true)
{
	add_data(src);
}

Node::~Node(void)
{
	//if (!data.empty()){
	for (auto c_sptr: data)
		c_sptr.reset();
	//}
}

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
	if (!op2.data.empty()){
		//if ostream is not cout expand all nodes?
		string name = op2.data.front()->get_name();
		if (!op2.collapsed)
			out << '\n';
		out << "//**~~~\"" << name << "\"~~~**//\n";
		if (!op2.collapsed){
			auto it = op2.data.begin();
			auto end = op2.data.end();
			while (it != end){
				out << **it << '\n';
				++it;
			}
		}
	}
	return out;
	//else do nothing; do not print empty nodes, since we can't remove them...
}

/*	PUBLIC METHODS	*/

bool Node::is_red(void) const
{
	return color;
}
bool Node::is_black(void) const
{
	return !color;
}

void Node::collapse(void)
{
	collapsed = true;
}

void Node::expand(void)
{
	collapsed = false;
}

Node* Node::get_parent(void) const
{
	return parent;
}

Node*& Node::get_parent(void)
{
	return parent;
}

Node* Node::get_left(void) const
{
	return left;
}

Node*& Node::get_left(void)
{
	return left;
}

Node* Node::get_right(void) const
{
	return right;
}

Node*& Node::get_right(void)
{
	return right;
}

List Node::get_data(void) const
{
	return data;
}

List& Node::get_data(void)
{
	return data;
}

void Node::set_parent(Node* new_parent)
{
	parent = new_parent;
}

void Node::set_left(Node* new_left)
{
	left = new_left;
}

void Node::set_right(Node* new_right)
{
	right = new_right;
}

//add a concept to the internal list
void Node::add_data(const Concept& new_concept)
{
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
		return; //shouldn't ever get here based on RBT implem but have to check
	to_remove = find_data<T>(key_name);
	if (to_remove){
		if (dynamic_pointer_cast<T>(to_remove)){
			data.remove(to_remove);
		}
	} //check if node was left empty in RBT, remove if so
	//fails silently? todo
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

void Node::recolor(bool new_color)
{
	color = new_color;
}

bool Node::has_loose_match(const string& key)
{
	return has_loose_match(key, data.begin(), data.end());
}
bool Node::has_loose_match(const string& key, L_iterator list, L_iterator end)
{
	if (list == end)
		return false;
	else if ((**list).contains(key)){
		return true;
	}
	else
		return has_loose_match(key, ++list, end);
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
void RBT::remove_all(Node*& rem_root)
{
	Node*& rem_left = rem_root->get_left();
	Node*& rem_right = rem_root->get_right();
	if (rem_left)
		remove_all(rem_left);
	if (rem_right)
		remove_all(rem_right);
	delete rem_root;
	rem_root = nullptr;
	return;
}

/* 	OPERATORS		*/

RBT& RBT::operator=(const RBT& op2)
{
	if (this != &op2){
		if (root)
			remove_all(root);
		copy_all(op2.root, root);
	}
	return *this;
}
//preorder traversal
//DEST MUST BE NULL ON INITIAL CALL
void RBT::copy_all(Node* src, Node*& dest)
{
	Node* clone_left = src->get_left();
	Node* clone_right = src->get_right();
	dest = new Node(*src); //copy constr to copy position 
	if (clone_left)
		copy_all(clone_left, dest->get_left());
	if (clone_right)
		copy_all(clone_right, dest->get_right());
	return;
}

ostream& operator<<(ostream& out, const RBT& op2) //friend
{
	op2.display(out);
	return out;
}

/*	PUBLIC METHODS	+	PRIVATE RECURSIVE HELPERS	*/

size_t RBT::height(void)
{
	return height(root);
}
size_t RBT::height(Node* tree)
{
	if (!tree)
		return 0;
	return max(height(tree->get_left()), height(tree->get_right())) + 1;
}

size_t RBT::size(void)
{
	return count_nodes(root);
}
size_t RBT::count_nodes(Node* tree)
{
	if (!tree)
		return 0;
	else
		return count_nodes(tree->get_left()) + count_nodes(tree->get_right())
			 + 1;
}

void RBT::insert(const Concept& new_c) //may require rotation
{
	Node* new_node = new Node(new_c);
	if (!root){ //CASE 1 root is passed in null
		root = new_node; //no need to fix
		root->recolor(0);
	}
	else
		insert(new_node, root, root->get_parent()); //recursive helper
}
void RBT::insert(Node*& new_node, Node*& this_node, Node*& this_parent)
{
	Concept& new_c = *new_node->get_data().front();
	Concept& this_c = *this_node->get_data().front();
	Node*& this_left = this_node->get_left();
	Node*& this_right = this_node->get_right();
	bool check_rbt {false};
	if (new_c == this_c){	//case names match, add to same list
		this_node->add_data(new_c);	//(discard new_node)
	}
	else if (new_c < this_c){	//case new < this, seek left
		if (this_left)	//more to check
			return insert(new_node, this_left, this_node);
		else{			//next up is void - add here
			this_node->set_left(new_node);
			new_node->set_parent(this_node);
			check_rbt = true;
		}
	}
	else{	//case new > this, seek right
		if (this_right)
			return insert(new_node, this_right, this_node);
		else{
			this_node->set_right(new_node);
			new_node->set_parent(this_node);
			check_rbt = true;
		}
	}
	if (check_rbt){
		if (new_node->get_parent()->is_black()) //CASE 2
			; //tree cannot be violated, go on/no need to fix
		else{ //new node's parent is red CASE 3
			fix_insert(new_node);
		}
	}
}

/* ^ INSERT
   Welcome to the ascii cafe - if you're using vim and jumping between blocks
         ,-"-.		with { and }, take a moment to rest or visit the
       _r-----i          _		RBT insert algorithms adjacent to the
       \      |-.      ,###.		cafe. enjoy your stay!
     	|     | |    ,-------.
       	|     | |   c|       |      {draw pie here}  ,--. http://www.ascii-art
       	|     |'     |       |      ______TODO_____ C|  | .de/ascii/c/coffee.txt
		(=====)      =========      \_____________/  `==' 
(HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH)
   V FIX_INSERT */

void RBT::fix_insert(Node* new_node)
{
	if (Node*& mother = new_node->get_parent(); mother){
		if (Node*& grandmother = mother->get_parent(); grandmother){
			if (mother->is_red())
				fix_insert_recursive(new_node);
		}
		else
			mother->recolor(0);
	}
	else
		new_node->recolor(0);
}
//Only call when mother is red. num of ! indicates level of nesting in logic
void RBT::fix_insert_recursive(Node* new_node)//, Node*& mother,
					 //Node*& grandmother)
{
	Node* mother = new_node->get_parent();
	Node* grandmother = mother->get_parent();
	Node* aunt = nullptr;
	if (mother == grandmother->get_right()){	//!case left aunt
		aunt = grandmother->get_left();
		if (aunt and aunt->is_red()){			//!!case red left aunt
			aunt->recolor(0);
			mother->recolor(0);
			grandmother->recolor(1);
			return fix_insert(grandmother);
		}
		else{									//!!case black left aunt (BA)
			if (new_node == mother->get_left()){//!!!case BA:RL
				new_node = mother;
				rotate_right(new_node);
				mother = new_node->get_parent();
				grandmother = mother->get_parent();
			}
			mother->recolor(0);					//!!!case BA:RR & rest of BA:RL
			grandmother->recolor(1);
			rotate_left(grandmother);
			return fix_insert(new_node);
		}
	}
	else{										//!case right aunt
		aunt = grandmother->get_right();
		if (aunt and aunt->is_red()){			//!!case red right aunt
			aunt->recolor(0);
			mother->recolor(0);
			grandmother->recolor(1);
			return fix_insert(grandmother);
		}
		else{									//!!case black right aunt (BA)
			if (new_node == mother->get_right()){//!!!case BA:LR
				new_node = mother;
				rotate_left(new_node);
				mother = new_node->get_parent();
				grandmother = mother->get_parent();
			}
			mother->recolor(0);					//!!!case BA:LL & rest of BA:LR
			grandmother->recolor(1);
			rotate_right(grandmother);
			return fix_insert(new_node);
		}
	}
}
void RBT::rotate_left(Node* this_node)
{
	Node* this_right {this_node->get_right()};
	Node* this_parent {this_node->get_parent()};
	this_node->set_right(this_right->get_left());
	if (this_right->get_left())
		this_right->get_left()->set_parent(this_node);
	this_right->set_parent(this_parent);
	if (!this_parent)
		root = this_right;
	else if (this_node == this_parent->get_left())
		this_parent->set_left(this_right);
	else
		this_parent->set_right(this_right);
	this_right->set_left(this_node);
	this_node->set_parent(this_right);
}
void RBT::rotate_right(Node* this_node)
{
	Node* this_left {this_node->get_left()};
	Node* this_parent {this_node->get_parent()};
	this_node->set_left(this_left->get_right());
	if (this_left->get_right())
		this_left->get_right()->set_parent(this_node);
	this_left->set_parent(this_parent);
	if (!this_parent)
		root = this_left;
	else if (this_node == this_parent->get_right())
		this_parent->set_right(this_left);
	else
		this_parent->set_left(this_left);
	this_left->set_right(this_node);
	this_node->set_parent(this_left);
}

void RBT::display(ostream& out) const
{
	if (!root)
		cout << "Empty!\n";
	else
		in_order_ostream_dump(out, root);
	return;
}

bool RBT::is_empty(void)
{
	bool ret = true;
	if (root)
		ret = root->get_data().empty();
	return ret;
			
}

/*
"defined" in .tpp
template<typename T>
T* RBT::find(string& key) const
{
	T* ret {nullptr};
	if (root)
		ret = find<T>(key, root); 
	return ret;
}
*/

Node* RBT::find_node(string& key) const
{
	Node* ret {nullptr};
	if (root)
		ret = find_node(key, root); 
	return ret;
}

Node* RBT::find_min(void)
{
	Node* ret {nullptr};
	if (root)
		ret = find_min(root);
	return ret;
}

Node* RBT::find_max(void)
{
	Node* ret {nullptr};
	if (root)
		ret = find_max(root);
	return ret;
}

void RBT::expand_matches(const string& key)
{
	expand_matches(key, root);
	return;
}
//this_node == root on init
void RBT::expand_matches(const string& key, Node* this_node)
{
	if (this_node){
		Node* this_left = this_node->get_left();
		Node* this_right = this_node->get_right();
		if (this_node->has_loose_match(key))
			this_node->expand();
		else
			this_node->collapse();
		expand_matches(key, this_left);
		expand_matches(key, this_right);
	}
	return;
}

void RBT::collapse_all(void)
{
	collapse_all(root);
	return;
}
void RBT::collapse_all(Node* this_node)
{
	if (this_node){
		this_node->collapse();
		collapse_all(this_node->get_left());
		collapse_all(this_node->get_right());
	}
	return;
}

/*	PRIVATE METHODS	*/
//recursive helpers

/*	Should only be called when a new node is inserted and its parent is red.
 *	Wrapper function guards recursive calls that would otherwise fault.
 *	Adapted/translated to recursion from the various iterative solutions:
 *		https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/red-black-trees/RedBlackTree.cpp
 */
Node* RBT::find_min(Node* node)
{
	if (!node->get_left())
		return node;
	else
		return find_min(node->get_left());
}

Node* RBT::find_max(Node* node)
{
	if (!node->get_right())
		return node;
	else
		return find_max(node->get_right());
}

/*
Node* RBT::get_root(void) //testing
{
	return root;
}
*/

//could potentially be used for a (very inefficient) save-to-file
void RBT::in_order_ostream_dump(ostream& out, const Node* tree) const
{
	if (!tree)
		return;
	else{
		in_order_ostream_dump(out, tree->get_left());
		out << *tree;
		in_order_ostream_dump(out, tree->get_right());
	}
}

/*
"defined" in .tpp
//preorder traversal
template<typename T>
T* RBT::find(string& key, Node* node) const
{
	T* ret {nullptr};
	if (!node)
		ret = nullptr; //unnecessary but explicit
	//please fasten your seatbelt for the following line
	else if (T* that =
			 dynamic_cast<T*>(node->find_data<T>(key).get()); that){
		ret = that;
	}
	else{
		ret = find<T>(key, node->get_left());
		if (!ret)
			ret = find<T>(key, node->get_right());
	}
	return ret;
}
*/

Node* RBT::find_node(string& key, Node* node) const
{
	Node* ret {nullptr};
	if (!node)
		ret = nullptr; //unnecessary but explicit
	else if (Concept* that = node->find_data<Concept>(key).get(); that)
		ret = node;
	else{
		ret = find_node(key, node->get_left());
		if (!ret)
			ret = find_node(key, node->get_right());
	}
	return ret;
}

/*
Node* find_predecessor(Node*)
{
}

Node* find_successor(Node*)
{
}
*/
