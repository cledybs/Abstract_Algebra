#include <iostream>
#include <string>
using namespace std;
class caesar
{   
	private: 
		int clave;
		string scrpt, text, scrpt_copy;
		//char alfabeto[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
		string alfabeto = "abcdefghijklmnopqrstuvwxyz";
		int a, n, q, r;
	public:
		caesar(string,int);
		void emisor(string);
		void receptor(string);
		void intruso(string);
		
};
caesar::caesar(string text, int clave)
{
	this -> clave = clave;
	this -> text = text;
	scrpt = text;
	n = alfabeto.length();
	//scrpt_copy = scrpt; //B) HABILITAR ESTA LINEA Y COMENTAR LINEA 27, SI SE QUIERE DESCUBRIR EL MENSAJE YA TENIENDO EL MENSAJE CIFRADO EN EL MAIN
	
	emisor(text); //A) COMENTAR ESTA LINEA SI SOLO SE QUIERE PROBAR EL DECIFRADO (YA SE TIENE LA CLAVE Y EL MENSAJE EN EL MAIN)
	scrpt_copy = scrpt; //A) HABILITAR ESTA LINEA Y COMENTAR LINEA 24, SI SE QUIERE DESCUBRIR EL MENSAJE EN PLENO PROCESO DE ENVIO EMISOR-RECEPTOR
	receptor(scrpt); 
	intruso(scrpt_copy);
}
void caesar::emisor(string text)
{
	cout << "EMISOR" << endl;
	for(int i=0; i<text.length(); i++) { scrpt[i] = ' '; }
	
	cout << "mensaje decifrado: " << text << endl;
	
	for (int k=0; k<text.length(); k++)
	{
		for (int i=0; i<alfabeto.length(); i++)
		{
			if (alfabeto[i] == text[k])
			{
				a = i + clave;
				//r = a%n;
				q = a/n;
				r = a - q*n;
				
				scrpt[k] = alfabeto[r]; 
				break;
			}
		}
	}
	cout << "mensaje cifrado: " << scrpt << endl;
}
void caesar::receptor(string scrpt)
{
	//FUNCIONA CON CLAVE
	cout << "RECEPTOR" << endl;
	for(int i=0; i<text.length(); i++) { text[i] = ' '; }
	
	cout << "mensaje cifrado: " << scrpt << endl;
	for (int k=0; k<scrpt.length(); k++)
	{
		for (int i=0; i<alfabeto.length(); i++)
		{
			if (alfabeto[i] == scrpt[k])
			{
				r = i;
				q = (clave-r+n)/n;
				a = r + q*n;
				
				//cout << "r: " << r << "\t" << "q: " << q << endl;
				int pos = a - clave;
				if (pos == n) {	pos = 0;}
				text[k] = alfabeto[pos]; 
				break;
			}
		}
	}
	cout << "mensaje decifrado: " << text << endl;
}
void caesar::intruso(string scrpt_copy)
{
	//FUNCIONA SIN CLAVE
	cout << "INTRUSO" << endl;
	/*int ctr;
	for (int k=0; k<scrpt.length(); k++)
	{
		ctr = 0;
		for (int i=0; i<scrpt.length(); i++)
		{
			if (scrpt[i] == scrpt[k])
			{
				ctr++;
			}
		}
	}*/
	for (int k=0; k<alfabeto.length(); k++)
	{
		for (int i=0; i<scrpt_copy.length(); i++)
		{
			for (int j=0; j<alfabeto.length(); j++)
			{
				if (scrpt_copy[i] == alfabeto[j])
				{
					if (j+k < 26)
					{
						text[i] = alfabeto[j+k];
					}
					else
					{
						text[i] = alfabeto[(j+k)%n];
					}
				}
			}
		}
		cout << text << "\t" << n-k << endl;
	}
}
int main()
{
	int clave;
	string text;
	//string text = "mira que bonito tiene la chinita los ojitos"; //A)
	//string text = "t wzde xj xtyo  wzde lww xj xzypj"; //B)
	getline(cin,text);
	cout << "clave: "; cin >> clave; cout << endl;
	
	caesar mensaje(text,clave);
	
	return 0;
}
