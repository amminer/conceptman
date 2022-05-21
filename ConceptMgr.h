#pragma once

#include "RBT.h"

/*	Amelia Miner				5/20/2022
 *	cs202, section 003
 *	FILE:		ConceptMgr.h
 *	PURPOSE:	Declares a main class that uses an RBT to store and manage
 * concept objects. Supports insert, display, remove_all, find by name,
 * editing and removal of concepts by name, etc TODO
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
		void remove_topic(void);
		void remove_concept(void);
		void select_site(void);
		void expand_topic(void);
		void collapse_topic(void);
		void lookup(void);
		template<typename T>
		void lookup_by_type(void);
};
