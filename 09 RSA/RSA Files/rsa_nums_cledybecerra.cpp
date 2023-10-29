#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;
string alfabeto = "abcdefghijklmnopqrstuvwxyz";

class rsa
{
  public:
    rsa(int);
    rsa(int,int);
    int modulo(int,int);
    int exponenciacion(int,int);
    int resto_chino(int);
    int cifrar(int);
    int descifrar(int);
    int euclides(int,int);
    int euclides_extd(int,int);
    int inversa(int,int);
    int generar_aleatorio(int);
    bool test_primalidad(int);
    int e;
    int N;
  
  private:
    int d;
    int phN;
    int p;
    int q;

};
rsa::rsa(int bits) 
{
  cout << "constructor del receptor" << endl;
  do
    p = generar_aleatorio(pow(2,bits-1)-1);
  while(test_primalidad(p) != true);

  do
    q = generar_aleatorio(pow(2,bits-1)-1);
  while(test_primalidad(q) != true);

  N = p * q;
  phN = (p-1) * (q-1);
  N = 143; phN = 120;
  cout << "N = " << N << '\t' << "phN = " << phN << endl;

  do
    e = generar_aleatorio(phN);
  while(euclides(e,phN) != 1);
  e = 23; 
  d = modulo(inversa(e,phN),phN);
  cout << "e = " << e << '\t' << "d = " << d << endl; cout << endl;
}
rsa::rsa(int e, int N) 
{
  cout << "constructor del emisor" << endl;
  this -> e = e;
  this -> N = N;
  cout << "e = " << e << '\t' << "N = " << N << endl; cout << endl;
}
int rsa::modulo(int a, int b)
{
  //cout << "modulo" << endl;
  cout << a << " mod " << b << " = ";
  int q = a/b; 
  if (a < 0)
    a = a - (q-1) * b;
  else
    a = a - q * b;
  cout << a << endl;
  return a;
}
int rsa::exponenciacion(int a, int b)
{
  cout << "exponenciacion" << endl;
  cout << a << " ^ " << b << " mod " << N << endl;
  int res = 1;
  while (b)
  {
    cout << "---------------------------------------------------" << endl;
    a = modulo(a,N);
    cout << res << " * " << a << " = ";
    if (b % 2 == 1)
      res *= a;
    cout << res << '\t' << '\t'; 
    res = modulo(res,N);
    b = b >> 1;
    a = a * a;
  }
  cout << "---------------------------------------------------" << endl;
  cout << '\n';
  return res;
}
int rsa::resto_chino(int)
{
  return 1;
}
//string rsa::cifrar(string plaintext)
int rsa::cifrar(int P)
{
  cout << "cifrar" << endl;
  cout << "Q = (P ^ e) mod N" << endl; cout << endl;
  int Q = exponenciacion(P,e);
  return Q;
}
//string rsa::descifrar(string ciphertext)
int rsa::descifrar(int Q)
{
  cout << "descifrar" << endl;
  cout << "P = (Q ^ d) mod N" << endl; cout << endl;
  int P = exponenciacion(Q,d);
  return P;
}
int rsa::euclides(int r1, int r2)
{
  cout << "euclides" << endl;
  int r, q;
	while (r2 > 0)
	{
		q = r1/r2;	
		r = modulo(r1,r2);
		r1 = r2; r2 = r;
	}
  cout << "mcd = " << r1 << endl;
	return r1;
}
int rsa::euclides_extd(int r1, int r2)
{
  cout << "euclides_extd" << endl;
  //cout << r1 << "(x) + " << r2 << "(y) = 1" << endl;
  cout << "a(x) + b(y) = 1" << endl;
  int r = 1;
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
  cout << "a(" << s1 << ") + b(" << t1 << ") = 1" << endl;
	return s1;
}
int rsa::inversa(int a, int b)
{
  cout << "inversa" << endl;
  int x = euclides(a,b);
  if (x == 1)
    x = euclides_extd(a,b);
  else
    x = 0;
  x = modulo(x,phN);
	return x;
}
int rsa::generar_aleatorio(int num)
{
  //cout << "aleatorio" << endl;
  srand(time(0));
  int x = 1 + rand() % num;
  //cout << "aleatorio = " << x << endl;
  return x;
}
bool rsa::test_primalidad(int num)
{
  bool primo = true;
  if (num == 0 or num == 1)
    primo = false;
  else 
  {
    for (int i = 2; i <= num / 2; i++) 
    {
      if (num % i == 0)
        primo = false; break;
    }
  }
  return primo;
}

int main()
{
  rsa Elle(8);
  rsa Cledy(Elle.e,Elle.N);
  
  int P = 10;

  int Q = Cledy.cifrar(P);
  cout << "Q = " << Q << endl; cout << endl;
  
  P = Elle.descifrar(Q);
  cout << "P = " << P << endl;

  return 0;
}