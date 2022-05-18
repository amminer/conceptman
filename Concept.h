#pragma once

#include "SubConcept.h"
#include <set>
#include <iterator>

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

		bool operator< (const Concept& op2) const;
		bool operator==(const Concept& op2) const;
		friend ostream& operator<<(ostream& out, const Concept& op2);

		void select_site(void) const;	//demanded by spec for some reason
		virtual void display(ostream& out = cout) const; //"polymorphic" op<<
		//calls all private setters/1 of each adder
		virtual bool setup(bool = false, bool = false, bool = false); 
		//add website, method, pro or con
		virtual void add(string = "");
		//edit website, method, pro or con
		virtual void edit(string = "");
		//remove website, method, pro, or con
		virtual void remove(string = "");
		//contains website, method, pro or con
		virtual bool contains(string&) const =0;	//pure virtual//ABC
		//string arg used to search for STL method or PythonLib class 
		//or method by name, or search for a pros/cons of a ModernCpp by keyword

	protected:
		string name; //must be protected to access from derived operators

	private:
		string description;
 		//set preferred for fast random access?
		set<Website> websites; //set best for prioritizing lookup speed?

		//Called by UI functions, validate input, throw exceptions
		void set_name(void);
		void set_description(void);
		void add_site(void);
		void edit_site(void);			//calls public Website::edit method
		void remove_site(void);
};

/*	Each STL container class gets one STL object instance, and there is one
 * STL instance for holding any STL methods that do not belong to a container
 * (such as std::min_element)
 *	SHOULD BE UNIQUE BASED ON name FIELD IN CLIENT CODE (operator==)
 */
class STL: public Concept
{
	public:
		//default constructor acceptable?

		//need a unique derived method TODO
		virtual void display(ostream& out = cout) const;    //"polymorphic" op<<
		virtual bool setup(bool = false, bool = false);	  //calls setters/adders
		virtual void add(string = "");								//add method
		virtual void edit(string = "");							   //edit method
		virtual void remove(string = "");						 //remove method
		virtual bool contains(string&) const; //partially match method name/desc

	private:
		set<Method> methods;

		void add_stl(void);	 	//wrappers kept in for extensibility/uniformity
		void edit_stl(void); 	//called by edit as subroutinue
		void remove_stl(void);
		void add_method(void);
		void edit_method(void); //select a method and call its .edit()
		void remove_method(void);
};

/*	Each Python library class gets many PythonLib instances with the same base
 * name field denoting the library name, with one instance per library class
 * containing the methods of that class (such as Pandas.DataFrame), plus one
 * instance to hold all library methods not belonging to any particular class
 * whose class_name string is "global to library".
 *	SHOULD BE UNIQUE BASED ON class_name FIELD IN CLIENT CODE (operator==)
 */
class PythonLib: public Concept
{
	public:
		//default constructor works

		bool operator< (const PythonLib& op2) const;
		//not sure about this, prob not a good move for use in tree-by-name
		//bool operator==(const PythonLib& op2) const;

		//need a unique derived method TODO
		virtual void display(ostream& out = cout) const;    //"polymorphic" op<<
		virtual bool setup(bool = false, bool = false, bool = false);
		virtual void add(string = "");							    //add method
		virtual void edit(string = "");				   //edit method, class name
		virtual void remove(string = "");						 //remove method
		virtual bool contains(string&) const; //part. match class/meth name/desc

	private:
		string class_name;
		set<Method> methods;

		void set_class_name(void);
		void add_pythonlib(void);
		void edit_pythonlib(void); //called by edit as subroutine
		void remove_pythonlib(void);
		void add_method(void);
		void edit_method(void);
		void remove_method(void);
};

/*	Each modern c++ technique gets one ModernCpp instance, with a container of
 * strings for pros and cons of that technique.
 *	SHOULD BE UNIQUE BASED ON name FIELD IN CLIENT CODE (operator==)
 */
class ModernCpp: public Concept
{
	public:
		//default constructor acceptable?

		string check_applicability(string&); //returns all pros and cons from
										//any ModernCpp instance if they contain
										//the string arg+concatenating them with
										//double-newlines as separators
		virtual void display(ostream& out = cout) const;    //"polymorphic" op<<
		virtual bool setup(bool = false, bool = false);	  //calls setters/adders
		virtual void add(string = "");							//add pro or con
		virtual void edit(string = "");						   //edit pro or con
		virtual void remove(string = "");					 //remove pro or con
		virtual bool contains(string&) const;	 //partially match pros and cons

	private:
		set<string> pros;
		set<string> cons;

		void edit_moderncpp(void); //called by edit as subroutine
		void add_pro_or_con(void);
		void edit_pro_or_con(void);
		void remove_pro_or_con(void);
};
