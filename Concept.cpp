#include "Concept.h"

/*	Amelia Miner				5/14/2022
 *	cs202, section 003
 *	FILE:		Concept.cpp
 *	PURPOSE:	Define the central hierarchy for the program,
 *			one base class Concept and three derived classes Library,
 *			PythonLib, and ModernCpp. Subclasses generally call the base
 *			version of their method before following it up with their own
 *			behavior based on derived needs.
 */

/*			CLASS CONCEPT			*/

Concept::Concept(void)
	: name("NOT SET"), description("NOT SET") {}

Concept::Concept(string key_name)
	: name(key_name), description("NOT SET (key)") {}

bool Concept::operator==(const Concept& op2) const
{
	return name == op2.name;
}

bool Concept::operator<(const Concept& op2) const
{
	return name < op2.name;
}

ostream& operator<<(ostream& out, const Concept& op2)
{
	op2.display(out);
	return out;
}

/*	PUBLIC METHODS	*/

//TODO remove after testing
string& Concept::get_name(void)
{
	return name;
}

//TODO remove after testing
void Concept::set_name(string n)
{
	name = n;
}

//should only be called after a concept has been displayed
void Concept::select_site(void)	const //demanded by spec for some reason
{
	int _choice {-2};
	cout << "Which website would you like to select,\n"
		 << " by its number? {-1 to cancel}: ";
	try{
		_choice = get_int(1, websites.size());
		//very inefficient to iterate over a set... but we need ordered unique
		cout << "Selected:\n" << next(websites.begin(), _choice-1)->get_url()
			 << '\n';
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		select_site();
	}

	catch (const char*& user_cancels){ //user entered !q
		;
	}

	return;
}

void Concept::display(ostream& out) const
{
	//this is a rough draft for testing
	size_t count = 0;
	if (! (name == "stl globals" or name == "python globals"))
		out << name;
	out << "~~~*/\n/*~Description~*/\n"
		<< description << "\n/*~Websites~*/";
	if (websites.size() == 0)
		cout << "\nNo websites...";
	else{
		for (const Website& w: websites){
			out << '\n' << ++count << ": " << w;
		}
	}
}

bool Concept::setup(bool name_set, bool desc_set, bool site_added)
{
	bool ret {true};
	try{
		if (! name_set){
			set_name();
			name_set = true;
		}
		if (! desc_set){
			set_description();
			desc_set = true;
		}
		if (! site_added){
			add_site();
			site_added = true;
		}
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		return setup(name_set, desc_set); //setup must be completed
	}

	/* concept is never instantiated, catch this in derived class;best option?
	catch (const char*& user_cancels){								//todo
		//not strictly necessary... but useful info for debugging
		//should I let the program be run with a -g flag? vargs easy to set up
		*this = Concept(); //reset and return
		ret = false;
	}
	*/ //catch in derived

	return ret;
}

void Concept::add(string _choice)
{
	try{
		if (_choice == ""){
			cout << "Would you like to add a {website}, or an{other} piece of "
				 << "info?\n{!q} to cancel: ";
			_choice = get_string(2); //may throw char*; caught in derived
		}
		if 		(_choice == "website")
			add_site();
		else if (_choice == "other")
			throw out_of_range("User adds derived!"); //caught in derived
		else{
			disp_invalid_input(_choice);
			add();
		}
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		add();
	}

	return;
}

void Concept::edit(string _choice)
{
	try{
		if (_choice == ""){
			cout << "Would you like to edit the"
				 << " {name}, {description}, a {website},"
				 << " or an{other} attribute?\n{!q} to cancel: ";
			_choice = get_string(2); //may throw char*; caught in derived
		}
		if		(_choice == "name")
			set_name();
		else if (_choice == "description")
			set_description();
		else if (_choice == "website")
			edit_site();
		else if (_choice == "other")
			throw out_of_range("User edits derived!"); //edit outside of base
		else{
			disp_invalid_input(_choice);
			edit();
		}
	}

	catch (const invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		edit(_choice);
	}

	/* catch in derived; could change, is this the best way? todo
	catch (const char*& user_cancels){ //user entered !q
		throw user_cancels; //throw again to inform derived method of cancel
							//since base::edit should only be called
							//from derived::edit... should this just be caught
							//in derived::edit? ...Yes
	}
	*/

	return;
}

