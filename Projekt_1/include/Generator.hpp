#pragma once
#include <cstdlib>
#include <string>
#include <algorithm> 
#include "Parameters.h"

using namespace std;

template <typename T> T wygenerujWartosc(); // Deklaracja szablonu funkcji, która będzie specjalizowana dla różnych typów danych

template <> inline int wygenerujWartosc<int>() {
    return (rand() % 100000) - 50000;     // zakres [-50000, 49999]
}

template <> inline float wygenerujWartosc<float>() {
    return ((static_cast<float>(rand()) / RAND_MAX) * 100000.0f) - 50000.0f; // zakres [-50000.0, 49999.9]
}

template <> inline unsigned int wygenerujWartosc<unsigned int>() {
    return static_cast<unsigned int>(rand() % 100000); // zakres [0, 99999]
}

template <> inline string wygenerujWartosc<string>() {
    string str = "";
	int dlugosc = 1 + (rand() % 15); // losowa długość od 1 do 15 znaków

    for (int i = 0; i < dlugosc; ++i) {
		char znak;
		znak = (char)(32 + rand() % 95); // zakres znaków ASCII od 32 do 126 
		str += znak;
    }
    return str;
}

// Funkcja wypelniajaca strukture danymi testowymi, generujac wartosci na podstawie typu danych i ustawien rozkladu
template <typename DataType, typename Structure>  
void wypelnijDaneTestowe(Structure& struktura) {

    size_t rozmiar = Parameters::structureSize;
    int rozklad = static_cast<int>(Parameters::distribution);
	struktura.reserve(rozmiar);

    DataType* bufor = new DataType[rozmiar];

    for (size_t i = 0; i < rozmiar; ++i) {
        bufor[i] = wygenerujWartosc<DataType>();
    }

    if (rozklad == 1) {
        sort(bufor, bufor + rozmiar);
    }
    else if (rozklad == 2) {
        sort(bufor, bufor + (rozmiar / 2));
    }
    else if (rozklad == 3) {
        sort(bufor, bufor + rozmiar, greater<DataType>());
    }

    for (size_t i = 0; i < rozmiar; ++i) {
        struktura.push_back(bufor[i]);
    }
    delete[] bufor;
}