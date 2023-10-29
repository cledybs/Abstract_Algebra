#include <bits/stdc++.h>
#include <windows.h>
#include <chrono>
#include <psapi.h>
#include <bitset>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

ZZ mod(ZZ a,ZZ b){
    ZZ r=a-(b*(a/b));
    if(r<0)r=b-r;
    return r;
}
bool even(ZZ a){
    ZZ r=(a>>1)<<1;
    if(r<0) r=ZZ(2)+r;
    return r==a;
}
ZZ ValAbs(ZZ a){
    if (a<0) return (a*-1);
    return a;
}
ZZ mod_power(ZZ a, ZZ n, ZZ m){
    ZZ result;
    result = ZZ(1);
    while( n != ZZ(0)) {
        if(!even(n))
            result = mod(result*a,m);
        a = mod(a*a,m);
        n >>= 1;
    }
    return result;
}
int ModInteger(int a, int b){
    int r=a-(b*(a/b));
    if(r<0)
        r=b+r;
    return r;
    }
ZZ power(ZZ a, ZZ n){
    ZZ result;
    result = ZZ(1);
    while( n != ZZ(0)) {
        if(mod(n, ZZ(2)) != 0)
            result = result*a;
        a = a*a;
        n >>= 1;
    }
    return result;
}

int contador=0;
string processInfo;

void fillWithMemoryInfo() {
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    if (EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {//obtiene los procesos en aProcesses
        cProcesses = cbNeeded / sizeof(DWORD);// Calcula cuantos procesos fueron retornados
        for (long i = 100; i < cProcesses; i++){
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
            if (NULL != hProcess){
                PROCESS_MEMORY_COUNTERS pmc;
                if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
                    processInfo+=(to_string(pmc.PageFaultCount)+to_string(pmc.WorkingSetSize)+
                    to_string(pmc.QuotaPagedPoolUsage)+to_string(pmc.QuotaNonPagedPoolUsage)+to_string(pmc.PeakPagefileUsage));
                }
            }
            CloseHandle(hProcess);
        }
    }
}
vector<int> generateSeed(){
    if((processInfo.size()<contador+15)||processInfo.empty()){
        processInfo.clear();
        fillWithMemoryInfo();
        contador=0;
    }
    vector<int> k;
    for(int i=0, j=contador;i<5;i++,j+=3){
        int n=stoi(processInfo.substr(j,3));
        while(n>255) n>>=1;
        while(n<128) n<<=1;
        k.push_back(n);
    }
    contador+=15;
    return k;
}
vector<bool> RC4(vector<int> semilla){
    vector<int> Or;
    {//permite que S solo pertenezca a este scope
    vector<int> S;
    for(int i=0;i<256;i++) S.push_back(i);
    {//permite que k solo exista en este scope, optimiza memoria
        vector<int> K;
        for(int i=0,k=0;i<=51;i++)
            for(int j=0;j<5;j++,k++)
                K.push_back(semilla[j]);
        for(int i=0,f=0;i<256;i++){
            f= ModInteger(f + S[i] + K[i], 256);
            swap(S[i],S[f]);
        }
    }
    for(int i = 0; i < S.size(); i++)
        cout << S.at(i) << ';';
    cout << endl;
    for(int i=0,f=0,k=0;k<8;k++){
        i= ModInteger(i + 1, 256);
        f= ModInteger(f + S.at(i), 256);
        swap(S.at(i),S.at(f)); //hasta aqui el PRNG
        Or.push_back(S.at(ModInteger(S.at(i) + S.at(f), 256)));//t, solo hay 8 elementos en Or que derivan de S en PRNG
        cout << Or.at(k) << ';';
    }
    }

    cout << endl;
    vector<bool> out;
    for(int i=0;i<8;i++){
        bitset<8> aux(Or[i]);
        for(int j=0;j<8;j++)
            out.push_back(aux[j]);
    }
    return out;
}
void izqRotate(vector<bool> &vec, int times){
    vec.insert(vec.end(),vec.begin(),vec.begin()+times);
    vec.erase(vec.begin(),vec.begin()+times);
}
int PC_1[]={56,48,40,32,24,16,8,0,57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,60,52,44,36,28,20,12,4,27,19,11,3};
int PC_2[]={13,16,10,23,0,4,2,27,14,5,20,9,22,18,11,3,25,7,15,6,26,19,12,1,40,51,30,36,46,54,29,39,50,44,32,47,43,48,38,55,33,52,45,41,49,35,28,31};
int rotaciones[]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1,1,1,2,2,2,2};
vector<bool> DES(int bits=1024){
    vector<bool> K;//para guardar todas las k
    {
    vector<bool>k=RC4(generateSeed());
    int nBits=bits/48+1;
    vector<bool> c; vector<bool> d;
    for(int i=0;i<28;i++) c.push_back(k.at(PC_1[i]));
    for(int i=28;i<56;i++) d.push_back(k.at(PC_1[i]));
    for(int i=0;i<nBits;i++){
        izqRotate(c,rotaciones[i]);
        izqRotate(d,rotaciones[i]);
        vector<bool> both(c.begin(),c.end());
        both.insert(both.end(),d.begin(),d.end());
        for(int i=0;i<48;i++) K.push_back(both.at(PC_2[i]));
    }
    }
    K.resize(bits);
    K[0]=1; K[bits-1]=1;
    return K;
}
ZZ Random_Number(vector<bool> vec){
    ZZ salida(0);
    ZZ i(1);
    for(vector<bool>::reverse_iterator it=vec.rbegin();it!=vec.rend();++it){
        if(*it) salida+=i;
        i<<=1;
    }
    return salida;
}

