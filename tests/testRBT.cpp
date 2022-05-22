#include "../RBT.h"

Node* node_ptr = nullptr;
Node* node2_ptr = nullptr;
Node  node;
Node  node2;
//Node seteq;
RBT tree;
STL p;
STL p2; 
STL p3; 
string choice;

void testNode(void)
{
	if (p.setup()){

		node_ptr = new Node;
		node = *node_ptr;
		node.add_data(p);
		//node.find_data(p)->add();
		cout << '\n' << node << '\n';

		p2.setup();
		//node.add_data(p2);	//RBT::insert will have to prevent duplicates using std::find?
		node2_ptr = new Node;
		node2 = *node2_ptr;
		node2.add_data(p2); //for rbt later
		cout << '\n' << node2 << '\n';

		/*
		cout << "Enter a class name to remove from the library: ";
		getline(cin, choice);
		node.remove_data<STL>(choice); //should fail silently on failed lookup
		cout << '\n' << node << '\n';  //or on <type> mismatch
		*/

		/*
		seteq = node;
		Node copied(node);
		cout << "SET EQUAL:\n" << seteq
			 << "\nCOPIED:\n" << copied << '\n';
		*/
		if (node_ptr)
			delete node_ptr;
		if (node2_ptr)
			delete node2_ptr;
	}
}

void testRBT(void)
{
	STL			a, d, g;
	PythonLib	b, e, h;
	ModernCpp	c, f, i;

	a.set_name("vector");
	b.set_name("dataframe");
	c.set_name("templates");

	tree.display();
	cout << "Inserting 1\n";
	tree.insert(a);
	cout << "Inserting 2\n";
	tree.insert(b);
	cout << "Inserting 3\n\n";
	tree.insert(c);
	tree.display();
	cout << "Root concept is at\n" << tree.get_root()->get_data().front().get() <<'\n';
	cout << "If insert was balanced, root should be at\n" << tree.find<Concept>(c.get_name()) << '\n';
	cout << "If insert was NOT balanced, root should be at\n" << tree.find<Concept>(a.get_name()) << '\n';
}

int main(void)
{
	//testNode(); //hacked into the dirt, thankful for smart pointers
	testRBT();
}
