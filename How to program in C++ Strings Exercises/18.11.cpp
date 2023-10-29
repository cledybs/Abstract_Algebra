//18.11
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string nombre;
	string apellido;
	string registro;
	
	getline(cin,nombre);
	getline(cin,apellido);
	
	registro = nombre + ' ' + apellido;
	
	cout << registro;
	return 0;
}