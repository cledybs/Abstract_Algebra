//18.22
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string cadena;
	getline(cin,cadena);
	
	string::const_iterator k = cadena.end()-1;

	while ( k != cadena.begin()-1)
	{
		cout << *k;
		k--;
	}
	
	return 0;
}