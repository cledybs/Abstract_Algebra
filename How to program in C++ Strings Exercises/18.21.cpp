//18.21
#include <iostream>
#include <cstring>
using namespace std;
int main()
{
	string cadena;
	getline(cin,cadena);
	
	string signos = ".,;:";
	
	int k = cadena.find_first_of(signos);

	int pos = 0;

 	while ( k != string::npos )
 	{
 		cadena.replace( k, 1, " " );
	 	k = cadena.find_first_of( signos, k + 1 );
 	} 
 	
 	cout << cadena << endl;
 	
	int len = cadena.length();
	char *ptr = new char[ len + 1 ];

	cadena.copy( ptr, len, 0 ); 
	ptr[ len ] = '\0'; 

	//cout << cadena.c_str() << endl;

 	char *tokenPtr = strtok(ptr, " " );

	while ( tokenPtr != NULL )
	{
		cout << tokenPtr << '\n';
		tokenPtr = strtok( NULL, " " );
	} 
	
	delete [] ptr;
	
	return 0;
}