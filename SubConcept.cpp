#include "SubConcept.h"

/*	Amelia Miner				5/14/2022
 *	cs202, section 003
 *	FILE:		SubConcept.h
 *	PURPOSE:	Define behavior of abstractions of data contained by Concept
 *			classes; class Method can read in and set a method name and a
 *			description string re: a STL or PythonLib method, class Website can
 *			read in and set a string URL and an int rating out of 10. Both
 *			classes can display their contents via ostream operator<< overloads.
 */

/*			CLASS UTIL			*/
/*	PUBLIC METHODS	*/

int Util::get_int(const int min, const int max) const
{
	int _ret {-2};
	cin >> _ret;
	cin.clear();
	cin.ignore(1000, '\n');
	if (_ret == -1)
		throw "user cancels!"; //const char*
	if (_ret < min or _ret > max)
		throw invalid_argument(to_string(_ret));
	return _ret;
}

string Util::get_string(const int min, const int max) const
{
	string _ret {""};
	getline(cin, _ret);
	if (_ret == "!q")
		throw "user cancels!";
	size_t len {_ret.length()};
	if (len < (size_t)min or len > (size_t)max)
		throw invalid_argument(_ret);
	return _ret;
}

void Util::disp_invalid_input(const string bad_input) const
{
	cout << "Bad input! \"" << bad_input << "\" is not valid.\n";
}

/*			CLASS WEBSITE			*/

Website::Website(void)
	: url("NOT SET"), rating(-1) {}

bool Website::operator<(const Website& op2) const
{
	return url < op2.url;
}

bool Website::operator==(const Website& op2) const
{
	return url == op2.url; //TODO partial matching
}

bool Website::operator==(const string& op2) const
{
	return url == op2; //TODO partial matching
}

ostream& operator<<(ostream& out, const Website& op2)
{
	cout << op2.url << " (rated " << op2.rating << " out of 10)\n\t"
		 << op2.description;
	return out;
}

/*	PUBLIC METHODS	*/

bool Website::setup(bool url_set, bool desc_set, bool rating_set)
{
	bool ret {true};
	try{
		if (! url_set){
			cout << "Setting up a new Website...\n"; //testing, will refine message to user
			set_url();
			url_set = true;
		}
		if (! desc_set){
			set_description();
			desc_set = true;
		}
		if (! rating_set){
			set_rating();
			rating_set = true; //unnecessary to check last input? TODO
		}
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		return setup(url_set, desc_set, rating_set); //setup must be completed
	}

	/* Continue passing cancel signal up to client class
	catch (const char*& user_cancels){
		*this = Website(); //reset and return
		ret = false;
	}
	*/

	return ret;
}

void Website::edit(string _choice)
{
	try{
		if (_choice == ""){
			cout << "Would you like to edit the"
				 << " {url}, {rating}, or {description}?\n{!q} to cancel: ";
			_choice = get_string(2);
		}
		if		(_choice == "url")
			set_url();
		else if (_choice == "rating")
			set_rating();
		else if (_choice == "description")
			set_description();
		else{
			disp_invalid_input(_choice);
			edit();
		}
	}

	catch (const invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		edit(_choice);
	}

	/* Continue passing cancel signal up to client class
	catch (const char*& user_cancels){ //user entered !q
		; //do nothing and return (don't want to erase existing data)
	}
	*/

	return;
}

const string& Website::get_url(void) const
{
	return url;
}

/*	PRIVATE METHODS	*/

/*	This will accept any format from the most shortened possible like "a.co"
 * to the longest most unwieldy like "https://online.visual-paradigm.com/
 * w/jwdamuwc/app/diagrams/#diagram:workspace=jwdamuwc&proj=0&id=1".
 */
void Website::validate_url(const string& _url) const
{
	regex pattern { //pattern modified from regexr.com/2rj36
		  (string) "[-a-zA-Z0-9@:%_\\+.~#?&\\/=]{1,256}\\."
		+ (string) "[a-z]{2,4}\\b(\\/[-a-zA-Z0-9@:%_\\+.~#?&\\/=]*)?" };

	if (! regex_match(_url, pattern))
		throw invalid_argument(_url);
	return;
}

void Website::set_url(void)
{
	cout << "Enter a URL or {!q} to cancel: ";
	string _url {get_string(4, 2048)};	//may throw
	validate_url(_url);					//may throw (regex quarantine)
	url = _url;
}

void Website::set_rating(void)
{
	cout << "Enter a rating out of 10 or {-1} to cancel: ";
	rating = get_int(1, 10);	//may throw
}

void Website::set_description(void)
{
	cout << "Enter a description or {!q} to cancel: ";
	description = get_string();	//may throw
}

/*		CLASS METHOD		*/

Method::Method(void)
	: name("NOT SET"), description("NOT SET") {}

bool Method::operator<(const Method& op2) const
{
	return name < op2.name;
}

bool Method::operator==(const Method& op2) const
{
	return name == op2.name;
}
bool Method::operator==(const string& op2) const
{
	return name == op2;
}

ostream& operator<<(ostream& out, const Method& op2)
{
	cout << "Method \"" << op2.name << "\":\n\t"
		 << op2.description;
	return out;
}

/*	PUBLIC METHODS	*/

bool Method::setup(bool name_set, bool desc_set)
{
	bool ret {true};
	try{
		if (! name_set){
			cout << "Setting up a new Method...\n"; //testing, will refine 
			set_name();
			name_set = true;
		}
		if (! desc_set){
			set_description();
			desc_set = true; //unnecessary to check last input? TODO
		}
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		return setup(name_set, desc_set); //setup must be completed
	}

	/*	continue passing cancel signal up to class calling setup
	catch (const char*& user_cancels){
		*this = Method(); //reset and return
		ret = false;
	}
	*/

	return ret;
}

void Method::edit(string _choice)
{
	try{
		if (_choice == ""){
			cout << "Would you like to edit the"
				 << " {name} or {description}?\n{!q} to cancel: ";
			_choice = get_string(2);
		}
		if		(_choice == "name")
			set_name();
		else if (_choice == "description")
			set_description();
		else{
			disp_invalid_input(_choice);
			edit();
		}
	}

	catch (const invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		edit(_choice);
	}

	/*	continue passing cancel signal up to client class
	catch (const char*& user_cancels){ //user entered !q
		; //do nothing and return (don't want to erase existing data)
	}
	*/

	return;
}

const string& Method::get_name(void) const
{
	return name;
}

/*	PRIVATE METHODS	*/

void Method::set_name(void)
{
	cout << "Enter a name or {!q} to cancel: ";
	name = get_string();		//may throw
}

void Method::set_description(void)
{
	cout << "Enter a description or {!q} to cancel: ";
	description = get_string();	//may throw
}
