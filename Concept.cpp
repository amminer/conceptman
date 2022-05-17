#include "Concept.h"

/*	Amelia Miner				5/14/2022
 *	cs202, section 003
 *	FILE:		Concept.cpp
 *	PURPOSE:	Define the central hierarchy for the program,
 *			one base class Concept and three derived classes STL,
 *			PythonLib, and ModernCpp. Subclasses generally call the base
 *			version of their method before following it up with their own
 *			behavior based on derived needs.
 */


/*			CLASS CONCEPT			*/

Concept::Concept(void)
	: name("NOT SET"), description("NOT SET") {}

ostream& operator<<(ostream& out, const Concept& op2)
{
	op2.display(out);
	return out;
}

/*	PUBLIC METHODS	*/

//should only be called after a concept has been displayed
void Concept::select_site(void)	const //demanded by spec for some reason
{
	int _choice {-2};
	cout << "Which site would you like to select, by its number?: ";
	try{
		_choice = get_int(1, websites.size());
		cout << "Selected:\n" << websites.at(_choice - 1).get_url() << '\n';
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		select_site();
	}

	return;
}

void Concept::display(ostream& out) const
{
	//this is a rough draft for testing
	size_t count = 0;
	out << '"' << name << "\";\nDescription: "
		<< description << "\nWebsites:";
	if (websites.size() == 0)
		cout << "No websites...";
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
	if (_choice == ""){
		cout << "Would you like to add a {website}, or an{other} piece of "
			 << "info?\n{!q} to cancel: ";
		_choice = get_string(2);
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

void Concept::edit(string _choice)
{
	try{
		if (_choice == ""){
			cout << "Would you like to edit the"
				 << " {name}, {description}, a {website},"
				 << " or an{other} attribute?\n{!q} to cancel: ";
			_choice = get_string(2);
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

/*	PRIVATE METHODS	*/

void Concept::set_name(void)
{
	cout << "Enter a name or {!q} to cancel: ";
	name = get_string();		//may throw
}

void Concept::set_description(void)
{
	cout << "Enter a description or {!q} to cancel: ";
	description = get_string();	//may throw
}

void Concept::add_site(void)
{
	Website new_site;
	if (new_site.setup())
		websites.push_back(new_site);
	else //user cancelled
		throw "User cancels!";
}

void Concept::edit_site(void)
{
	//todo could edit_method borrow from this somehow?
	string _choice;
	bool match {false};
	switch (websites.size()){
		case 0:
			cout << "No websites to edit!\n";
			break;
		case 1:
			cout << "Editing \"" << websites.at(0).get_url() << "\"...\n";
			websites.at(0).edit();
			break;
		default:
			for (Website& w: websites)
				cout << w << '\n';
			cout << "Which website would you like to edit? {!q to cancel}: ";
			_choice = get_string();
			for (Website& w: websites){
				if (w == _choice){
					w.edit();
					match = true;
				}
			}
			if (!match)
				cout << "No such website!\n";
	}
	return;
}

/*			CLASS STL			*/ //TODO mostly complete

/*	PUBLIC METHODS	*/

void STL::display(ostream& out) const
{
	//this is a rough draft for testing
	out << "STL concept ";
	Concept::display(out); //name, desc, websites handled here
	out << "\nMethods:";//go on to handle derived
	if (methods.size() == 0)	//todo may want STL::display_meths subrtn
		cout << "\nNo methods...";  //...can I just cout << vector ?
	else{
		for (const Method& m: methods){
			cout << '\n' << m;
		}
	}
}

bool STL::setup(bool base_set_up, bool method_added)
{
	bool ret {true};
	try{
		if (! base_set_up){
			cout << "Setting up a new STL...\n"; //testing, will refine message 
			ret = Concept::setup();
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
		*this = STL(); //reset and return
		ret = false;
	}

	return ret;
}

void STL::edit(string _choice){
	try{
		Concept::edit(); //if this returns w/ no throws, user edited base
	}

	catch (out_of_range& user_edits_derived){ //case user wants to edit derived
		edit_stl(); //call to derived edit function goes here
	}

	return;
}

void STL::add(string _choice)
{
	try{
		Concept::add(); //if this returns w/ no throws, user added to base
	}

	catch (out_of_range& user_adds_derived){ //case user wants to add derived
		add_stl();
	}

	catch (const char*& user_cancels){ //user entered !q
		;
	}

	return;
}


bool STL::contains(string& key)
{
	//TODO partially match method name/desc
	//IN PROG
	bool ret = false;
	for (Method& m: methods){
		if (m.get_name().find(key) != string::npos){
			ret = true;
			break; //is this ok to use here?
		}
	}
	return ret;
}

//need a unique derived method TODO

/*	PRIVATE METHODS	*/

//Kept in design for maintainability and uniformity
void STL::add_stl(void)
{
	add_method(); //no need to do UI things since there is only one option
	return;
}

//Kept in design for maintainability and uniformity
void STL::edit_stl(void)
{
	edit_method(); //no need to do UI things since there is only one option
	return;
}

void STL::edit_method(void)
{
	string _choice;
	bool match {false};
	switch (methods.size()){
		case 0:
			cout << "No methods to edit!\n";
			break;
		case 1:
			cout << "Editing method \"" << methods.at(0).get_name() << "\"...\n";
			methods.at(0).edit();
			break;
		default:
			for (Method& m: methods)
				cout << m << '\n';
			cout << "Which method would you like to edit? {!q to cancel}: ";
			_choice = get_string();
			for (Method& m: methods){
				if (m == _choice){
					m.edit();
					match = true;
				}
			}
			if (!match){
				cout << "No such method!\n";
				edit_method();
			}
			break;
	}
	return;
}

void STL::add_method(void)
{
	Method new_method;
	if (new_method.setup())
		methods.push_back(new_method);
	else //user cancelled
		; //char* will be caught in add()
	return;
}

/*			CLASS PYTHONLIB			*/ //TODO not started
/*	PUBLIC METHODS	*/

bool PythonLib::contains(string& key)
{
	//TODO partially match class, lib, or meth name/desc
}

//need a unique derived method TODO

/*	PRIVATE METHODS	*/



/*
class PythonLib
{
	public:
		PythonLib(void);						//for use in client code
		PythonLib(string, string, string, int,
				  string, vector<Method>);		//for tests

		bool setup(void);		//calls all private setters/1 of each adder
		void add_info(void);		//add pro or con
		void edit_info(void);		//edit pro or con
		bool contains(string&);		//partially match pros and cons

	private:
		string class_name;
		vector<Method> methods;
};
*/

/*			CLASS MODERNCPP			*/ //TODO not started
/*	PUBLIC METHODS	*/

/*	PRIVATE METHODS	*/

bool ModernCpp::contains(string& key)
{
	//TODO partially match pro or con or name or desc
}

string ModernCpp::check_applicability(string&) //cats partial matches
{
	//TODO
}

/*
class ModernCpp
{
	public:
		ModernCpp(void);
		ModernCpp(string, string, string, int, vector<Method>); //for tests

		string check_applicability(string&); //returns all pros and cons from
										//any ModernCpp instance if they contain
										//the string arg, concatenating them and
										//printing them.
		bool setup(void);		//calls all private setters/1 of each adder
		void add_info(void);		//add pro or con
		void edit_info(void);		//edit pro or con
		bool contains(string&);		//partially match pros and cons

	private:
		vector<string> pros;
		vector<string> cons;
};
*/
