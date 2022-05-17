#pragma once

#include <iostream>
#include <climits>		//INT_MAX
#include <exception>	//bad_argument
#include <regex>		//sorry, you have to look at a regex pattern

using namespace std;

/*	Amelia Miner				5/12/2022
 *	cs202, section 003
 *	FILE:		SubConcept.h
 *	PURPOSE:	Declare abstractions of data contained by Concept
 *			classes; class Method is used to contain information
 *			regarding a STL or PythonLib method, class Website is used
 *			to contain information regarding a website including a URL
 *			and a rating out of 10, as well as whatever else one might
 *			want to add down the road, since this is much more flexible
 *			than representing a website as a pair<string, int> for example.
 *				Also contains a Util class, inherited by any classes that need
 *			to perform common IO operations via terminal input (all of them).
 *		*.......All classes in this program follow a pattern of public methods
 *			setup and edit, which are UI entry points for client code. All
 *			validation happens internal to the class and exceptions + recursive
 *			calls with boolean return values for each field being set allow the
 *			program to return to the exact point it needs to based on previous
 *			user input.
 */

class Util //contains basic IO behaviors needed by other classes
{
	public:
		//THROWS CONST CHAR* ON "-1" INPUT
		int get_int(const int = 0, const int = INT_MAX) const;
		//THROWS CONST CHAR* ON "!q" INPUT
		string get_string(const int = 1,				
						  const int = 100000) const;	//arbitrary max
		//pass const char*s to this to display to user
		void disp_invalid_input(const string) const;
};

/*	Wraps information about a website into a convenient package for maintenance,
 * may add more information later, makes it easier to search websites by keyword
 */
class Website: public Util
{
	public:
		Website();

		bool operator==(const Website& op2);
		bool operator==(const string& op2);
		friend ostream& operator<<(ostream&, const Website&);

		//calls all private validators, true on success
		bool setup(bool = false, bool = false, bool = false);
		void edit(string = "");
		string& get_url(void);

	private:
		//these throw exceptions...
		void validate_url(const string& _url) const;	//uses regex - see .cpp
		void set_url(void);
		void set_rating(void);
		void set_description(void);

		string url; //limited by setter to len 3-2000, must contain a ., etc?
		string description;
		int rating; //limited by setter to 1-10
};

/* 	Wraps information about a method into a convenient package for maintenance,
 * may add a list of pairs of strings to represent args and descriptions of what
 * role they play in the method, a string for return type, etc. down the road...
 */
class Method: public Util
{
	public:
		Method();

		bool operator==(const Method& op2) const;
		bool operator==(const string& op2) const;
		friend ostream& operator<<(ostream&, const Method&);

		bool setup(bool = false, bool = false);	//calls all private setters
		void edit(string = "");	//user chooses to set name or description
		string& get_name(void);

	private:
		void set_name();			//min len 1
		void set_description();		//min len 1

		string name;
		string description;
		//strikingly similar to concept - could concept inherit from method?
};
