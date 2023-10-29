#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

class rsa
{
  public:
    rsa(int);
    //rsa(int,int);
    //virtual ~rsa(void);
    int modulo(int,int);
    int exponenciacion(int,int);
    int resto_chino(int);
    //string cifrar(string);
    //string descifrar(string);
    int emisor(int);
    int receptor(int);
    int euclides(int,int);
    int euclides_extd(int,int);
    int inversa(int,int);
    int generar_aleatorio(int);
    bool test_primalidad(int);
  
  private:
    int d;
    int e;
    int N;
    int phN;
    int p;
    int q;
    //string alfabeto = "abcdefghijklmnopqrstuvwxyz";
    //int n = alfabeto.size();
};
rsa::rsa(int bits)
{
  cout << "1" << endl;
  do
    p = generar_aleatorio(pow(2,bits-1)-1);
  while(test_primalidad(p) != true);

  do
    q = generar_aleatorio(pow(2,bits-1)-1);
  while(test_primalidad(q) != true);

  N = p * q;
  phN = (p-1) * (q-1);
  //cout << N << '\t' << phN << endl;
  do
    e = generar_aleatorio(phN);
  while(euclides(e,phN) != 1);

  d = modulo(inversa(e,phN),phN);
  cout << e << '\t' << d << endl;
}
int rsa::modulo(int a, int b)
{
  cout << "2" << endl;
  int q = a/b; 
  if (a < 0)
    a = a - (q-1) * b;
  else
    a = a - q * b;
  return a;
}
int rsa::exponenciacion(int a, int b)
{
  cout << "3" << endl;
  int res = 1;
  while (b)
  {
    if (b % 2 != 0)
      res = res * a;
    res = modulo(res,N);
    b = b >> 1;
    a = a * a;
  }
  return res;
}
int rsa::resto_chino(int)
{
  return 1;
}
//string rsa::cifrar(string plaintext)
int rsa::emisor(int P)
{
  cout << "4" << endl;
  int Q = modulo(exponenciacion(P,e),N);
  return Q;
}
//string rsa::descifrar(string ciphertext)
int rsa::receptor(int Q)
{
  cout << "5" << endl;
  int P = modulo(exponenciacion(Q,d),N);
  return P;
}
int rsa::euclides(int r1, int r2)
{
  cout << "6" << endl;
  int r, q;
	while (r2 > 0)
	{
		q = r1/r2;	
		r = modulo(r1,r2);
		r1 = r2; r2 = r;
	}
	return r1;
}
int rsa::euclides_extd(int r1, int r2)
{
  cout << "7" << endl;
  int r = 1;
  int s1 = 1, s2 = 0, s; 
	//int t1 = 0, t2 = 1 , t;
	while (r2>0)
	{
		int q; 
		q = r1/r2;	
		
		r = modulo(r1,r2);
		r1 = r2; r2 = r;
		
	  s = modulo(s1,s2);
		s1 = s2; s2 = s;
		
		//t = modulo(t1,t2);
		//t1 = t2; t2 = t;
	}
	return s1;
}
int rsa::inversa(int a, int b)
{
  cout << "8" << endl;
  int x;
  int d = euclides(a,b);
  if (d == 1)
	  x = euclides_extd(a,b);
  else
    x = 0;
	x = modulo(x,N);
	
	return x;
}
int rsa::generar_aleatorio(int num)
{
  cout << "9" << endl;
  srand(time(0));
  return 1 + rand() % num;
}
bool rsa::test_primalidad(int num)
{
  cout << "10" << endl;
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
  //string plaintext = "";
  int M = 48;

  rsa RSA(4);

  int Q = RSA.emisor(M);
  M = RSA.receptor(Q);

  cout << Q << endl;
  cout << M << endl;

  return 0;
}