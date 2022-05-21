#include "ConceptMgr.h"

/*	Amelia Miner				5/20/2022
 *	cs202, section 003
 *	FILE:		ConceptMgr.cpp
 *	PURPOSE:	Defines a main class that uses an RBT to store and manage
 * concept objects. Supports insert, display, remove_all, find by name,
 * editing and removal of concepts by name, etc TODO
 */

ConceptMgr::ConceptMgr(bool debug)	//main loop
{
	cout << "\nWelcome to Concept Rolodex Under Nigh Catastrophic Hijinx!\n";
	if (debug)
		test();
	else
		main_loop();
	cout << "\nThanks for stopping by!\n";
}
void ConceptMgr::test(void)
{
	STL			a, d, g;
	PythonLib	b, e, h;
	ModernCpp	c, f, i;

	a.set_name("vector");
	b.set_name("dataframe");
	c.set_name("templates");			//name field set with
	d.set_name("stl globals");		//<--result of user entering "global"
	e.set_name("python globals");	//<--result of user entering "global"
	f.set_name("OOP");

	cout << "\n/|\\|/~*Digital Rolodex*~/|\\|/\n" << tree << "\n";
	cout << "DEBUG: Adding some concepts...\n";
	add_concept(&a);
	add_concept(&b);
	add_concept(&c);
	add_concept(&d);
	add_concept(&e);
	add_concept(&f);
	main_loop();
	//remove_concept();
	//remove_topic();
	//TODO etc tests
}
void ConceptMgr::add_concept(Concept* new_c)
{
	if		(auto s = dynamic_cast<STL*>(new_c); s)
		tree.insert(*s);
	else if	(auto p = dynamic_cast<PythonLib*>(new_c); p)
		tree.insert(*p);
	else if	(auto m = dynamic_cast<ModernCpp*>(new_c); m)
		tree.insert(*m);
	else //uhoh
		throw out_of_range("Dynamic cast failure!"); //should never see this happen
}

//UI
void ConceptMgr::main_loop(bool cont, string _choice)
{
	//TODO
	if (cont){ //guards entire function
	cout << "\n/|\\|/~*Digital Rolodex*~/|\\|/\n" << tree << '\n';
	cout << "Would you like to...\n"
		 << "{a}dd a concept to the program,\n"
		 << "{e}dit a concept in the program,\n"
		 << "{rem}ove a concept from the program,\n"
		 << "{remove} a topic from the program,\n"
		 << "{exp}and a topic by name,\n"
		 << "{col}lapse a topic by name,\n"
		 << "{look}up a concept by keyword/type,\n"
		 << "{sel}ect a website, or\n"
		 << "{!q} to exit?\n: ";
	try{
		_choice = get_string(1); //may throw invalid
		if (_choice == "a")
			add_concept();
		else if (_choice == "e")
			edit_concept();
		else if (_choice == "rem")
			remove_concept();
		else if (_choice == "remove")
			remove_topic();
		else if (_choice == "exp")
			expand_topic();
		else if (_choice == "col")
			collapse_topic();
		else if (_choice == "look")
			lookup();
		else if (_choice == "sel")
			select_site();
		else
			throw invalid_argument(_choice);
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
	}

	catch (const char*& user_quits){
		cont = false; //this could cause some erroneous exits if I have a hole in exception handling...
	}

	cout << '\n';
	main_loop(cont); //recursive call after catch or complete subroutine call

	}//end if (cont)
	return;
}

void ConceptMgr::add_concept(void)
{
	//TODO test
	string _choice;
	STL _new_s;
	PythonLib _new_p;
	ModernCpp _new_m;
	cout << "What type of concept would you like to add?\n{stl} class/methods,"
		 << " a {py}thon library, or a modern {c++} technique?\n{!q} to cancel: ";
	try{
		_choice = get_string(2);
		if (_choice == "stl"){
			if (_new_s.setup())
				tree.insert(_new_s);
			else
				cout << "Addition canceled!\n";
		}
		else if (_choice == "py"){
			if (_new_p.setup())
				tree.insert(_new_p);
			else
				cout << "Addition canceled!\n";
		}
		else if (_choice == "c++"){
			if (_new_m.setup())
				tree.insert(_new_m);
			else
				cout << "Addition canceled!\n";
		}
		else{
			throw invalid_argument(_choice);
		}
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		add_concept();
	}

	catch (const char*& user_cancels){
		;
	}
}

void ConceptMgr::edit_concept(void)
{
	//TODO
}

void ConceptMgr::remove_topic(void)
{
	//TODO
}

void ConceptMgr::remove_concept(void)
{
	//TODO
}

void ConceptMgr::select_site(void)
{
	//TODO
}

void ConceptMgr::expand_topic(void)
{
	//TODO
	string _choice {""};
	Node* to_expand {nullptr};
	cout << "Which topic would you like to expand?\n"
		 << "{Enter a topic name, or !q to cancel}: ";
	try{
		_choice = get_string(2);
		to_expand = tree.find_node(_choice); //null if not in tree
		if (to_expand)
			to_expand->expand();
		else
			throw invalid_argument(_choice); //redo?
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		expand_topic();
	}

	catch (const char*& user_quits){
		;
	}

}

void ConceptMgr::collapse_topic(void)
{
	//TODO
}

void ConceptMgr::lookup(void)
{
	//TODO
}

//template<typename T> void ConceptMgr::lookup_by_type<T>(void) {} //TODO tpp

int main(void)
{
	//ConceptMgr application;
	ConceptMgr application(true);
}










