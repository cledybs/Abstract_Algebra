//18.19
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string cadena;
	
	getline(cin,cadena);
	int mitad = cadena.length()/2;
	
	cadena.insert(mitad,"******");
	
	cout << cadena;
	
	return 0;
}