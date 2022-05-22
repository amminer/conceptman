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
	STL			a, d, g, x, y, z;
	PythonLib	b, e, h, p, o, k;
	ModernCpp	c, f, i, m, l, w;

	a.set_name("vector");
	b.set_name("dataframe");
	c.set_name("templates");
	d.set_name("stl globals");		//<--result of user entering "global"
	e.set_name("python globals");	//<--result of user entering "global"
	f.set_name("OOP");
	g.set_name("okay");
	h.set_name("random");
	i.set_name("teststrings");
	x.set_name("gonna");
	y.set_name("write");
	z.set_name("an");
	p.set_name("automated");
	o.set_name("test");
	k.set_name("script");
	m.set_name("tomorrowmorning");
	l.set_name("highthroughput");
	w.set_name("orbust");

	tree.insert(a);
	tree.insert(b);
	tree.insert(c);
	tree.insert(d);
	tree.insert(e);
	tree.insert(f);
	tree.insert(g);
	tree.insert(h);
	tree.insert(i);
	tree.insert(x);
	tree.insert(y);
	tree.insert(z);
	tree.insert(p);
	tree.insert(o);
	tree.insert(k);
	tree.insert(m);
	tree.insert(l);
	tree.insert(w);

	//cout << "num concepts: " << tree.c_size() << '\n';
	cout << "num nodes: " << tree.size() << '\n';
	cout << "height: " << tree.height() << '\n';
	tree.display();
}

int main(void)
{
	//testNode(); //hacked into the dirt, thankful for smart pointers
	testRBT();
}
