#define _WIN32_WINNT 0x0501
#include <bits/stdc++.h>
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <chrono>
#include <psapi.h>
#include <bitset>
#include<NTL/ZZ.h>
//#pragma comment(linker, "/DEFAULTLIB:psapi.lib")
using namespace std;
using namespace NTL;

int modINT(int a,int b){
    int r=a-(b*(a/b));
    if(r<0)
        r=b+r;
    return r;
    }

void PrintMemoryInfo(DWORD processID,vector <unsigned long> &al)
{
    HANDLE hProcess;
    PROCESS_MEMORY_COUNTERS pmc;
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
        PROCESS_VM_READ,
        FALSE, processID);
    if (NULL == hProcess)
        return;

    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
    {

        al.push_back(pmc.PageFaultCount);
        al.push_back(pmc.WorkingSetSize);
        al.push_back(pmc.QuotaPeakPagedPoolUsage);
        al.push_back(pmc.QuotaPeakNonPagedPoolUsage);
        al.push_back(pmc.QuotaNonPagedPoolUsage);
    }

    CloseHandle(hProcess);
}

vector<int>LLenarK(){
   DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;vector <unsigned long> al;

    if (EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
       cProcesses = cbNeeded / sizeof(DWORD);
    for (i = 0; i < cProcesses; i++)
    {
        PrintMemoryInfo(aProcesses[i],al);
    }
    }
    string k1;
    for(int i=5; i<26;i+=5){
        int t=(int)(al[i]);
        string temp=to_string(t);
        k1+=temp;}
        k1=k1.substr(0,15);
    vector <int> k;
    for(int i=0;i<k1.size();i+=3){
        string temp=k1.substr(i,3);
        int t=stoi(temp);
        while(t>255)
            t>>=1;
        while(t<128)
            t<<=1;
        k.push_back(t);
    }
    vector<int>K;
    for(int i=0;i<256;){
        for(int j=0;j<k.size();j++,i++)
            K.push_back(k[j]);}
    return K;
}
vector<int> RC4(){
    vector<int>k=LLenarK();
    vector<int>s;
    vector<int>Ori;
    vector<int>Or;
    for(int i=0;i<256;i++)
        s.push_back(i);
    int f=0;
    for(int i=0;i<256;i++){
        f=modINT(f+k.at(i)+s.at(i),256);
        swap(s.at(i),s.at(f));
    }
    f=0;
    for(int j=0,i=0;j<8;j++){
        i=modINT(i+1,256);
        f=modINT(f+s.at(i),256);
        swap(s.at(i),s.at(f));
        int t=modINT(s.at(i)+s.at(f),256);
        Ori.push_back(s.at(t));
    }
    for(int i=0;i<Ori.size();i++){
        bitset<8>temp=Ori[i];
        string tp=temp.to_string();
        for(int j=0;j<8;j++){
            int tmp=stoi(tp.substr(j,1));
            Or.push_back(tmp);
        }
    }
    return Or;
}
void DesplazamientoIzq(int num,vector<int>&c){
    for(int i=0;i<num;i++){
        c.push_back(c.at(i));
    }
    c.erase(c.begin(),c.begin()+num);
}
vector<int>DES(int bits){
    vector<int>Kfin;
    vector<int>K=RC4();
    int PC_1[56]={57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
    int PC_2[48]={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
    int rot[]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1,1,1,2,2,2,2};
    vector<int>Ki;
    vector<int>c;
    vector<int>d;
    for(int i=0;i<56;i++){
        Ki.push_back(K.at(PC_1[i]-1));
    }
    for(int n=0;n<28;n++)
        c.push_back(Ki[n]);
    for(int n=28;n<56;n++)
        d.push_back(Ki[n]);
    int i=0;
    int vueltas=(bits/48)+1;
    while(i<vueltas){
        vector<int>cd;
        vector<int>fin;
        DesplazamientoIzq(rot[i],c);
        DesplazamientoIzq(rot[i],d);
        cd.insert(cd.begin(),c.begin(),c.end());
        cd.insert(cd.end(),d.begin(),d.end());
        for(int z=0;z<48;z++){
            fin.push_back(cd.at(PC_2[z]-1));
        }
        Kfin.insert(Kfin.end(),fin.begin(),fin.end());
        i++;
    }
    int quit=bits-(vueltas*48);
    Kfin.resize(bits);
    if(!Kfin[0]) Kfin[0]=1;
    if(!Kfin[Kfin.size()-1]) Kfin[Kfin.size()-1]=1;
    return Kfin;
}
ZZ NumeroAleatorio(int bits){
    vector<int>K=DES(bits);
    ZZ num(0);ZZ i(1);
    for(vector<int>::reverse_iterator it=K.rbegin();it!=K.rend();++it){
        if(*it)
            num+=i;
        i<<=1;
    }
    return num;
}
int main(){
    //cout << "hola" << endl;
    cout << NumeroAleatorio(8192) << endl;
}
