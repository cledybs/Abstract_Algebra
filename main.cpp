//la version antigua estaba pensada para el cifrado de 3*6, en esta ya se puede cifrar y descifrar cualquier oracion, sin embargo quiero hacerle mejoras
#include <iostream>
#include <string>
using namespace std;
class Algoritmo
{   
	private: 
		int f = 4, c = 10;
		string scrpt;
	public:
		void Emisor(string);
		void Receptor(string);
};
void Algoritmo::Emisor(string text)
{
	scrpt = text;
	cout << text << endl;
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
void Algoritmo::Receptor(string text) //en lugar de texto deberia recibir el scrpt, pero este es privado, entonces si solo queremos descifrar tendriamos que darle un valor al scrpt
{
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
	
	
	Algoritmo Script;
	Script.Emisor(text); //aqui llamo a ambas funciones, sin embargo solo quiero llamar a una Comunicar() y que en esta llame a esas dos
 	Script.Receptor(text);

	return 0;
}
