#include "../Concept.h"

int main(void)
{
	STL c;
	if (c.setup())
		cout << '\n' << c << '\n';
	else
		cout << "User canceled setup!\n";

	//bit more work to do before a full test script can be written
	//please take a look at testWebsite.cpp and testMethod.cpp to see where this is going
}
