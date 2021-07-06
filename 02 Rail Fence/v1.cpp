#include <iostream>
#include <string>
using namespace std;
int main()
{
	string message = "hola como estas";
	int f = 3, c = message.length(); 
	int i, j, k;
	char text[f][c];
	
	for (i = 0; i < f; i++)
	{
		for (j = 0; j < c; j++)
		{
			text[i][j] = '?';
		}
	}
	
	int ctr = f*2-2;
	int gof = 0;
	bool down = true;
	

	for (k = 0; k < c; k++)
	{
		if (down == true)
		{
			text[gof][k] = message[k]; gof++;
			if (gof == f) { down = false; gof--; }
		}
		else 
		{
			gof--; text[gof][k] = message[k]; 
			if (gof == 0) { down = true; gof = 1; }
		}
	}
		
	/*for (i = 0; i < f; i++)
	{
		for (j = 0; j < c; j++)
		{
			cout << text[i][j];
		}
		cout << endl;
	}*/
	
	string scrpt = message;
	for (i = 0; i < scrpt.length(); i++) { scrpt[i] = ' '; }
	k = 0;
	for (i = 0; i < f; i++)
	{
		for (j = 0; j < c; j++)
		{
			if (text[i][j] != '?') { scrpt[k] = text[i][j]; k++;}
			
		}
	}
	cout << scrpt;
	
	////////////////////////////////////////////////////////////////////////////
	
	cout << scrpt;
	
	for (i = 0; i < f; i++)
	{
		for (j = 0; j < c; j++)
		{
			text[i][j] = '?';
		}
	}
	
	for (k = 0; k < c; k++)
	{
		if (down == true)
		{
			text[gof][k] = message[k]; gof++;
			if (gof == f) { down = false; gof--; }
		}
		else 
		{
			gof--; text[gof][k] = message[k]; 
			if (gof == 0) { down = true; gof = 1; }
		}
	}	
	
	

	
	
	
	return 0;
}