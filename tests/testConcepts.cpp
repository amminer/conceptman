#include "../Concept.h"

void testPolymorphismAndMutation(Concept* c)
{
	string _choice;
	bool cont{true};
	while (cont){
		cout << "\n{edit} {add} or {remove} properties, {goto} website,\n"
		   << "test whether the concept {contains} a string, or {!q} to quit: ";
		getline(cin, _choice);
		if (_choice == "edit")
			c->edit();
		else if (_choice == "add")
			c->add();
		else if (_choice == "remove")
			cout << "Not yet implemented :P\n";
		else if (_choice == "goto")
			c->select_site();
		else if (_choice == "contains"){
			cout << "Enter a keyword: ";
			getline(cin, _choice);
			if (c->contains(_choice))
				cout << "Contains!\n";
			else
				cout << "Does not contain!\n";
		}
		else if (_choice == "!q")
			cont = false;
		if (cont)
			cout << '\n' << *c << '\n';
	}
}

void testSTL(void)
{
	STL c;
	string _choice;
	if (c.setup()){
		cout << '\n' << c << '\n';
		testPolymorphismAndMutation(&c);
	}
	else
		cout << "User canceled setup!\n";

}

void testModernCpp(void)
{
	//TODO
}

void testPythonLib(void)
{
	//TODO
}

int main(void)
{
	testSTL();
	return 0;
}
