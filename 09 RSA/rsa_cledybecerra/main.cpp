#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <string>
#include <sstream>
#include <random>
#include <NTL/ZZ.h>

using namespace NTL;
using namespace std;

ZZ exponer(const ZZ& a, const ZZ& e)
{
   if (e == 0) return ZZ(1);
   long k = NumBits(e);
   ZZ res;
   res = 1;
   for (long i = k-1; i >= 0; i--)
   {
      res = (res*res);
      if (bit(e, i) == 1) res = (res*a);
   }
    return res;
}
class rsa
{
  public:
    rsa(int);
    rsa(ZZ,ZZ);
    ZZ modulo(ZZ,ZZ);
    ZZ exponenciacion(ZZ,ZZ);
    ZZ resto_chino(ZZ);
    string estandar_str(ZZ,ZZ);
    string cifrar(string);
    string descifrar(string);
    ZZ euclides(ZZ,ZZ);
    ZZ euclides_extd(ZZ,ZZ);
    ZZ inversa(ZZ,ZZ);
    ZZ generar_aleatorio(ZZ);
    bool test_primalidad(ZZ);
    ZZ e;
    ZZ N;

  private:
    ZZ d;
    ZZ phN;
    ZZ p;
    ZZ q;
    string alfabeto = "abcdefghijklmnopqrstuvwxyz ";


};
rsa::rsa(int bits)
{
  cout << "constructor del receptor" << endl;
  ZZ x = exponer(ZZ(2),ZZ(bits-1));
  cout << x;
  do
    p = generar_aleatorio(x);
  while(test_primalidad(p) != true);

  do
    q = generar_aleatorio(x);
  while(test_primalidad(q) != true);

  N = p * q;
  phN = (p-1) * (q-1);
  //N = ; phN = 120;
  //N = 153964669,   phN = 153938944;
  cout << "N = " << N << '\t' << "phN = " << phN << endl;

  do
    e = generar_aleatorio(phN);
  while(euclides(e,phN) != 1);
  //e = 23;
  //e = 101525391;
  d = modulo(inversa(e,phN),phN);
  cout << "e = " << e << '\t' << "d = " << d << endl; cout << endl;
}
rsa::rsa(ZZ e, ZZ N)
{
  cout << "constructor del emisor" << endl;
  this -> e = e;
  this -> N = N;
  cout << "e = " << e << '\t' << "N = " << N << endl; cout << endl;
}
ZZ rsa::modulo(ZZ a, ZZ b)
{
  //cout << "modulo" << endl;
  cout << a << " mod " << b << " = ";
  ZZ q = a/b;
  if (a < 0)
    a = a - (q-1) * b;
  else
    a = a - q * b;
  cout << a << endl;
  return a;
}
ZZ rsa::exponenciacion(ZZ a, ZZ b)
{
  cout << "exponenciacion" << endl;
  cout << a << " ^ " << b << " mod " << N << endl;
  ZZ res = ZZ(1);
  while (b != 0)
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
ZZ rsa::resto_chino(ZZ)
{
  return ZZ(1);
}
string rsa::estandar_str(ZZ n, ZZ estandar_int)
{
  ostringstream y;
  y << n;
  string elem = y.str();
  //string elem = to_string(n);
  while(elem.size() != estandar_int)
    elem = "0" + elem;

  return elem;
}
string rsa::cifrar(string M)
{
  cout << "cifrar" << endl;
  cout << "Q = (P ^ e) mod N" << endl; cout << endl;
  cout << M << endl;
  string P;
  string estandar_elem;
  ostringstream y;
  y << alfabeto.size();
  estandar_elem = y.str();
  //estandar_elem = to_string(alfabeto.size());

  for(int i = 0; i < M.size(); i++)
  {
    for(int j = 0; j < alfabeto.size(); j++)
    {
      if(alfabeto[j] == M[i])
      {
        P.append(estandar_str(ZZ(j),ZZ(estandar_elem.size())));
        break;
      }
    }
  }
  cout << P << endl;
  string Q;
  ostringstream z;
  z << N;
  estandar_elem = z.str();
  //estandar_elem = to_string(N);
  for(long i = 0; i < P.size(); i+=estandar_elem.size()-1)
  {
    string bloque = P.substr(i, estandar_elem.size()-1);
    cout << bloque << endl;
    stringstream x(bloque);
    ZZ bloque_entero = ZZ(0);
    x >> bloque_entero;
    ZZ C = exponenciacion(bloque_entero,e);
    Q.append(estandar_str(C,ZZ(estandar_elem.size())));
  }

  return Q;
}
string rsa::descifrar(string M)
{
  cout << "descifrar" << endl;
  cout << "P = (Q ^ d) mod N" << endl; cout << endl;
  cout << M << endl;
  string estandar_elem;
  string Q;
  ostringstream y;
  y << N;
  estandar_elem = y.str();
  //estandar_elem = to_string(N);
  for(long i = 0; i < M.size(); i+=estandar_elem.size())
  {
    string bloque = M.substr(i, estandar_elem.size());
    cout << bloque << endl;
    stringstream x(bloque);
    ZZ bloque_entero = ZZ(0);
    x >> bloque_entero;
    ZZ C = exponenciacion(bloque_entero,d);
    Q.append(estandar_str(C,ZZ(estandar_elem.size()-1)));
  }
  cout << Q << endl;
  string P;
  ostringstream z;
  z << alfabeto.size();
  estandar_elem = z.str();
  //estandar_elem = to_string(alfabeto.size());
  for(long i = 0; i < Q.size(); i+=estandar_elem.size())
  {
    string bloque = Q.substr(i, estandar_elem.size());
    stringstream x(bloque);
    long bloque_entero = 0;
    x >> bloque_entero;
    P.push_back((alfabeto[bloque_entero]));
  }
  return P;
}
ZZ rsa::euclides(ZZ r1, ZZ r2)
{
  cout << "euclides" << endl;
  ZZ r, q;
	while (r2 > 0)
	{
		q = r1/r2;
		r = modulo(r1,r2);
		r1 = r2; r2 = r;
	}
  cout << "mcd = " << r1 << endl;
	return r1;
}
ZZ rsa::euclides_extd(ZZ r1, ZZ r2)
{
  cout << "euclides_extd" << endl;
  //cout << r1 << "(x) + " << r2 << "(y) = 1" << endl;
  cout << "a(x) + b(y) = 1" << endl;
  ZZ r = ZZ(1);
  ZZ s1 = ZZ(1), s2 = ZZ(0), s;
	ZZ t1 = ZZ(0), t2 = ZZ(1) , t;
	while (r2>0)
	{
		ZZ q;
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
ZZ rsa::inversa(ZZ a, ZZ b)
{
  cout << "inversa" << endl;
  ZZ x = euclides(a,b);
  if (x == 1)
    x = euclides_extd(a,b);
  else
    x = 0;
  x = modulo(x,phN);
	return x;
}
ZZ rsa::generar_aleatorio(ZZ num)
{
    cout << num;
  //cout << "aleatorio" << endl;
  //default_random_engine random_num(time(NULL));
  //uniform_int_distribution<ZZ> rotar(ZZ(1),num);
  //this_thread::sleep_for(chrono::seconds(1));
  //ZZ x = rotar(random_num);
  //srand(time(0));
  //ZZ x = rand() % num;
  ZZ x = RandomBnd(num);
  cout << "aleatorio = " << x << endl;
  return x;
}
bool rsa::test_primalidad(ZZ num)
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
  rsa Elle(16);
  cout << "e: " << Elle.e << endl;
  cout << "N: " << Elle.N << endl;
  cout << Elle.descifrar("118993052112699985048314440136307455074719446084005279130463055099333766113479856087671233111062930153484273");
  //rsa Cledy(Elle.e,Elle.N);
    //rsa Cledy(ZZ(),ZZ());
    //string plaintext = "this illustrates an important point about ntls programming interface for every function in ntl there is a procedural version that stores its result in its first argument the reason for using the procedural variant is efficieny on every iteration through the above loop";
    //string Q = Cledy.cifrar(plaintext);
    //cout << "Q = " << Q << endl; cout << endl;
  /*string P = "notthesameanymore";

  string Q = Cledy.cifrar(P);
  cout << "Q = " << Q << endl; cout << endl;

  P = Elle.descifrar(Q);
  cout << "P = " << P << endl;*/


  return 0;
}