void Concept::remove(string _choice)
{
	try{
		if (_choice == ""){
			cout << "Would you like to remove a {website}, or an{other} piece of "
				 << "info?\n{!q} to cancel: ";
			_choice = get_string(2); //may throw char* - caught in derived
		}
		if 		(_choice == "website")
			remove_site();
		else if (_choice == "other")
			throw out_of_range("User removes derived!"); //caught in derived
		else{
			disp_invalid_input(_choice);
			remove();
		}
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		remove();
	}

	return;
}

/*	PRIVATE METHODS	*/

void Concept::set_name(void)
{
	cout << "Enter a name or {!q} to cancel: ";
	name = get_string(1);		//may throw
}

void Concept::set_description(void)
{
	cout << "Enter a description or {!q} to cancel: ";
	description = get_string(1);	//may throw
}

void Concept::remove_site(void)
{
	string _choice;
	set<Website>::iterator to_rem {websites.begin()}; //set->const iterator
	bool match {false};
	switch (websites.size()){
		case 0:
			cout << "No websites to remove!\n";
			break;
		case 1:
			cout << "Removing \"" << to_rem->get_url() << "\"...\n";
			websites.erase(to_rem);
			break;
		default:
			cout << "Which website would you like to remove? {!q to cancel}: ";
			try{
				_choice = get_string(2);
				for (const Website& w: websites){
					if (w == _choice){
						match = true;
						websites.erase(to_rem);
						break; //is this ok?
					}
					else
						advance(to_rem, 1);
				}
				if (!match){
					cout << "No such website!\n";
					remove_site();
				}
			}

			catch (invalid_argument& bad_input){
				disp_invalid_input((string) bad_input.what());
				cout << "Please try again.\n";
				remove_site();
			}

			break;
	}
	return;
}

void Concept::add_site(void)
{
	Website new_site;
	if (new_site.setup())
		websites.insert(new_site);
	else //user cancelled
		throw "User cancels!";
}

void Concept::edit_site(void)
{
	string _choice;
	set<Website>::iterator to_edit {websites.begin()}; //set->const iterator
	Website new_site;				//enables editing by reinserting edited
	bool match {false};
	switch (websites.size()){
		case 0:
			cout << "No websites to edit!\n";
			break;
		case 1:
			cout << "Editing \"" << to_edit->get_url() << "\"...\n";
			new_site = *to_edit;
			new_site.edit(); //if user cancels, execution proceeds w/o edits...
			websites.erase(to_edit);
			websites.insert(new_site);
			break;
		default:
			cout << "Which website would you like to edit? {!q to cancel}: ";
			try{
				_choice = get_string(2);
				for (const Website& w: websites){
					if (w == _choice){
						match = true;
						new_site = w;
						new_site.edit(); //if user cancels,
						websites.erase(to_edit);
						websites.insert(new_site);
						break; //is this ok?
					}
					else
						advance(to_edit, 1);
				}
				if (!match){
					cout << "No such website!\n";
					edit_site();
				}
			}

			catch (invalid_argument& bad_input){
				disp_invalid_input((string) bad_input.what());
				cout << "Please try again.\n";
				edit_site();
			}

			break;
	}
	return;
}

/*			CLASS LIBRARY			*/

/*	PUBLIC METHODS	*/

void Library::display(ostream& out) const
{
	//this is a rough draft for testing
	size_t count {0};
	//if (! dynamic_cast<const PythonLib*>(this)) //rm bc new inheritance
	//	out << "/*~~~Library concept ";
	Concept::display(out); //name, desc, websites handled here
	out << "\n/*~Methods~*/";//go on to handle derived
	if (methods.size() == 0)	//todo may want Library::display_meths subrtn
		out << "\nNo methods...";  //...can I just cout << set ?
	else{
		for (const Method& m: methods){
			out << '\n' << ++count << ": " << m;
		}
	}
}

