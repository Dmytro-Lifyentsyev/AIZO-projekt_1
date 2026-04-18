#include <string>
#include <fstream>
#include <iostream>

template <typename T, typename Structure> // szablon funkcji do odczytu danych z pliku

bool read(const std::string& nazwaPliku, Structure& Struktura) { 
    std::ifstream plik(nazwaPliku); 

    if (!plik.is_open()) {
        std::cerr << "Blad: Nie mozna otworzyc pliku: " << nazwaPliku << "\n";
        return false;
    }

	size_t iloscDanych; // zmienna do przechowywania liczby elementów do odczytania
	if (!(plik >> iloscDanych)) { // próba odczytania liczby elementów z pliku
        std::cerr << "Blad: Nie mozna odczytac liczby elementow.\n";
        return false;
    }

    for (size_t i = 0; i < iloscDanych; ++i) {
		T wartosc; // zmienna do przechowywania odczytanej wartości
		if (plik >> wartosc) { // próba odczytania wartości z pliku
            Struktura.push_back(wartosc);
        }
        else {
            std::cerr << "Blad: Koniec pliku w linii " << i + 2 << "\n";
            return false;
        }
    }

    plik.close();
    return true;
}