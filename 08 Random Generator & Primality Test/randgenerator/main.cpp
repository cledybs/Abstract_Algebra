#include <iostream>
#include<NTL/ZZ.h>
#include <bits/stdc++.h>
using namespace std;
using namespace NTL;

/*void linearCongruentialMethod(
    ZZ Xo, ZZ m, ZZ a, ZZ c,
    vector<ZZ>& randomNums,
    long noOfRandomNums)
{

    // Initialize the seed state
    randomNums[0] = Xo;

    // Traverse to generate required
    // numbers of random numbers
    for (long i = 1; i < noOfRandomNums; i++) {
        // Follow the linear congruential method
        randomNums[i] = ((randomNums[i - 1] * a) + c) % m;
    }
}
int main()
{
    ZZ Xo = ZZ(5); // Seed value
    ZZ m = ZZ(7); // Modulus parameter
    ZZ a = ZZ(3); // Multiplier term
    ZZ c = ZZ(3); // Increment term

    // Number of Random numbers
    // to be generated
    long noOfRandomNums = 10;

    // To store random numbers
    vector<ZZ> randomNums(noOfRandomNums);

    // Function Call
    linearCongruentialMethod(
        Xo, m, a, c, randomNums, noOfRandomNums);

    // Print the generated random numbers
    for (long i = 0; i < noOfRandomNums; i++) {
        cout << randomNums[i] << " ";
    }

    return 0;
}*/
ZZ linearCongruentialMethod(ZZ Xo, ZZ m, ZZ a, ZZ c){
    ZZ res;
    res = Xo;
    res = ((res * a) + c) % m;

    return res;
}
int main()
{
    ZZ Xo = ZZ(5); // Seed value
    ZZ m = ZZ(7); // Modulus parameter
    ZZ a = ZZ(3); // Multiplier term
    ZZ c = ZZ(3); // Increment term

    ZZ res = linearCongruentialMethod(Xo, m, a, c);
    cout << res;

    return 0;
}
