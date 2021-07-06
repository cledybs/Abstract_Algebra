//control - ej01
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string cadena;
	cout << "ingrese cadena: ";
	getline(cin,cadena);
	
	cout << "ingrese numero: ";
	int num;
	cin >> num;
	int len = cadena.length();
	int r = (len%num);


	if (r!=0)
	{
		for (int i=0; i< num - r; i++) { cadena.append("X"); }
	}

	string cadena2(cadena);
	for (int i=num; i< cadena2.length(); i+=num+1) { cadena2.insert(i,"*"); }
	
	int len2 = cadena2.length();
	char *ptr = new char[ len2 + 1 ];
	
	
	cadena2.copy( ptr, len2, 0 ); 
	ptr[ len2 ] = '\0'; 

	//cout << cadena.c_str() << endl;
	
 	char *tokenPtr = strtok(ptr, "*");
	
	int j = len/num;
	const char *almacen[j];
	int i=0;
	
	cout << "cadena con *" << endl;
	cout << cadena2 << endl; 
	
	cout << "cadena dividida" << endl;
	while ( tokenPtr != NULL )
	{
		almacen[i] = tokenPtr;
		cout << tokenPtr << '\n';
		tokenPtr = strtok( NULL, "*");
		i++;
	} 

	cout << "cadena de strings" << endl;
    for (int i = 0; i < j; i++)
        cout << almacen[i] << endl;
	
	delete [] ptr;
	return 0;
}