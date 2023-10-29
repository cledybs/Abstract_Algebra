#include <cmath>
#include <iostream>
#include<NTL/ZZ.h>
using namespace std;
using namespace NTL;
ZZ modulo(ZZ a, ZZ b)
{
ZZ q = a/b;
if (b < ZZ(0)) { q++; }
return a - b * q;
}
ZZ expo_modular(ZZ a, ZZ n){
    ZZ result;
    result = ZZ(1);
    while( n != ZZ(0)) {
        if(modulo(n,ZZ(2))!=0)
            result = result*a;
        a = a*a;
        n >>= 1;
    }
    return result;
}
bool Lucas_Lehmer(ZZ p) {

  ZZ num = expo_modular(ZZ(2), p) - 1;

  ZZ nextval = modulo(ZZ(4),num);

  for (ZZ i = ZZ(1); i < p - 1; i++)
    nextval = modulo((nextval * nextval - 2),num);

  return (nextval == ZZ(0));
}

int main() {
  ZZ p = ZZ(77);

  ZZ num = expo_modular(ZZ(2), p) - 1;

  if (Lucas_Lehmer(p))
    cout << num << " es primo.";
  else
    cout << num << " no es primo.";

  return 0;
}
