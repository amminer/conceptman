#include "../RBT.h"

void testNode(void)
{
	Node node;
	Node seteq;
	STL p;
	string choice;
	if (p.setup()){

		node.add_data(p);
		//node.find_data(p)->add();
		cout << '\n' << node << '\n';

		STL p2; p2.setup(); //training wheels off
		node.add_data(p2);	//RBT::add_data will have to prevent duplicates using std::find?
		cout << '\n' << node << '\n';

		cout << "Enter a class name to remove from the library: ";
		getline(cin, choice);
		node.remove_data<STL>(choice); //should fail silently on failed lookup
		cout << '\n' << node << '\n';  //or on <type> mismatch

		/*
		seteq = node;
		Node copied(node);
		cout << "SET EQUAL:\n" << seteq
			 << "\nCOPIED:\n" << copied << '\n';
		*/
	}
}

void testRBT(void)
{
	RBT tree;
}

int main(void)
{
	testNode(); //hacked into the dirt
	testRBT(); //TODO
}
