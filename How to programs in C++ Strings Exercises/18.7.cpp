//18.7
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string alfabeto = "abcdefghijklmnopqrstuvwxyz";
	//char alfabeto[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	
	string text ("alone uu");
	string scrpt (text);
	int clave = 13;
	
	//a)
	for(int i=0; i<text.length(); i++) { scrpt[i] = ' '; }
	
	cout << text << endl;
	
	for (int k=0; k<text.length(); k++)
	{
	for (int i=0; i<26; i++)
	{
		if (alfabeto[i] == text[k])
		{
			if (i+clave>=26) { scrpt[k] = alfabeto[i+clave-26]; }
			else { scrpt[k] = alfabeto[i+clave]; }
			break;
		}
	}
	}
	cout << scrpt << endl;
	
	//b)
	
	for(int i=0; i<text.length(); i++) { text[i] = ' '; }
	
	cout << scrpt << endl;
	for (int k=0; k<scrpt.length(); k++)
	{
	for (int i=0; i<26; i++)
	{
		if (alfabeto[i] == scrpt[k])
		{
			if (i-clave<0) { text[k] = alfabeto[i-clave+26]; }
			else { text[k] = alfabeto[i-clave]; }
			break;
		}
	}
	}
	cout << text << endl;

	return 0;
}