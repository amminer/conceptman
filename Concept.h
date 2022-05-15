#pragma once

#include "SubConcept.h"
#include <vector>

/*	Amelia Miner				5/12/2022
 *	cs202, section 003
 *	FILE:		Concept.h
 *	PURPOSE:	Declare the central hierarchy for the program,
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

class Concept: public Util
{
	public:
		Concept(void);
		~Concept(void);

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

/*	Each STL container class gets one STL object instance, and there is one
 * STL instance for holding any STL methods that do not belong to a container
 * (such as std::min_element)
 */
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

/*	Each Python library class gets many PythonLib instances with the same base
 * name field denoting the library name, with one instance per library class
 * containing the methods of that class (such as Pandas.DataFrame), plus one
 * instance to hold all library methods not belonging to any particular class
 * whose class_name string is "global to library"
 */
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

/*	Each modern c++ technique gets one ModernCpp instance, with a container of
 * strings for pros and cons of that technique.
 */
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
