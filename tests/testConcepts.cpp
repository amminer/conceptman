#include "../Concept.h"
//NOTE! todo
// Should indicate to user in a {help} message that attempting to add a site
//	with a duplicate URL or a method with a duplicate name will be silently
//	rejected, and no addition will occur.
// Further, if an edit is made that would cause the edited item to take the
//	url or name of an existing item, the edit is silently rejected and the
//	state of the program is not changed.
// Could maybe present this as a warning whenever this occurs, but haven't
//	figured out a way to do this cleanly yet...

void testSTL(void);

void rtti(Concept* c)
{
	if (auto x = dynamic_cast<PythonLib*>(c)){
		if (x->is_object_oriented()) //will be used in a loop in ConceptMgr
			cout << "is oop\n";
		else
			cout << "is NOT oop\n";
	}
	else if (auto y = dynamic_cast<STL*>(c)){
		cout << "Set up another STL for testing...\n"
			 << "DO NOT CALL RTTI AGAIN! Just exit when it's set up\n";
		STL temp; temp.setup(); temp.add(); //add a method or two
		y->copy_methods(temp);
		cout << "Result of copy_methods:\n\n";
	}
	else if (auto z = dynamic_cast<ModernCpp*>(c)){
		string results = z->check_applicability();
		cout << results << '\n';
	}
	return;
}

void testPolymorphismAndMutation(Concept* c)
{
	string _choice;
	bool cont{true};
	while (cont){
		cout << "{edit} {add} or {remove} properties, {goto} website,\n"
		   << "test whether the concept {contains} a string,\n"
		   << "test {rtti}, or {!q} to quit: ";
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
		else if (_choice == "rtti"){
			rtti(c);
		}
		else if (_choice == "!q")
			cont = false;
		if (cont)
			cout << '\n' << *c << '\n';
		cout << '\n';
	}
}

void testSTL(void)
{
	STL c;
	string _choice;
	cout << "setting up a stl...\n";
	if (c.setup()){
		cout << '\n' << c << "\n\n";
		testPolymorphismAndMutation(&c);
	}
	else
		cout << "User canceled setup!\n";

	return;
}

void testModernCpp(void)
{
	ModernCpp c;
	string _choice;
	cout << "setting up a modern...\n";
	if (c.setup()){
		cout << '\n' << c << "\n\n";
		testPolymorphismAndMutation(&c);
	}
	else
		cout << "User canceled setup!\n";
}

void testPythonLib(void)
{
	PythonLib c;
	string _choice;
	cout << "setting up a python...\n";
	if (c.setup()){
		cout << '\n' << c << "\n\n";
		testPolymorphismAndMutation(&c);
	}
	else
		cout << "User canceled setup!\n";
}

int main(void)
{
	string choice;
	while (true){
		cout << "test {m}oderncpp, {p}ythonlib, or {s}tl? {!q} to quit: ";
		getline(cin, choice);
		if		(choice == "m")
			testModernCpp();
		else if (choice == "p")
			testPythonLib();
		else if (choice == "s")
			testSTL();
		else if (choice == "!q")
			break;
		else{
			cout << "Bad input! This is my one chance to not handle it and just let you deal with it\n"
				 << "muahahahaha better luck next time! Now exiting...\n\n\njk\n";
		}
	}
	return 0;
}
