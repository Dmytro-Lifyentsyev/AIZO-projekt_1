#include <iostream>
#include "Tablica.h"
#include "Reader.h" 

using namespace std;

int main() {
    Tablica<int> tablica; // objekt tablicy 
    string nazwaPliku = "..\\..\\..\\dane.txt";

    cout << "Rozpoczynam test odczytu z pliku...\n";

    if (read<int>(nazwaPliku, tablica)) {
        cout << "Wczytano " << tablica.getSize() << " elementow.\n";
        cout << "Zawartosc tablicy:\n";
        for (size_t i = 0; i < tablica.getSize(); ++i) {
           cout << tablica[i] << " ";
        }
        cout << "\n";
    }
    else {
        cout << "Nie udalo sie wczytac danych.\n";
    }

    return 0;
}