bool Miller_Rabin(ZZ d, ZZ n){

    ZZ a; a=2;
    ZZ x = mod_power(a, d, n);
    if (x == 1  || x == n-1)return true;
    while (d != n-1){

        x = mod((x * x), n);
        d *= 2;
        if (x == 1)return false;
        if (x == n-1)return true;
    }

    return false;
}
bool isPrime(ZZ n){
    ZZ k; k=0;
    if (n <= 1 or n == 4)return false;
    if (n <= 3)return true;

    ZZ d = n - 1;
    while (even(d)){
        //d /= 2;
        d >>= 1;
        k++;
    }
    for (int i = 0; i < k+1; i++)
         if (!Miller_Rabin(d, n))
              return false;

    return true;
}

ZZ prime(ZZ n){//Encuentra el primo mas cercano a un numero aleatorio
    //ZZ n= op.generate_random(bits);
    ZZ a= mod(n, ZZ(6));
    n-=a+ZZ(5); //para obtener la forma 6n+5
    //Los numeros primos tienen la forma de 6n+1 y 6n+5, no necesariamente todos los numeros obtenidos con esa
    if(isPrime(n)) return n;//Si es primo retorna ese valor
    else{//Caso contrario busca los siguientes numeros de la forma 6n+1 y 6n+5 hasta encontrar un primo
        while(true){
            n+=2;
            if(isPrime(n)) return n;
            n+=4;
            if(isPrime(n)) return n;
        }
    }
}

int main(){

    ZZ num, p;

    /*for(int i = 0; i < 20; i++)
    {
        num = Random_Number(DES(1024));
        if(isPrime(num))
            cout << num << " es primo\n" << endl;
        else
            cout << num << " no es primo\n" << endl;
    }
//    ZZ num;
//    num = conv<ZZ>("55079");
//    cout << isPrime(num) << endl;


*/
    cout << "-------------sin modificar----------------------------------"<<endl;
   num = Random_Number(DES(1024));

   if(isPrime(num))
       cout << num << " es primo\n" << endl;
   else
       cout << num << " no es primo\n" << endl;

    /*cout << "-------------------------------\n\nmodificado: -------------------------"<<endl;
    p= prime(num);

    if(isPrime(p))
       cout << p << " es primo\n" << endl;
   else
       cout << p << " no es primo\n" << endl;*/


    return 0;
}
