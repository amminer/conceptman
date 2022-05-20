#include "../RBT.h"

void testNode(void)
{
	Node node;
	Node seteq;
	PythonLib p;
	if (p.setup()){
		node.add_data(p);
		//node.find_data(p)->add();
		cout << '\n' << node << '\n';
		//TODO add more pythons
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
	testNode();
	testRBT();
}
