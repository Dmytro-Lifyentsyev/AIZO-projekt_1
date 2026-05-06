#pragma once
#include <iostream>
#include "Parameters.h"
#include "Reader_Writer.hpp"
#include "Weryfikator.hpp"
#include "Quick_sort.hpp"
#include "Stoper.hpp"
#include "ZapisCSV.hpp"

using namespace std;

// Funkcja przeprowadzająca badanie dla danego typu danych i struktury
template <typename DataType, typename Structure>
void przeprowadzenieBadania() {

	// Tłumaczenia dla czytelności wyników
    string nazwaAlgorytmu = tlumaczAlgorytm(); 
    string nazwaTypu = tlumaczTyp();
    string nazwaStruktury = tlumaczStrukture();
    string nazwaPivota = tlumaczPivot();

	// Sprawdzanie trybu działania programu czy to pojedynczy plik
    if (Parameters::runMode == Parameters::RunModes::singleFile) {
        Structure struktura;
        if (!read<DataType>(Parameters::inputFile, struktura)) return;

		string czasStart = pobierzAktualnyCzas(); // Pobieramy aktualny czas przed rozpoczęciem sortowania
        Stoper stoper;
		stoper.start(); // Uruchamiamy stoper

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
		string czasKoniec = pobierzAktualnyCzas(); // Pobieramy aktualny czas po zakończeniu sortowania

		string weryfikacja = sprawdzCzyPosortowane(struktura) ? "OK" : "BLAD"; // Sprawdzamy, czy dane są posortowane i zapisujemy wynik weryfikacji

		// Zapisujemy wyniki do pliku określonego we fladze -r
        if (!Parameters::resultsFile.empty()) {
            zapiszWynikDoCSV(Parameters::resultsFile, struktura.getSize(), nazwaStruktury, nazwaTypu,
                nazwaAlgorytmu, nazwaPivota, stoper.getCzasMikrosekundy(), czasStart, czasKoniec, weryfikacja);
        }
        else 
            cout << "Nie podano flagi -r! Wyniki nie zostana zapisane do pliku CSV.\n";
		
        // Zapisujemy wartości do pliku wskazanego we fladze -o
        if (!Parameters::outputFile.empty()) {
            if (write(Parameters::outputFile, struktura)) {
                cout << "Zapisano pomyslnie do pliku: " << Parameters::outputFile << "\n";
            }
            else {
                cerr << "Nie udalo sie zapisac do pliku " << Parameters::outputFile << "!\n";
			}
        }
    	else 
			cout << "Nie podano flagi -o! Posortowane dane nie zostana zapisane do pliku.\n";
    }

	// Tryb badań 
    else if (Parameters::runMode == Parameters::RunModes::benchmark) {

		string plikWynikowy = Parameters::resultsFile; // Pobieramy nazwę pliku wynikowego z flagi -r
		// Jeśli nie podano flagi -r, ustawiamy domyślną nazwę pliku wynikowego i informujemy użytkownika
        if (plikWynikowy.empty()) {
            plikWynikowy = "wyniki_domyslne.csv";
            cout << "Uwaga: Nie podano flagi -r! Zapisuje do: " << plikWynikowy << "\n";
        }
        else {
            cout << "Plik wynikowy CSV: " << plikWynikowy << "\n";
        }

		int liczbaPowtorzen = Parameters::iterations; // Pobieramy liczbę powtórzeń z flagi -n

        for (int i = 0; i < liczbaPowtorzen; ++i) {
            Structure struktura;

            string czasStart = pobierzAktualnyCzas(); // Pobieramy aktualny czas przed rozpoczęciem sortowania
            Stoper stoper;
            stoper.start(); // Uruchamiamy stoper

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
            string czasKoniec = pobierzAktualnyCzas(); // Pobieramy aktualny czas po zakończeniu sortowania

            string weryfikacja = sprawdzCzyPosortowane(struktura) ? "OK" : "BLAD";

            // Zapisujemy wyniki do pliku CSV
                zapiszWynikDoCSV(Parameters::resultsFile, struktura.getSize(), nazwaStruktury, nazwaTypu,
                    nazwaAlgorytmu, nazwaPivota, stoper.getCzasMikrosekundy(), czasStart, czasKoniec, weryfikacja);
        }
    }

	// tryb pomocy
    else if (Parameters::runMode == Parameters::RunModes::help) {
        Parameters::help();
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