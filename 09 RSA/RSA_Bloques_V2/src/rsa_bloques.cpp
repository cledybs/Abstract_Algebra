#include "rsa_bloques.h"
prime_generator opr;
rsa_bloques::rsa_bloques(int bits){///Receptor
    // /*
    p=conv<ZZ>("116392169431889610812057559048578059851819452679538223557873114371623702861632886362132309798941624758818954799539051248194871125611862571617124313250123978312750036779646706593551448631068915189467445175511195942904849280430621049860387420606295281370323929429324122814212181642868936837093363501896708497431");
    q=conv<ZZ>("135730484312091421803594051580244147075537286062899513100406435443797320416080886058762796596740646082163255766665258354739632478234198216010038451581142506545162787637718057721118027379695029627514936027497979815865520110765657929031527899440364581805646256708287689553033446989260099150570805845698263614571");
    e = conv<ZZ>("118831771744614267884036168004006690066504645352011370129391916764391780293048861973550184496682081579622056644769615336918162659304713710594754645459116635721407805930018503066008815302178554106599701452495570354353770312280468040655537534370080874682166156791589728565770080678017522614928691686579641699591");// */
    /*
    p=findProbablyPrimeClosest(bits);
    q=findProbablyPrimeClosest(bits);//*/
    n=p*q;
    Phi=(p-1)*(q-1);
     /*
   do{
       e=opr.generate_random(1024);
   }while(!Existe_Inversa(e,Phi));//*/
    d=inversa(e, Phi);
    cout<<"VALORES \n\nn: "<<n<<"\n\ne: "<<e<<endl;
    cout<<"\n\np: "<<p<<"\n\nq: "<<q<<"\n\nPhi: "<<Phi<<"\n\nd: "<<d<<endl;
}

rsa_bloques::rsa_bloques(ZZ n,ZZ e){
    this->n=n;
    this->e=e;
}

string rsa_bloques::encrypt(string mensaje){
    int digit=to_string(alfabeto.size()).size();
    string str;
    string cero(digit,'0');
    for(int i=0;i<mensaje.size();i++){
        size_t pos=alfabeto.find(mensaje.at(i));
        int len=to_string(pos).size();
        if(len<digit) str+=cero.substr(0,digit-len);
        str+=to_string(pos);
    }
    digit=ZZtoStr(n).size()-1;
    while(modint(str.size(),digit)) str+="22";
    int digitN=digit+1;
    string out;
    for(int i=0;i<str.size();i+=digit){
        ZZ p(conv<ZZ>(str.substr(i,digit).c_str()));
        p= Power_mod(p, e, n);
        string ceros((digitN-ZZtoStr(p).size()),'0');
        out=out+ceros+ZZtoStr(p);
    }
    return out;
}

string rsa_bloques::decrypt(string mensaje){
    string salida;
    int digitN=ZZtoStr(n).size();
    int digit=digitN-1;
    for(int i=0;i<mensaje.size();i+=digitN){
        ZZ c(conv<ZZ>(mensaje.substr(i,digitN).c_str()));
        c= TRC(c);
        string ceros((digit-ZZtoStr(c).size()),'0');
        salida+=ceros+ZZtoStr(c);
    }
    digit=to_string(alfabeto.size()).size();
    string outLetters;
    for(int i=0;i<salida.size();i+=digit){
        outLetters+=alfabeto.at(stoi(salida.substr(i,digit)));
    }
    return outLetters;
}

string rsa_bloques::ZZtoStr(ZZ z){
    stringstream ss;
    ss<<z;
    return ss.str();
}

ZZ rsa_bloques::TRC(ZZ M){
    ZZ q1= inversa(modulo(q, p), p);
    ZZ a1= Power_mod(modulo(M, p), modulo(d, p - 1), p);//Dp,dp,p
    ZZ q2= inversa(modulo(p, q), q);
    ZZ a2= Power_mod(modulo(M, q), modulo(d, q - 1), q);
    return modulo(modulo(a1 * q * q1, n) + modulo(a2 * p * q2, n), n);
}
