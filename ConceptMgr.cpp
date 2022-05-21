#include "ConceptMgr.h"

/*	Amelia Miner				5/20/2022
 *	cs202, section 003
 *	FILE:		ConceptMgr.cpp
 *	PURPOSE:	Defines a main class that uses an RBT to store and manage
 * concept objects. Supports insert, display, remove_all, find by name,
 * editing of concepts by name, etc.
 *	Removal is not supported by the tree (spec says not needed if tree is
 * self balancing), but is fully implemented up to the Node level such that
 * all that must be done to get it working should be writing
 * RBT::remove_data, RBT::remove_node, and RBT::fix_remove, the first 2 of
 * which should be identical to BST::remove behaviors.
 *	I desparately want to use system("clear") here, but graders may
 * be using windows... shame on them! Just kidding please don't fail me.
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
void ConceptMgr::test(void) //debug
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

	cout << "DEBUG: Adding some concepts...\n";
	add_concept(&a);
	add_concept(&b);
	add_concept(&c);
	add_concept(&d);
	add_concept(&e);
	add_concept(&f);
	main_loop();		//edit as needed
}
void ConceptMgr::add_concept(Concept* new_c) //debug
{
	if		(auto s = dynamic_cast<STL*>(new_c); s)
		tree.insert(*s);
	else if	(auto p = dynamic_cast<PythonLib*>(new_c); p)
		tree.insert(*p);
	else if	(auto m = dynamic_cast<ModernCpp*>(new_c); m)
		tree.insert(*m);
	else //uhoh
		throw out_of_range("Dynamic cast failure!"); //should never happen
}

//UI
void ConceptMgr::main_loop(bool cont, string _choice)
{
	if (cont){ //guards entire function
	cout << "\n/|\\|/~*Digital Rolodex*~/|\\|/\n" << tree << '\n';
	cout << "Would you like to...\n"
		 << "{a}dd a concept to the program,\n"
		 << "{e}dit a concept in the program,\n"
		 //<< "{r}emove a concept from the program,\n"
		 //<< "{rem}ove a topic from the program,\n"
		 << "{exp}and a topic by name,\n"
		 << "{col}lapse a topic by name,\n"
		 << "{l}ookup & expand all concepts containing a keyword,\n"
		 << "{s}elect a website, or\n"
		 << "{!q} to exit?\n: ";
	try{
		_choice = get_string(1); //may throw invalid
		if (_choice == "a")
			add_concept();
		else if (_choice == "e")
			edit_concept();
		//else if (_choice == "r")		//not required by spec
			//remove_concept();
		//else if (_choice == "rem")	//not required by spec
			//remove_topic();
		else if (_choice == "exp")
			expand_topic();
		else if (_choice == "col")
			collapse_topic();
		else if (_choice == "l")
			lookup();
		else if (_choice == "s")
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
	return;
}

void ConceptMgr::edit_concept(void)
{
	string _choice {""};
	string _choice2 {""};
	Concept* to_edit {nullptr};
	cout << "Which class or modernCppwould you like to edit?\n"
		 << "{Enter a topic name, or !q to cancel}: ";
	try{
		_choice = get_string(2);
		to_edit = find_concept(true, _choice, "");
		/* find_concept implemented
		cout << "Specify a concept type, or leave blank to match any type\n"
			 << "{python} class, {stl} class, modern {c++} concept name,\n"
			 << "or {!q} to cancel: ";
		_choice2 = get_string(0);
		if (_choice2 == "")
			to_edit = tree.find<Concept>(_choice); //null if not in tree
		else if (_choice2 == "python")
			to_edit = tree.find<PythonLib>(_choice); //null if not in tree
		else if (_choice2 == "stl")
			to_edit = tree.find<STL>(_choice); //null if not in tree
		else if (_choice2 == "c++")
			to_edit = tree.find<ModernCpp>(_choice); //null if not in tree
		else
			throw invalid_argument(_choice); //redo?
		*/

		if (to_edit)
			edit_or_add(to_edit);
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		edit_concept();
	}

	catch (const char*& user_cancels){
		;
	}

	return;
}
//MUST NOT BE CALLED WITH NULL
void ConceptMgr::edit_or_add(Concept* to_edit)
{
	string _choice = "";
	cout << "Do you want to {edit} or {rem}ove existing info, or {add} new info?\n"
		 << "{!q} to cancel: ";
	try{
		_choice = get_string(2); //thrown !q would be caught in Mgr::edit_concept()
		if (_choice == "edit")
			to_edit->edit();
		else if (_choice == "add")
			to_edit->add();
		else if (_choice == "rem")
			to_edit->remove();
		else
			throw invalid_argument(_choice);
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		edit_or_add(to_edit);
	}
}

