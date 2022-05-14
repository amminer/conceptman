#include "../Concept.h"	//PythonLib, STL, ModernCpp
#include "../SubConcept.h" //Util, Method, Website

int main(void)
{
	Website site;
	site.setup();
	if (site.is_set_up()){
		cout << site << '\n';
		site.edit();
		cout << site << '\n';
	}
	else
		cout << "User cancelled site!\n";

	return 0;
}
