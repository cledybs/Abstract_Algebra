#include <iostream>
using namespace std;
string alfabeto = "abcdefghijklmnopqrstuvwxyz";
//string alfabeto = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,;:-()[]123456789";
int alflen = alfabeto.length();
int euclides(int r1, int r2)
{
	int r;
	while (r2>0)
	{
		int q; 
		q = r1/r2;	
		if (r1 >= 0) { r = r1 - q*r2; }
		else { r = r1 - (q-1)*r2; }
		
		r1 = r2; r2 = r;
	}
	return r1;
}
int euclides_extd(int r1, int r2, int r, bool n)
{
	int s1 = 1, s2 = 0, s; 
	int t1 = 0, t2 = 1 , t;
	while (r2>0)
	{
		int q; 
		q = r1/r2;	
		
		r = r1 - q*r2;
		r1 = r2; r2 = r;
		
		s = s1 - q*s2;
		s1 = s2; s2 = s;
		
		t = t1 - q*t2;
		t1 = t2; t2 = t;
	}
	if (n == 0) return s1;
	else if (n == 1) return t1;
	else return 0;
	
}
int inversa (int a, int b)
{
	int d = euclides(a,b);
	//cout << "d:\t" << d << endl;
	int x = euclides_extd(a,b,d,0);
	if (x < 0) 
	{   
		int q = x/alflen; x = x - (q-1)*alflen; 
	}
	//cout << "x:\t" << x << endl;
	return x;
}
class afin
{   
	private: 
		int a, b; //claves
		string plaintext, ciphertext;
		
	public:
		afin(string);
		void emisor(string,int,int);
		void receptor(string,int,int);
		
};
afin::afin(string plaintext)
{
	this -> plaintext = plaintext;
	ciphertext = plaintext;
	
	int ver_coprim;
	do
	{
		a = rand() % alflen;
		ver_coprim = euclides(a,alflen);
	}
	while (ver_coprim != 1);
	
	b = rand() % alflen;
	//int a = 7, b = 18;
	cout << "a:\t" << a << endl;
	cout << "b:\t" << b << endl;
	emisor(plaintext,a,b);
	receptor(ciphertext,a,b); 

}
void afin::emisor(string plaintext, int a, int b)
{
	cout << "EMISOR" << endl;
	for(int i=0; i<plaintext.length(); i++) { ciphertext[i] = ' '; }
	
	cout << "mensaje decifrado:\t" << plaintext << endl;
	
	for (int i = 0; i < plaintext.length(); i++)
	{
		for (int j = 0; j < alflen; j++)
		{
			if (plaintext[i] == alfabeto[j])
			{
				cout << j << endl;
				int r = a*j + b;
				cout << r << endl;
				if (r >= alflen) { int q = r/alflen; r = r - q*alflen; }
				cout << r << endl;
				ciphertext[i] = alfabeto[r];
			}
		}
	}
	
	cout << "mensaje cifrado:\t" << ciphertext << endl;
}
void afin::receptor(string ciphertext, int a, int b)
{
	cout << "RECEPTOR" << endl;
	for(int i=0; i<ciphertext.length(); i++) { plaintext[i] = ' '; }

	cout << "mensaje cifrado:\t" << ciphertext << endl;
	
	a = inversa(a,alflen);
	for (int i = 0; i < plaintext.length(); i++)
	{
		for (int j = 0; j < alflen; j++)
		{
			if (ciphertext[i] == alfabeto[j])
			{
				int r = a*(j-b);
				if (r < 0) 
				{  
					int q = r/alflen; 
					r = r - (q-1)*alflen; 
				}
				else if (r >= alflen) { int q = r/alflen; r = r - q*alflen; }
				plaintext[i] = alfabeto[r];
			}
		}
	}

	cout << "mensaje decifrado:\t" << plaintext << endl;
}
int main()
{
	string text = "wolfpack";
	//string text = "La primera edicion alemana data de 1953. A instancias de su editor, Hans Waltmann, Guardini accedio a publicar en edicion aparte algunas de las lecciones de etica que impartia por este tiempo en la Universidad de Munich con gran esmero y extraordinaria asistencia de alumnos[2].";
	afin message(text);
	
	return 0;
}