/*
void ConceptMgr::remove_topic(void)
{
	//todo not required
}
*/

/*
void ConceptMgr::remove_concept(void)
{
	//todo not required
}
*/

void ConceptMgr::select_site(void)
{
	string _choice {""};
	string _choice2 {""};
	Concept* to_select {nullptr};
	cout << "Which class or modernCppwould you like to select a site from?\n"
		 << "{Enter a topic name, or !q to cancel}: ";
	try{
		_choice = get_string(2);
		to_select = find_concept(true, _choice, "");
		/* find_concept implemented
		cout << "Specify a concept type, or leave blank to match any type\n"
			 << "{python} class, {stl} class, modern {c++} concept name,\n"
			 << "or {!q} to cancel: ";
		_choice2 = get_string(0);
		if (_choice2 == "")
			to_edit = tree.find<Concept>(_choice); //null if not in tree
		else if (_choice2 == "python")
			to_edit = tree.find<PythonLib>(_choice); //null if not in tree
		else if (_choice2 == "stl")
			to_edit = tree.find<STL>(_choice); //null if not in tree
		else if (_choice2 == "c++")
			to_edit = tree.find<ModernCpp>(_choice); //null if not in tree
		else
			throw invalid_argument(_choice); //redo?
		*/

		if (to_select)
			to_select->select_site();
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		select_site();
	}

	catch (const char*& user_cancels){
		;
	}

	return;
}

void ConceptMgr::expand_topic(void)
{
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
	return;
}

void ConceptMgr::collapse_topic(void)
{
	string _choice {""};
	Node* to_collapse {nullptr};
	cout << "Which topic would you like to collapse?\n"
		 << "Enter a topic name, or {all}, or {!q} to cancel: ";
	try{
		_choice = get_string(2);
		if (_choice == "all")
			tree.collapse_all();
		else{
			to_collapse = tree.find_node(_choice); //null if not in tree
			if (to_collapse)
				to_collapse->collapse();
			else
				throw invalid_argument(_choice); //redo?
		}
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		collapse_topic();
	}

	catch (const char*& user_quits){
		;
	}
	return;
}

Concept* ConceptMgr::find_concept(bool print, string _choice, string _choice2)
{
	Concept* to_select {nullptr};
	try{ //guards entire function
	if (print){
			if (_choice == ""){
				cout << "Which class or modernCppwould you like to find?\n"
					 << "{Enter a topic name, or !q to cancel}: ";
				_choice = get_string(2);
			}
			cout << "Specify a concept type, or leave blank to match any type\n"
				 << "{python} class, {stl} class, modern {c++} concept name,\n"
				 << "or {!q} to cancel: ";
			_choice2 = get_string(0);
	}
	if (_choice2 == "")
		to_select = tree.find<Concept>(_choice); //null if not in tree
	else if (_choice2 == "python")
		to_select = tree.find<PythonLib>(_choice); //null if not in tree
	else if (_choice2 == "stl")
		to_select = tree.find<STL>(_choice); //null if not in tree
	else if (_choice2 == "c++")
		to_select = tree.find<ModernCpp>(_choice); //null if not in tree
	else
		throw invalid_argument(_choice); //redo?
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		find_concept(true, _choice, ""); //won't return until cancel or good input
	}

	catch (const char*& user_cancels){
		return nullptr;
	}

	return to_select;
}

//search by keyword
void ConceptMgr::lookup(void)
{
	string _choice {""};
	cout << "Enter a keyword to expand all topics with concepts\n"
		 << "containing the keyword in any of their info\n"
		 << "{or !q to cancel}: ";
	try{
		_choice = get_string(2);
		tree.expand_matches(_choice);
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		lookup();
	}

	catch (const char*& user_cancels){
		;
	}

}

int main(void)
{
	//ConceptMgr application;		//user mode
	ConceptMgr application(true);	//debug mode
}
