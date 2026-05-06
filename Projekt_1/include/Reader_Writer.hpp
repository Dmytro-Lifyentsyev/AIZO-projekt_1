#pragma once

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

template <typename T, typename Structure> // szablon funkcji do odczytu danych z pliku

bool read(const string& nazwaPliku, Structure& Struktura) { 
    ifstream plik(nazwaPliku); 

    if (!plik.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku: " << nazwaPliku << "\n";
        return false;
    }

	size_t iloscDanych; // zmienna do przechowywania liczby elementów do odczytania
	if (!(plik >> iloscDanych)) { // próba odczytania liczby elementów z pliku
        cerr << "Blad: Nie mozna odczytac liczby elementow.\n";
        return false;
    }

    for (size_t i = 0; i < iloscDanych; ++i) {
		T wartosc; // zmienna do przechowywania odczytanej wartości
		if (plik >> wartosc) { // próba odczytania wartości z pliku
            Struktura.push_back(wartosc);
        }
        else {
            cerr << "Blad: Koniec pliku w linii " << i + 2 << "\n";
            return false;
        }
    }

    plik.close();
    return true;
}

// Szablon funkcji do zapisu danych do pliku, przyjmuje nazwę pliku i strukturę danych, którą chcemy zapisać
template <typename Structure>
bool write(const string& nazwaPliku, Structure& struktura) {
    ofstream plik(nazwaPliku);

    if (!plik.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku do zapisu: " << nazwaPliku << "\n";
        return false;
    }

	// Zapisujemy rozmiar struktury na początku pliku
    plik << struktura.getSize() << "\n";

    // Pętla przechodząca przez całą strukturę i zapisująca liczby
    for (size_t i = 0; i < struktura.getSize(); ++i) {
        plik << struktura[i] << "\n"; 
    }

    plik.close();
    return true;
}