bool Library::setup(bool base_set_up, bool method_added)
{
	bool ret {true};
	try{
		if (! base_set_up){
			//if (! dynamic_cast<const PythonLib*>(this)) //rm bc new inheritance
			//	cout << "Setting up a new STL...\n"; //testing, will refine 
			cout << "For the class of the library to which these methods\n"
				 << "will belong, unless these methods are global to the\n"
				 << "library in which case enter \"global\",\n";
			ret = Concept::setup();			//worst prompt I've ever written
			base_set_up = true;
		}
		if (! method_added){
			add_method();
			method_added = true;
		}
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		return setup(base_set_up, method_added); //setup must be completed
	}

	catch (const char*& user_cancels){
		//not strictly necessary... but useful info for debugging
		//should I let the program be run with a -g flag? vargs easy to set up
		*this = Library(); //reset and return
		ret = false;
		//if (! dynamic_cast<const PythonLib*>(this)) //rm bc new inheritance
		//	throw "User cancels!"; //caught in PythonLib::setup
	}

	return ret;
}

void Library::edit(string _choice)
{
	try{
		Concept::edit(); //if this returns w/ no throws, user edited base
	}

	catch (out_of_range& user_edits_derived){ //case user wants to edit derived
		edit_library(); //call to derived edit function goes here
	}

	catch (const char*& user_cancels){ //user entered !q
		; 
	}

	return;
}

void Library::add(string _choice)
{
	try{
		Concept::add(); //if this returns w/ no throws, user added to base
	}

	catch (out_of_range& user_adds_derived){ //case user wants to add derived
		add_library();
	}

	catch (const char*& user_cancels){ //user entered !q
		;
	}

	return;
}

void Library::remove(string _choice)
{
	try{
		Concept::remove(); //if this returns w/ no throws, user removed base
	}

	catch (out_of_range& user_edits_derived){ //case remove derived
		remove_library(); //call to derived remove function goes here
	}

	catch (const char*& user_cancels){ //user entered !q
		; 
	}

	return;
}

bool Library::contains(const string& key) const
{
	bool ret {false};
	if (name.find(key) != string::npos
	 or description.find(key) != string::npos)
		ret = true;
	else if (!ret){
		for (const Website& w: websites){
			if (w.get_url().find(key) != string::npos
			 or w.get_desc().find(key) != string::npos){
				ret = true;
				break;
			}
		}
	}
	else{
		for (const Method& m: methods){
			if (m.get_name().find(key) != string::npos
			 or m.get_desc().find(key) != string::npos){
				ret = true;
				break; //is this ok to use here?
			}
		}
	}
	return ret;
}

/*	PRIVATE METHODS	*/

//Kept in design for maintainability and uniformity
void Library::add_library(void)
{
	add_method(); //no need to do UI things since there is only one option
	return;
}

//Kept in design for maintainability and uniformity
void Library::edit_library(void)
{
	edit_method(); //no need to do UI things since there is only one option
	return;
}

void Library::remove_library(void)
{
	remove_method(); //no need to do UI things since there is only one option
	return;
}

void Library::add_method(void)
{
	Method new_method;
	if (new_method.setup())
		methods.insert(new_method);
	else //user cancelled
		; //char* will be caught in add()
	return;
}

void Library::edit_method(void)
{
	string _choice;
	set<Method>::iterator to_edit {methods.begin()}; //set->const iterator
	Method new_method;
	bool match {false};
	switch (methods.size()){
		case 0:
			cout << "No methods to edit!\n";
			break;
		case 1:
			cout << "Editing \"" << to_edit->get_name() << "\"...\n";
			new_method = *to_edit;
			new_method.edit(); //may throw char* cancel, caught in edit_library &&
			methods.erase(to_edit); //execution returns with pre-erase state
			methods.insert(new_method);
			break;
		default:
			cout << "Which method would you like to edit? {!q to cancel}: ";
			try{
				_choice = get_string(1);
				for (const Method& m: methods){
					if (m == _choice){
						match = true;
						new_method = m;
						new_method.edit(); //may throw cancel, caught in edit_library &&
						methods.erase(to_edit); //execution returns pre-erase
						methods.insert(new_method);
						break; //no need to examine rest of set - is this ok?
					}
					else{
						advance(to_edit, 1);
					}
				}
				if (!match){
					cout << "No such method!\n";
					edit_method();
				}
				break;
			}

			catch (invalid_argument& bad_input){
				disp_invalid_input((string) bad_input.what());
				cout << "Please try again.\n";
				edit_method();
			}
	}
	return;
}

