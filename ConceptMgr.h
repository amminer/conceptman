#pragma once

#include "RBT.h"

/*	Amelia Miner				5/20/2022
 *	cs202, section 003
 *	FILE:		ConceptMgr.h
 *	PURPOSE:		Declares a main class that uses an RBT to store and manage
 *				concepts. Supports insert, display, remove_all, find by name,
 *				editing of concepts by name, etc.
 *					Removal of nodes (therefore of concepts) is not supported;
 *				see implementation for details.
 *					ConceptMgr should be flexible enough to readily accept new
 *				functionality with minimal maintenance - I made my best effort,
 *				but one thing I began to get a grasp of while working on this
 *				project was how I might be able to write a display_choices or
 *				get_choice function to dramatically reduce the bulk of UI code.
 */

class ConceptMgr: public Util
{
	public:
		ConceptMgr(bool = false);	//main loop w/debug var

	private:
		RBT tree;

		//debug
		void test(void);
		void add_concept(Concept*);

		//UI
		void main_loop(bool = true, string = "_");
		void add_concept(void);
		void edit_concept(void);
		void edit_or_add(Concept* to_edit);
		void remove_topic(void);
		void remove_concept(void);
		void select_site(void);
		void expand_topic(void);
		void collapse_topic(void);
		Concept* find_concept(bool = false, string = "", string = ""); //bool whether mainloop display
		void rtti(void); //sorry, not sure what else to name this
		void lookup(void);
};
