#pragma once
#include <iostream>
#include "Parameters.h"
#include "Reader.hpp"
#include "Weryfikator.hpp"
#include "Quick_sort.hpp"
#include "Stoper.hpp"

using namespace std;

// Funkcja przeprowadzająca eksperyment dla danego typu danych i struktury
template <typename DataType, typename Structure>
void przeprowadzenieBadania() {
	Structure struktura; // Tworzymy instancję struktury danych

    if (!read<DataType>(Parameters::inputFile, struktura)) {
        cout << "Nie udalo sie wczytac pliku: " << Parameters::inputFile << "\n";
        return;
    }
    cout << "Wczytano " << struktura.getSize() << " elementow\n";

	Stoper stoper; // Tworzymy instancję stopera
	stoper.start(); // Uruchamiamy stoper przed rozpoczęciem sortowania

    // Switch zarządzający algorytmami
    switch (Parameters::algorithm) {
    case Parameters::Algorithms::quick:
        cout << "Algorytm: Quick Sort\n";
        uruchomQuickSort(struktura, Parameters::pivot);
        break;

    case Parameters::Algorithms::shell:
        cout << "Algorytm: Shell Sort\n";
        break;

    case Parameters::Algorithms::bucket:
        cout << "Algorytm: Bucket Sort\n";
        break;
    default:
        cout << "Nieznany algorytm\n";
        break;
    }

	stoper.stop(); // Zatrzymujemy stoper po zakończeniu sortowania
    cout << "Sortowanie zakonczone\n";
    cout << "Czas operacji: " << stoper.getCzasMikrosekundy() << " mikrosekund ("
        << stoper.getCzasMilisekundy() << " milisekund)\n";

	if (sprawdzCzyPosortowane(struktura)) { // Weryfikujemy, czy struktura jest posortowana
        cout << "OK\n";
    }
    else {
        cout << "Blad\n";
    }
}

// Funkcja uruchamiająca eksperyment dla wybranej struktury danych, wybierając odpowiedni typ danych na podstawie ustawień
template <template <typename> class Container>
void uruchomDlaWybranejStruktury() {
    switch (Parameters::dataType) {
    case Parameters::DataTypes::typeInt:
        cout << "Typ danych: int\n";
        przeprowadzenieBadania<int, Container<int>>();
        break;
    case Parameters::DataTypes::typeFloat:
        cout << "Typ danych: float\n";
        przeprowadzenieBadania<float, Container<float>>();
        break;
    default:
        cout << "Nieobsługiwany typ danych.\n";
        break;
    }
}