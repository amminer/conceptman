#include "Concept.h"

/*	Amelia Miner				5/14/2022
 *	cs202, section 003
 *	FILE:		Concept.cpp
 *	PURPOSE:	TODO... Declare the central hierarchy for the program,
 *			one base class Concept and three derived classes STL,
 *			PythonLib, and ModernCpp. Each class has a self similar
 *			interface with the exception of one function per derived
 *			class.
 *				PythonLib and STL objects contain a collection of methods,
 *			which belong to the container indicated by STL.name or the class
 *			indicated by PythonLib.class_name within the library PythonLib.name.
 *			PythonLib methods which do not belong to some class within their
 *			library are sorted into a single PythonLib instance with that library
 *			name + class_name "global to library". STL methods which do not
 *			belong to some container are sorted into a single STL instance with
 *			the name "global to STL".
 *				ModernCpp has a container of strings for pros and a container of
 *			strings for cons. There is one ModernCpp instance for each modern c++
 *			programming technique (ex smart pointers,
 *			initialization-within-conditionals, etc).
 */


/*			CLASS CONCEPT			*/

//vector needs initialization? TODO check in gdb
Concept::Concept(void)
	: name("NOT SET"), description("NOT SET") {}

/*	PUBLIC METHODS	*/

bool Concept::setup(bool name_set, bool desc_set, bool website_added)
{
	//TODO
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
		if (!website_added){
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
		*this = Method(); //reset and return
		ret = false;
	}

	return ret;
}

void Concept::add_info(string _choice = "")
{
	//TODO
}

void Concept::edit_info(string _choice = "")
{
	//TODO
}

bool Concept::lookup(string& key)
{
	//TODO
}

/*	PRIVATE METHODS	*/

void Concept::set_name(void)
{
	//TODO
}

void Concept::set_description(void)
{
	//TODO
}

void Concept::add_site(void)
{
	//TODO
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
		//or method by name, or search for a pros/cons of a ModernCpp by keyword.

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

/*			CLASS UTIL			*/
/*	PUBLIC METHODS	*/
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

/*			CLASS UTIL			*/
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

/*			CLASS UTIL			*/
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
