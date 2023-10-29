#include <iostream>
#include <string>
using namespace std;

const string alfabeto = "abcdefghijklmnopqrstuvwxyz";

string brute_force(string message) {
    string decrypted = "";

    for (int i = 1; i < 26; i++) {
        for (int j = 0; j < message.size(); j++) {
            char currentChar = message[j];
            unsigned int a = string::npos;

            for (int k = 0; k < alfabeto.size(); k++) {
                if (alfabeto[k] == currentChar) {
                    a = k;
                    break;
                }
            }

            if (a != string::npos) {
                if (a < i) a = a + alfabeto.size() - i;
                else a -= i;

                decrypted += alfabeto[a];
            } else {
                decrypted += " ";
            }
        }
    }

    for (int j = 0; j < 26; ++j) {
        cout << "con la clave: " << j + 1 << ": " << decrypted.substr(j * (message.length()), message.length()) << endl;
    }
}

int main() {
    string mensaje;
    cout << "ingrese un mensaje: ";
    getline(cin, mensaje);

    brute_force(mensaje);

    return 0;
}