void Library::remove_method(void)
{
	string _choice;
	set<Method>::iterator to_rem {methods.begin()}; //set->const iterator
	bool match {false};
	switch (methods.size()){
		case 0:
			cout << "No methods to remove!\n";
			break;
		case 1:
			cout << "Removing \"" << to_rem->get_name() << "\"...\n";
			methods.erase(to_rem);
			break;
		default:
			cout << "Which method would you like to remove? {!q to cancel}: ";
			try{
				_choice = get_string(1);
				for (const Method& m: methods){
					if (m == _choice){
						match = true;
						methods.erase(to_rem);
						break; //is this ok?
					}
					else
						advance(to_rem, 1);
				}
				if (!match){
					cout << "No such method!\n";
					remove_method();
				}
				break;
			}

			catch (invalid_argument& bad_input){
				disp_invalid_input((string) bad_input.what());
				cout << "Please try again.\n";
				remove_method();
			}

	}
	return;
}

/*			CLASS STL			*/

bool STL::setup(void)
{
	bool ret {true};
	ret = Library::setup();
	if (name == "global")
		name = "stl globals";
	return ret;
}

void STL::display(ostream& out) const    //"polymorphic" op<<
{
	//this is a rough draft for testing
	if (name == "stl globals")
		out << "/*~~~Global STL Methods";
	else
		out << "/*~~~STL Methods belonging to std::";
	Library::display(out); //name, desc, websites, methods handled here
	cout << '\n';
}

//Many standard library classes share similar interfaces;
//this allows us to define a generic set of methods and then copy it
//into new libraries instead of entering those generic methods each time
void STL::copy_methods(const STL& to_copy_from)
{
	for (Method m: to_copy_from.methods){
		methods.insert(m);
	}
}

/*			CLASS PYTHONLIB			*/

/* //not sure about this, prob not a good move for use in tree-by-name
bool PythonLib::operator==(const PythonLib& op2) const
{
	return (name == op2.name and class_name == op2.class_name);
}
*/

PythonLib::PythonLib(void)
	: Library(), lib_name("NOT SET") {}

bool PythonLib::operator<(const PythonLib& op2) const
{
	return (lib_name < op2.lib_name);
}

/*	PUBLIC METHODS	*/

void PythonLib::display(ostream& out) const
{
	//this is a rough draft for testing
	if (name == "python globals")
		out << "/*~~~Python Methods Global to " << lib_name;
	else
		cout << "/*~~~Python Library Methods of " << lib_name << " in class ";
	Library::display(out); //name, desc, websites, methods handled here
	cout << '\n';
}

bool PythonLib::setup(bool base_set_up, bool lib_name_set, bool method_added)
{
	bool ret {true};
	try{
		if (!lib_name_set){
			set_lib_name();
			lib_name_set = true;
		}
		if (! base_set_up){
			ret = Library::setup();
			if (name == "global")
				name = "python globals";
			base_set_up = true;
		}
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		return setup(base_set_up, lib_name_set, method_added); //finish setup
	}

	catch (const char*& user_cancels){
		//not strictly necessary... but useful info for debugging
		//should I let the program be run with a -g flag? vargs easy to set up
		*this = PythonLib(); //reset and return
		ret = false;
	}

	return ret;
}

void PythonLib::edit(string _choice)
{
	try{
		Concept::edit(); //if this returns w/ no throws, user edited base
	}

	catch (out_of_range& user_edits_derived){ //case user wants to edit derived
		edit_pythonlib(); //call to derived edit function goes here
	}

	catch (const char*& user_cancels){ //user entered !q
		; 
	}

	return;
}

bool PythonLib::contains(const string& key) const
{
	bool ret {false};
	if (name.find(key)			!= string::npos
	 or description.find(key)	!= string::npos
	 or lib_name.find(key)		!= string::npos)
		ret = true;
	else if (!ret){
		for (const Website& w: websites){
			if (w.get_url().find(key) != string::npos
			 or w.get_desc().find(key) != string::npos){
				ret = true;
				break;
			}
		}
	}
	else{
		for (const Method& m: methods){
			if (m.get_name().find(key) != string::npos){
				ret = true;
				break; //is this ok to use here?
			}
		}
	}
	return ret;
}

