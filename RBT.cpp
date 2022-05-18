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
	: left(nullptr), right(nullptr), color(red) {} //red on insertion

Node::~Node(void)
{
	//TODO
}

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
	if (color == red)
		color = black;
	else
		color = red;
}

void Node::rotate_left(void)
{
	//TODO
}

void Node::rotate_right(void)
{
	//TODO
}
