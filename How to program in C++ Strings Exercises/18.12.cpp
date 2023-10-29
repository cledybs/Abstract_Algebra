//18.12
#include <iostream>
#include <cstring>

using namespace std;
int main()
{
	string text("mano");
	string scrpt(text);
	int len = text.length();
	
	for (int i=0; i<len; i++) { scrpt[i] = 'x'; }
	
	cout << scrpt << endl;
	
	string colgado= " O /|\\ | / \\";

	
	int colgado_ctr = 0;
	string letra;
	
	
	while (true)
	{
		if (colgado_ctr==7)
		{
			cout << "colgado" << endl;
			break;
		}
		if (scrpt == text)
		{
			cout << "ganaste" << endl;
			break;
		}
		
		getline(cin,letra);
		int k = text.find(letra);
		
		if (k!=string::npos)
		{
			
			cout << "yes" << endl;
			while (k!=string::npos)
			{
				string aux(" ");
				aux[0] = text[k];
				scrpt.replace(k, 1, aux); 
				k = text.find(letra,k+1);
			}
			cout << scrpt << endl;
		}
		else
		{
			cout << "no" << endl;
			colgado_ctr++;
			
			int j = 0;
			for (int i=0; i<colgado.length(); i++)
			{
				if (colgado[i]!=' ') { j++; }
				cout << colgado[i];
				if (j==colgado_ctr)
				{
					cout << endl;
					break;
				}
				if(i==2 or i==5 or i==8 or i==11) { cout << endl;}
			}
		}
	}
	
	return 0;
}