//	Returns whether class name is anything but "global" value (set to
//the string "python globals" by setup)
//	std::map tracks each PythonLib::name and maps it to a boolean set by
//calls to each PyLib::is_o_o inside ConceptManager. Allows user to see
//which libraries are purely OO... not my favorite but it works... todo
bool PythonLib::is_object_oriented(void)
{
	bool ret {true};
	if (name == "python globals")
		ret = false;
	return ret;
}

/*	PRIVATE METHODS	*/
void PythonLib::set_lib_name(void)
{
	cout << "Enter a library name, or {!q} to cancel: ";
	lib_name = get_string(1);		//may throw
}

void PythonLib::edit_pythonlib(string _choice)
{
	try{
		if (_choice == ""){
			cout << "Would you like to edit the"
				 << " {library} name or a {method}?\n{!q} to cancel: ";
			_choice = get_string(2);
		}
		if		(_choice == "library")
			set_lib_name();
		else if (_choice == "method")
			edit_method();
		else{
			disp_invalid_input(_choice);
			edit_pythonlib();
		}
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		edit_pythonlib();
	}

	catch (const char*& user_cancels){
		;
	}

	return;
}


/*			CLASS MODERNCPP			*/

ModernCpp::ModernCpp(void)
	: Concept() {}

ModernCpp::ModernCpp(string key_name)
	: Concept(key_name) {}

/*	PUBLIC METHODS	*/

void ModernCpp::display(ostream& out) const
{
	//this is a rough draft for testing
	size_t count {0};
	out << "/*~~~Modern C++ technique: ";
	Concept::display(out); //name, desc, websites handled here
	out << "\n/*~Pros~*/";//go on to handle derived
	if (pros.size() == 0)
		out << "\nNo pros...";
	else{
		for (const string& s: pros){
			out << '\n' << ++count << ": " << s;
		}
	}
	out << "\n/*~Cons~*/";//go on to handle derived
	if (cons.size() == 0)	//todo may want Library::display_meths subrtn
		out << "\nNo cons...";  //...can I just cout << set ?
	else{
		for (const string& s: cons){
			out << '\n' << ++count << ": " << s;
		}
		count = 0;
	}
	cout << '\n';
}

bool ModernCpp::setup(bool base_set_up, bool pro_or_con_added)	   //set/add
{
	bool ret {true};
	try{
		if (! base_set_up){
			cout << "For the modern programming c++ technique,\n";
			ret = Concept::setup();
			base_set_up = true;
		}
		if (!pro_or_con_added){
			add_pro_or_con();
			pro_or_con_added = true;
		}
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		return setup(base_set_up, pro_or_con_added); //finish setup
	}

	catch (const char*& user_cancels){
		//not strictly necessary... but useful info for debugging
		//should I let the program be run with a -g flag? vargs easy to set up
		*this = ModernCpp(); //reset and return
		ret = false;
	}

	return ret;
}

void ModernCpp::add(string _choice)						//add pro or con
{
	try{
		Concept::add(); //if this returns w/ no throws, user added to base
	}

	catch (out_of_range& user_adds_derived){ //case user wants to add derived
		add_moderncpp();
	}

	catch (const char*& user_cancels){ //user entered !q
		;
	}

	return;
}

void ModernCpp::edit(string _choice)					   //edit pro or con
{
	try{
		Concept::edit(); //if this returns w/ no throws, user edited base
	}

	catch (out_of_range& user_edits_derived){ //case user wants to edit derived
		edit_moderncpp(); //call to derived edit function goes here
	}

	catch (const char*& user_cancels){ //user entered !q
		; 
	}

	return;
}

void ModernCpp::remove(string _choice)					 //remove pro or con
{
	try{
		Concept::remove(); //if this returns w/ no throws, user removed base
	}

	catch (out_of_range& user_edits_derived){ //case remove derived
		remove_moderncpp(); //call to derived remove function goes here
	}

	catch (const char*& user_cancels){ //user entered !q
		; 
	}

	return;
}


bool ModernCpp::contains(const string& key) const
{
	bool ret {false};
	if (name.find(key) != string::npos				//check name
	 or description.find(key) != string::npos)		//and desc
		ret = true;
	else if (!ret){
		for (const Website& w: websites){
			if (w.get_url().find(key) != string::npos
			 or w.get_desc().find(key) != string::npos){
				ret = true;
				break;
			}
		}
	}
	else{											//check pros
		for (const string& s: pros){
			if (s.find(key) != string::npos){
				ret = true;
				break; //is this ok to use here?
			}
		}
		if (!ret){
			for (const string& s: cons){			//check cons
				if (s.find(key) != string::npos){
					ret = true;
					break; //is this ok to use here?
				}
			}
		}
	}
	return ret;
}

