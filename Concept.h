#pragma once

#include "SubConcept.h"
#include <set>
#include <iterator>

/*	Amelia Miner				5/12/2022
 *	cs202, section 003
 *	FILE:		Concept.h
 *	PURPOSE:	Declare the central hierarchy for the program,
 *			one base class Concept and three derived classes Library,
 *			PythonLib, and ModernCpp. Each class has a self similar
 *			interface with the exception of one function per derived
 *			class. Concept is an abstract base class (ABC).
 *				PythonLib and Library objects contain a collection of methods,
 *			which belong to the container indicated by Library.name or the class
 *			indicated by PythonLib.class_name within the library PythonLib.name.
 *			PythonLib methods which do not belong to some class within their
 *			library are sorted into a single PythonLib instance w/ that library
 *			name + class_name "global to library". Library methods which do not
 *			belong to some container are sorted into a single Library instance with
 *			the name "global to Library".
 *				ModernCpp has a container of strings for pros and a container of
 *			strings for cons. There's one ModernCpp instance for each modern c++
 *			programming technique (ex smart pointers,
 *			initialization-within-conditionals, etc).
 */

class Concept: public Util	//ABC
{
	public:
		Concept(void);
		Concept(string); //for key in search via ModernCpp
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
		//string arg used to search for Library method or PythonLib class 
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

/*	STL and PythonLib class are Libraries, and there is one
 * Library instance for holding any methods that do not belong to a class
 * (such as std::min_element for STL or numpy.sin for PythonLib).
 *	In STL, this is indicated by name == "global to library".
 *	In PythonLib, this is indicated by class_name == "global to library".
 *	SHOULD BE UNIQUE BASED ON name FIELD IN CLIENT CODE (operator==)
 */
class Library: public Concept
{
	public:
		virtual void display(ostream& out = cout) const;    //"polymorphic" op<<
		virtual bool setup(bool = false, bool = false);	  //calls setters/adders
		virtual void add(string = "");								//add method
		virtual void edit(string = "");							   //edit method
		virtual void remove(string = "");						 //remove method
		virtual bool contains(string&) const; //partially match method name/desc

	protected:
		set<Method> methods;

		void add_method(void);
		void edit_method(void); //select a method and call its .edit()
		void remove_method(void);

	private:
		void add_library(void);	 	//wrappers kept in for extensibility/uniformity
		void edit_library(void); 	//called by edit as subroutinue
		void remove_library(void);
};

class STL: public Library
{
	public:
		virtual void display(ostream& out = cout) const;    //"polymorphic" op<<
		void copy_methods(const STL&);
};

/*	Each Python library class gets many PythonLib instances with the same base
 * name field denoting the library name, with one instance per library class
 * containing the methods of that class (such as Pandas.DataFrame), plus one
 * instance to hold all library methods not belonging to any particular class
 * whose class_name string is "global to library".
 *	SHOULD BE UNIQUE BASED ON class_name FIELD IN CLIENT CODE (operator==)
 */
class PythonLib: public Library
{
	public:
		bool operator< (const PythonLib& op2) const;
		//not sure about this, prob not a good move for use in tree-by-name
		//bool operator==(const PythonLib& op2) const;

		//returns whether class name is anything but "global to library"
		//std::map tracks each PythonLib::name and maps it to a table of python
		//libraries in ConceptManager to allow user to see which libraries are
		//purely OO... not my favorite but it works todo
		bool is_object_oriented(void);
		virtual void display(ostream& out = cout) const;    //"polymorphic" op<<
		virtual bool setup(bool = false, bool = false, bool = false);
		virtual void edit(string = "");				   //edit method, class name
		virtual bool contains(string&) const; //part. match class/meth name/desc

	private:
		string lib_name;

		void set_lib_name(void);
		void add_pythonlib(void);
		void edit_pythonlib(string = ""); //called by edit as subroutine
};

/*	Each modern c++ technique gets one ModernCpp instance, with a container of
 * strings for pros and cons of that technique.
 *	SHOULD BE UNIQUE BASED ON name FIELD IN CLIENT CODE (operator==)
 */
class ModernCpp: public Concept
{
	public:
		ModernCpp(void);
		ModernCpp(string); //used as key in searches since I can't instantiate 
						   //the base class
		string check_applicability(string = ""); //returns all pros and cons from
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

		void add_moderncpp(void);
		void edit_moderncpp(void);
		void remove_moderncpp(void);
		void add_pro_or_con(void);
		void edit_pro_or_con(void);
		void remove_pro_or_con(void);
};
