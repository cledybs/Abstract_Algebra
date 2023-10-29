#include <iostream>
using namespace std;
void Div(int a, int n)
{
	int q, r;
	if (a >= 0)
	{
		q = a/n;
		r = a - q*n;
	}
	else
	{
		q = a/n;
		r = a - (q-1)*n;
	}
	cout << r;
	}
int main ()
{
	int a, n;
	cout << "a: " << endl; cin >> a;
	cout << "n: " << endl; cin >> n;
	Div(a,n);
	return 0;
}

	