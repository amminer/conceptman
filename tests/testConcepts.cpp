#include "../Concept.h"
//NOTE! TODO
// Should indicate to user in a {help} message that attempting to add a site
//	with a duplicate URL or a method with a duplicate name will be silently
//	rejected, and no addition will occur.
// Further, if an edit is made that would cause the edited item to take the
//	url or name of an existing item, the edit is silently rejected and the
//	state of the program is not changed.
// Could maybe present this as a warning whenever this occurs, but haven't
//	figured out a way to do this cleanly yet...

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
			c->remove();
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
	PythonLib c;
	string _choice;
	if (c.setup()){
		cout << '\n' << c << '\n';
		testPolymorphismAndMutation(&c);
	}
	else
		cout << "User canceled setup!\n";
}

int main(void)
{
	testSTL();
	return 0;
}
