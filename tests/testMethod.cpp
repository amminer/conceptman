#include "../SubConcept.h" //Util, Method, Website

int main(void)
{
	Method meth;
	if (meth.setup()){ //returns false if user cancels
		cout << '\n' << meth << '\n';
		meth.edit();
		cout << '\n' << meth << '\n';
	}
	else
		cout << "User cancelled method!\n";

	return 0;
}
