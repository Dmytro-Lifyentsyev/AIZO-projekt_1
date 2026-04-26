#include <iostream>
#include <string>
#include "Tablica.h"
#include "Reader.h"    
#include "Weryfikator.h" 
#include "Quick_sort.h"  

using namespace std;

int main() {
    Tablica<int> tablica; // obiekt tablicy 
    string nazwaPliku = "..\\..\\..\\dane.txt";

    if (read<int>(nazwaPliku, tablica)) {
        cout << "Wczytano " << tablica.getSize() << " elementow.\n";

    	cout << "Przed sortowaniem: ";
    	for (size_t i = 0; i < tablica.getSize(); ++i) {
    		cout << tablica[i] << " ";
    	}

        uruchomQuickSort(tablica);
        cout << "Sortowanie zakonczone.\n";

        if (sprawdzCzyPosortowane(tablica)) {
            cout << "WYNIK: Pozytywny.\n";
        }
        else {
            cout << "WYNIK: Blad";
        }

    	cout << "Po posortowaniu: ";
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