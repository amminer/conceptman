#include "../Concept.h"

void testSTL(void)
{
	//TODO in progress
	STL c;
	string _choice;
	if (c.setup()){
		cout << '\n' << c << '\n';
		cout << "Edit {y or anything else}?: ";
		getline(cin, _choice);
		if (_choice == "y"){
			c.edit();
			cout << '\n' << c << '\n';
		}
	}
	else
		cout << "User canceled setup!\n";

}

void testModernCpp(void)
{
	//TODO
}

void testPythonLib(void)
{
	//TODO
}

Concept* testPolymorphism(void)
{
	//TODO
}

int main(void)
{
	testSTL();
	return 0;
}
