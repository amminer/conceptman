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
 *			class. Concept is an abstract base class (ABC).
 *				PythonLib and STL objects contain a collection of methods,
 *			which belong to the container indicated by STL.name or the class
 *			indicated by PythonLib.class_name within the library PythonLib.name.
 *			PythonLib methods which do not belong to some class within their
 *			library are sorted into a single PythonLib instance w/ that library
 *			name + class_name "global to library". STL methods which do not
 *			belong to some container are sorted into a single STL instance with
 *			the name "global to STL".
 *				ModernCpp has a container of strings for pros and a container of
 *			strings for cons. There's one ModernCpp instance for each modern c++
 *			programming technique (ex smart pointers,
 *			initialization-within-conditionals, etc).
 */

class Concept: public Util	//ABC
{
	public:
		Concept(void);
		//virtual ~Concept(void);

		friend ostream& operator<<(ostream& out, const Concept& op2);

		//calls all private setters/1 of each adder
		virtual bool setup(bool = false, bool = false, bool = false); 
		//add website, method, pro or con
		virtual void add(string = "");
		//edit website, method, pro or con
		virtual void edit(string = "");
		//lookup website, method, pro or con
		virtual bool lookup(string&)=0;	//pure virtual//ABC
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

/*	Each STL container class gets one STL object instance, and there is one
 * STL instance for holding any STL methods that do not belong to a container
 * (such as std::min_element)
 */
class STL: public Concept
{
	public:
		//default constructor acceptable?
		friend ostream& operator<<(ostream& out, const STL& op2);

		//need a unique derived method TODO
		bool setup(bool = false, bool = false);		//calls all private setters/1 of each adder
		void add(string = "");		//add method
		void edit(string = "");		//edit method
		bool lookup(string&);		//partially match method names and descriptions

	private:
		vector<Method> methods;

		void edit_stl(void); //called by edit as subroutine
		void add_method(void);
		void edit_method(void); //select a method and call its .edit()
};

/*	Each Python library class gets many PythonLib instances with the same base
 * name field denoting the library name, with one instance per library class
 * containing the methods of that class (such as Pandas.DataFrame), plus one
 * instance to hold all library methods not belonging to any particular class
 * whose class_name string is "global to library"
 */
class PythonLib: public Concept
{
	public:
		PythonLib(void);						//for use in client code
		PythonLib(string, string, string, int,
				  string, vector<Method>);		//for tests

		//need a unique derived method TODO
		bool setup(bool = false, bool = false);		//calls all private setters/1 of each adder
		void add_info(string = "");			//add method
		void edit_info(string = "");		//edit method, class name
		bool lookup(string&);		//partially match classes and methods by name or desc

	private:
		string class_name;
		vector<Method> methods;

		void edit_pythonlib(void); //called by edit as subroutine
		void set_class_name(void);
		void add_method(void);
		void edit_method(void);
};

/*	Each modern c++ technique gets one ModernCpp instance, with a container of
 * strings for pros and cons of that technique.
 */
class ModernCpp: public Concept
{
	public:
		//default constructor acceptable?

		string check_applicability(string&); //returns all pros and cons from
										//any ModernCpp instance if they contain
										//the string arg, concatenating them with
										//double-newlines separating
		bool setup(bool = false, bool = false);		//calls all private setters/1 of each adder
		void add(string = "");		//add pro or con
		void edit(string = "");		//edit pro or con
		bool lookup(string&);		//partially match pros and cons

	private:
		vector<string> pros;
		vector<string> cons;

		void edit_moderncpp(void); //called by edit as subroutine
		void add_pro_or_con(void);
		void edit_pro_or_con(void);
};
