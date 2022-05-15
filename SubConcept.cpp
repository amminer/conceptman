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
	int ret {-2};
	cin >> ret;
	cin.clear();
	cin.ignore(1000, '\n');
	if (ret == -1)
		throw "user quits!";
	if (ret < min or ret > max)
		throw invalid_argument(to_string(ret));
	return ret;
}

string Util::get_string(const int min, const int max) const
{
	string ret {""};
	getline(cin, ret);
	if (ret == "!q")
		throw "user quits!";
	size_t len {ret.length()};
	if (len < (size_t)min or len > (size_t)max)
		throw invalid_argument(ret);
	return ret;
}

void Util::disp_invalid_input(const string bad_input) const
{
	cout << "Bad input! \"" << bad_input << "\" is not valid.\n";
}

/*			CLASS WEBSITE			*/

Website::Website(void)
	: url("NOT SET"), rating(-1) {}

ostream& operator<<(ostream& out, const Website& op2)
{
	cout << op2.url << " (rated " << op2.rating << " out of 10)\n"
		 << op2.description;
	return out;
}

/*	PUBLIC METHODS	*/

bool Website::setup(bool url_set, bool desc_set, bool rating_set)
{
	bool ret {true};
	try{
		if (! url_set){
			set_url();
			url_set = true;
		}
		if (! desc_set){
			set_description();
			desc_set = true;
		}
		if (! rating_set){
			set_rating();
			rating_set = true;
		}
	}

	catch (invalid_argument& bad_input){
		disp_invalid_input((string) bad_input.what());
		cout << "Please try again.\n";
		return setup(url_set, desc_set, rating_set); //setup must be completed
	}

	catch (const char*& user_quits){
		*this = Website(); //reset and return
		ret = false;
	}

	return ret;
}

void Website::edit(string _choice)
{
	try{
		if (_choice == ""){
			cout << "Would you like to edit the"
				 << " {url}, {rating}, or {description}?\n{!q} to quit: ";
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

	catch (const char*& user_quits){
		; //do nothing and return (don't want to erase existing data)
	}

	return;
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
	cout << "Enter a URL or {!q} to quit: ";
	string _url {get_string(4, 2048)};	//may throw
	validate_url(_url);					//may throw (regex quarantine)
	url = _url;
}

void Website::set_rating(void)
{
	cout << "Enter a rating out of 10 or {-1} to quit: ";
	rating = get_int(1, 10);	//may throw
}

void Website::set_description(void)
{
	cout << "Enter a Description or {!q} to quit: ";
	description = get_string();	//may throw
}

/*		CLASS METHOD		*/
//TODO

/*
class Method
{
	public:
		Method();

		//UI functions
		void setup(void);	//calls all private setters
		void edit(void);	//user chooses to set name or description

	private:
		void set_name(string&);			//min len 1
		void set_description(string&);	//min len 1

		string name;
		string description;
		//strikingly similar to class concept - could class concept inherit from method?
};
*/
