#include <iostream>
#include <string>
using namespace std;
class Algoritmo
{
	private: 
		int f = 3, c = 6;
		string text, scrpt = "                  ";
	public:
		Algoritmo(string);
		void Emisor();
		void Receptor();
};
Algoritmo::Algoritmo(string text)
{
	this -> text = text;
}
void Algoritmo::Emisor()
{
	cout << text << endl;
	//for (int i = 0; i < text.length(); i++) { scrpt[i] = ' '; }
	int ctr = 0;
	for (int i = 0; i < c; i++)
	{
		for (int j = i; j < text.length(); j+=c)
		{
			//cout << ctr << " " << j << endl;
			scrpt[ctr] = text[j];
			ctr++;
		}
	}
	for (int i = 0; i < text.length(); i++) { text[i] = ' '; }
	cout << scrpt << endl;
}
void Algoritmo::Receptor()
{
	cout << scrpt << endl;
	
	int ctr = 0;
	for (int i = 0; i < c; i++)
	{
		for (int j = i; j < text.length(); j+=c)
		{
			//cout << ctr << " " << j << endl;
			text[j] = scrpt[ctr];
			ctr++;
		}
	}

	cout << text << endl;
}
int main()
{	
	string text = "hola como estas";
	
	Algoritmo Script(text);
	Script.Emisor();
	Script.Receptor();
	
	
	return 0;
}
/*
int main()
{
	int f = 3, c = 6;
	char emisortxt[f][c], receptortxt[f][c];
	string text = "dejamevivir en paz";
	
	cout << text <<endl;
	int ctr = 0;
	for (int i = 0; i < 3; i++)
	{              
		for (int j = 0; j < 6; j++)
		{
			if (ctr <= text.length())
			{
				emisortxt[i][j] = text[ctr];
			}                   
			else 
			{
				emisortxt[i][j] = ' ';
			}
			ctr++;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << emisortxt[i][j];
		}
	}
	cout << endl;	
	int k1 = 0, k2 = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (k1 > 2) {k1 = 0; k2++;}
			receptortxt[i][j] = emisortxt[k1][k2];
			k1++; 
		}
	}
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << receptortxt[i][j];
		}
	}
	return 0;
}
*/