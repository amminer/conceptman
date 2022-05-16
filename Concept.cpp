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

//vector needs initialization? TODO check in gdb
Concept::Concept(void)
	: name("NOT SET"), description("NOT SET") {}

ostream& operator<<(ostream& out, const Concept& op2)
{
	//this is a rough draft for testing
	out << "Concept \"" << op2.name << "\";\nDescription: "
		<< op2.description << "\nWebsites:\n";
	for (Website w: op2.websites){
		out << w << '\n';
	}
	return out;
}

/*	PUBLIC METHODS	*/

bool Concept::setup(bool name_set, bool desc_set, bool site_added)
{
	bool ret {true};
	try{
		if (! name_set){
			cout << "Setting up a new Concept...\n"; //testing, will refine message to user
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

	catch (const char*& user_cancels){
		//not strictly necessary... but useful info for debugging
		//should I let the program be run with a -g flag? vargs easy to set up
		*this = Concept(); //reset and return
		ret = false;
	}

	return ret;
}

void Concept::add(string _choice)
{
	//TODO in progress
	if (_choice == ""){
		cout << "Would you like to add a {website}, or an{other} piece of "
			 << "info?\n{!q} to cancel: ";
		_choice = get_string(2);
	}
	if 		(_choice == "website")
		add_site();
	else if (_choice == "other")
		throw out_of_range("User adds derived!");
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
			throw out_of_range("User edits derived!"); //user wants to edit outside of base "range"
		else{
			disp_invalid_input(_choice);
			edit();
		}
	}

	catch (const invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		edit(_choice);
	}

	catch (const char*& user_cancels){ //user entered !q
		throw user_cancels; //throw again to inform derived method of cancel
							//since base::edit should only be called
							//from derived::edit... should this just be caught
							//in derived::edit? TODO
	}

	return;
}

bool Concept::lookup(string& key)
{
	//TODO
}

/*	PRIVATE METHODS	*/

void Concept::set_name(void)
{
	//TODO test
	cout << "Enter a name or {!q} to cancel: ";
	name = get_string();		//may throw
}

void Concept::set_description(void)
{
	//TODO test
	cout << "Enter a description or {!q} to cancel: ";
	description = get_string();	//may throw
}

void Concept::add_site(void)
{
	//TODO test
	Website new_site;
	if (new_site.setup())
		websites.push_back(new_site);
	else //user cancelled
		throw "User cancels!";
}

void Concept::edit_site(void)
{
	//TODO
}

/*
class Concept: public Util
{
	public:
		Concept(void);
		virtual ~Concept(void);

		//calls all private setters/1 of each adder
		virtual bool setup(bool = false, bool = false, bool = false); 
		//add website, method, pro or con
		virtual void add_info(string = "");
		//edit website, method, pro or con
		virtual void edit_info(string = "");
		virtual bool lookup(string&);	//pure virtual seems appropriate?
		//string arg of lookup used to search for STL method or PythonLib class 
		//or method by name, or search for a pros/cons of a ModernCpp by keyword

	private:
		string name;
		string description;
 		//vector preferred for fast random access?
		vector<Website> websites; //vector best for prioritizing lookup speed?

		//Called by UI functions, validate input, throw exceptions
		void set_name(void);
		void set_description(void);
		void add_site(void);
		void edit_site(void);			//calls public Website::edit method
};
*/

/*			CLASS STL			*/
/*	PUBLIC METHODS	*/

// remember to catch the out_of_range when user wants to edit derived property
void STL::edit(string _choice){
	try{
		//TODO in progress
		this->Concept::edit(); //if this returns w/ no throws, user edited base
	}

	catch (out_of_range& user_edits_derived){ //case user wants to edit derived
		edit_stl(); //call to derived edit function goes here
	}


	catch (const char*& user_cancels){ //user entered !q
		;
	}
}
void STL::edit_stl(string _choice)
{
	try{
		if (_choice == "")
			;//body of derived edit w/prompts etc
			//TODO in progress
	}

	catch (const invalid_argument& bad_input){ //case user provides bad input
		disp_invalid_input((string) bad_input.what());
		edit_stl(_choice);
	}
}


/*	PRIVATE METHODS	*/

/*
class STL
{
	public:
		STL(void);							//for use in client code
		STL(string, string, string, int,
			vector<Method>);				//for tests

		//need a unique derived method TODO
		bool setup(void);		//calls all private setters/1 of each adder
		void add_info(void);		//add pro or con
		void edit_info(void);		//edit pro or con
		bool lookup(string&);		//partially match pros and cons

	private:
		vector<Method> methods;
};
*/

/*			CLASS PYTHONLIB			*/
/*	PUBLIC METHODS	*/
/*	PRIVATE METHODS	*/

/*
class PythonLib
{
	public:
		PythonLib(void);						//for use in client code
		PythonLib(string, string, string, int,
				  string, vector<Method>);		//for tests

		//need a unique derived method TODO
		bool setup(void);		//calls all private setters/1 of each adder
		void add_info(void);		//add pro or con
		void edit_info(void);		//edit pro or con
		bool lookup(string&);		//partially match pros and cons

	private:
		string class_name;
		vector<Method> methods;
};
*/

/*			CLASS MODERNCPP			*/
/*	PUBLIC METHODS	*/
/*	PRIVATE METHODS	*/

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
		bool lookup(string&);		//partially match pros and cons

	private:
		vector<string> pros;
		vector<string> cons;
};
*/
