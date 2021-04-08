#include <iostream>
#include <string>
using namespace std;
class Algoritmo
{   
	private: 
		int f = 4, c = 10;
		string scrpt, text;
	public:
		Algoritmo(string);
		void Emisor(string);
		void Receptor(string);
};
Algoritmo::Algoritmo(string text)
{
	this -> text = text;
	scrpt = text; //proceso completo (cifrado y descifrado)
	//comentar "scrpt = text" y utilizar alguna de las siguientes lineas si solo se quiere decifrar, el mensaje encriptado es secreto, por eso solo se puede hacer dentro de la clase
	//scrpt = "hotomalosa   e cs"; //devuelve "hola como estas", f=3, c=6
	//scrpt = "mam enbc aiadsari rrsdmeteere  a cd gae"; //devuelve "me diste ganas de cambiarme de carrera", f=4, c=10
	Emisor(text);
	Receptor(scrpt);
}
void Algoritmo::Emisor(string text)
{
	cout << text << endl;
	for (int i = 0; i < text.length(); i++) { scrpt[i] = ' '; }
	for (int i = text.length(); i < f*c; i++) { scrpt.append(" "); }

	int ctr = 0;
	for (int i = 0; i < c; i++)
	{
		for (int j = i; j < f*c; j+=c)
		{
			scrpt[ctr] = text[j];
			if (j >= text.length()) { scrpt[ctr] = ' ';}
			ctr++;
		}
	}

	cout << scrpt << endl;
}
void Algoritmo::Receptor(string scrpt)
{
	for (int i = 0; i < text.length(); i++) { text[i] = ' '; }
	cout << scrpt << endl;
	
	int ctr = 0;
	for (int i = 0; i < c; i++)
	{
		for (int j = i; j < f*c; j+=c)
		{
			text[j] = scrpt[ctr];
			ctr++;
		}
	}

	cout << text << endl;
}
int main(int argc, char** argv)
{	
	string text = "me diste ganas de cambiarme de carrera";
	
	Algoritmo Script(text);

	return 0;
}