//returns pros and cons relevant to a keyword, concatenated
string ModernCpp::check_applicability(string key) //cats partial matches
{
	string ret = "\n";
	bool no_pros = true, no_cons = true;
	try{
		cout << "Enter a keyword to check pros and cons for: ";
		key = get_string(1);
		for (const string& s: pros){
			if (s.find(key) != string::npos){
				if (no_pros){
					ret += "! Pros:\n";
					no_pros = false;
				}
				ret += (s + '\n');
			}
		}
		for (const string& s: cons){
			if (s.find(key) != string::npos){
				if (no_cons){
					ret += "! Cons:\n";
					no_cons = false;
				}
				ret += (s + '\n');
			}
		}
		if (no_pros and no_cons)
			ret += "No relevant pros or cons found";
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		return check_applicability();
	}

	catch (const char*& user_cancels){ //user entered !q
		;
	}

	return ret;
}

/*	PRIVATE METHODS	*/

void ModernCpp::add_moderncpp(void)
{
	add_pro_or_con(); //no need to do UI things, only one option
	return;
}

void ModernCpp::edit_moderncpp(void)
{
	edit_pro_or_con(); //no need to do UI things since there is only one option
	return;
}

void ModernCpp::remove_moderncpp(void)
{
	remove_pro_or_con(); //no need to do UI, only one option for now
}

void ModernCpp::add_pro_or_con(void)
{
	string _choice;
	string _new_item; //stores new pro or con for insertion
	cout << "Would you like to add a {pro} or a {con}? {!q to cancel}: ";
	try{
		_choice = get_string(2,3);
		if (_choice != "pro" and _choice != "con"){
			disp_invalid_input(_choice);
			add_pro_or_con();
			return;
		}
		else{
			cout << "Enter the " << _choice << ": ";
			_new_item = get_string(1);
			if (_choice == "pro")
				pros.insert(_new_item);
			else
				cons.insert(_new_item);
		}
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		add_pro_or_con();
	}

	catch (const char*& user_cancels){ //user entered !q
		;
	}

	return;
}

void ModernCpp::edit_pro_or_con(void)
{
	int _choice {-2};
	string _new_item;
	if (pros.empty() and cons.empty())
		cout << "No pros or cons to edit!\n";
	else{
		cout << "Which pro or con would you like to edit,\n"
			 << " by its number? {-1 to cancel}: ";
		try{
			_choice = get_int(1, pros.size() + cons.size());
			if ((size_t)_choice <= pros.size()){
				cout << "Enter the pro's new contents: ";
				_new_item = get_string(1);
				pros.erase(next(pros.begin(), _choice-1));
				pros.insert(_new_item);
			}
			else{
				_choice -= pros.size();
				cout << "Enter the con's new contents: ";
				_new_item = get_string(1);
				cons.erase(next(cons.begin(), _choice-1));
				cons.insert(_new_item);
			}
		}

		catch (invalid_argument& bad_input){
			disp_invalid_input((string) bad_input.what());
			cout << "Please try again.\n";
			edit_pro_or_con();
		}

		catch (const char*& user_cancels){ //user entered !q
			;
		}
	}

	return;
}

void ModernCpp::remove_pro_or_con(void)
{
	int _choice {-2};
	string _new_item;
	if (pros.empty() and cons.empty())
		cout << "No pros or cons to remove!\n";
	else{
		cout << "Which pro or con would you like to remove,\n"
			 << " by its number? {-1 to cancel}: ";
		try{
			_choice = get_int(1, pros.size() + cons.size());
			if ((size_t)_choice <= pros.size()){
				pros.erase(next(pros.begin(), _choice-1));
			}
			else{
				_choice -= pros.size();
				cons.erase(next(cons.begin(), _choice-1));
			}
		}

		catch (invalid_argument& bad_input){
			disp_invalid_input((string) bad_input.what());
			cout << "Please try again.\n";
			remove_pro_or_con();
		}

		catch (const char*& user_cancels){ //user entered !q
			;
		}
	}

	return;
}
