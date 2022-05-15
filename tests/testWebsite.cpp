#include "../Concept.h"	//PythonLib, STL, ModernCpp
#include "../SubConcept.h" //Util, Method, Website

int main(void)
{
	Website site;
	if (site.setup()){ //returns false if user cancels
		cout << '\n' << site << '\n';
		site.edit();
		cout << '\n' << site << '\n';
	}
	else
		cout << "User cancelled site!\n";

	return 0;
}
