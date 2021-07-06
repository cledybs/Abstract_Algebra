#include <iostream>
#include <string>
using namespace std;
class Algoritmo
{   
	private: 
		int f = 4, c;
		string text, scrpt, base;
	public:
		Algoritmo(string);
		void Emisor(string);
		void Receptor(string);
		
};
Algoritmo::Algoritmo(string text)
{
	this -> text = text;
	c = text.length();
	base = text; //proceso completo (cifrado y descifrado)
	scrpt = text;
	//comentar "scrpt = text" y utilizar alguna de las siguientes lineas si solo se quiere decifrar, el mensaje encriptado es secreto, por eso solo se puede hacer dentro de la clase
	//scrpt = "h otoacm saloes"; //devuelve "hola como estas", f=3
	//scrpt = "mam enbc aiadsari rrsdmeteere  a cd gae"; //devuelve "me diste ganas de cambiarme de carrera", f=4
	Emisor(text);
	Receptor(scrpt);
}
void Algoritmo::Emisor(string text)
{
	cout << text << endl;
	for (int i = 0; i < text.length(); i++) { scrpt[i] = '?'; }
	for (int i = 0; i < text.length(); i++) { base[i] = '?'; }
	for (int i = text.length(); i < f*c; i++) { base.append("?"); }
	cout << base << endl;

	bool down = true;
	int k = 0;
	for (int i = 0; i < c; i++)
	{
		if (down == true)
		{
			base[k*c+i] = text[i]; k++;
			if (k == f) { down = false; k--; }
		}
		else 
		{
			k--; base[k*c+i] = text[i]; 
			if (k == 0) { down = true; k = 1; }
		}
	}
	cout << base << endl;
	
	k = 0;
	for (int i = 0; i < f*c; i++)
	{
		if (base[i] != '?') { scrpt[k] = base[i]; k++;}
	}
	
	cout << scrpt << endl;
}
void Algoritmo::Receptor(string scrpt)
{
	for (int i = 0; i < text.length(); i++) { text[i] = '?'; }
	for (int i = 0; i < f*c; i++) { base[i] = '?'; }
	cout << scrpt << endl;
	cout << base << endl;
	
	//int dc01 = f*2-2, dc02 = 0;
	int fijo=f*2-2, dc=f*2-2;
	
	int k = 0;
	int pos = 0;
	for (int i = 0; i < f; i++)
	{
		pos=pos+i;
		base[pos] = scrpt[k]; k++;
		
		while (pos+dc < c*(i+1) and pos+dc+(fijo-dc) < c*(i+1))
		{
			if(dc!=0)
			{
				pos=pos+dc;
				base[pos] = scrpt[k];
				k++;	
			}
			
			if(dc!=fijo)
			{
				pos=pos+(fijo-dc);
				base[pos] = scrpt[k];
				k++;
			}
			
		}
		pos=c*(i+1);
		dc=dc-2;
	}
	
	cout << base << endl;
	
	bool down = true;
	k = 0;
	for (int i = 0; i < c; i++)
	{
		if (down == true)
		{
			text[i] = base[k*c+i]; k++;
			if (k == f) { down = false; k--; }
		}
		else 
		{
			k--; text[i] = base[k*c+i]; 
			if (k == 0) { down = true; k = 1; }
		}
	}
	
	cout << text << endl;
}
int main(int argc, char** argv)
{	
	string text = "hola como estas";
	
	Algoritmo Script(text);

	return 0;
}