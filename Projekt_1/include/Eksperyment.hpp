#pragma once
#include <iostream>
#include "Parameters.h"
#include "Reader_Writer.hpp"
#include "Weryfikator.hpp"
#include "Quick_sort.hpp"
#include "Shell_sort.hpp"
#include "Bucket_sort.hpp"
#include "Quick_sort_stos.hpp"
#include "Stoper.hpp"
#include "ZapisCSV.hpp"
#include "Generator.hpp"
#include "BST.hpp"

using namespace std;

// Funkcja przeprowadzająca badanie dla danego typu danych i struktury
template <typename DataType, typename Structure>
void przeprowadzenieBadania() {

	// Tlumaczenia dla czytelnosci wynikow
    string nazwaAlgorytmu = tlumaczAlgorytm(); 
    string nazwaTypu = tlumaczTyp();
    string nazwaStruktury = tlumaczStrukture();
    string nazwaPivota = tlumaczPivot();
    string nazwaOdstepu = tlumaczOdstep();
	string nazwaUlozenia = tlumaczUlozenie();

	// Sprawdzanie trybu działania programu czy to pojedynczy plik
    if (Parameters::runMode == Parameters::RunModes::singleFile) {
        Structure struktura;

        Tablica<DataType> bufor;
        if constexpr (is_same_v<Structure, BST<DataType>>) {
            if (!read<DataType>(Parameters::inputFile, bufor)) return;
        }
        else {
            // Normalne wczytywanie
            if (!read<DataType>(Parameters::inputFile, struktura)) return;
        }

        string plikWynikowy = Parameters::outputFile;
        if (plikWynikowy.empty()) {
            plikWynikowy = "wyniki.txt";
            cout << "Uwaga: Nie podano flagi -o! Zapisuje do: " << plikWynikowy << "\n";
        }
        else {
            cout << "Plik wynikowy txt: " << plikWynikowy << "\n";
        }

		string czasStart = pobierzAktualnyCzas(); // Pobieramy aktualny czas przed rozpoczęciem sortowania
        Stoper stoper;
		stoper.start(); // Uruchamiamy stoper

        switch (Parameters::algorithm) {  // Switch zarzadzajacy algorytmami
        case Parameters::Algorithms::quick:
            cout << "Algorytm: Quick Sort\n";
            if constexpr (is_same_v<Structure, Stos<DataType>>) {
                uruchomQuickSortStos(struktura, Parameters::pivot);
            }
            else if constexpr (is_same_v<Structure, BST<DataType>>) {
                for (size_t i = 0; i < bufor.getSize(); ++i) {
                    struktura.push_back(bufor[i]);
                }
            }
            else {
                uruchomQuickSort(struktura, Parameters::pivot);
            }
            break;
        case Parameters::Algorithms::shell:
            cout << "Algorytm: Shell Sort\n";
            uruchomShellSort(struktura, Parameters::shellParameter);
            break;
        case Parameters::Algorithms::bucket:
            cout << "Algorytm: Bucket Sort\n";
            uruchomBucketSort<DataType>(struktura);
            break;
        default:
            cout << "Nieznany algorytm\n";
            break;
        }

		stoper.stop(); // Zatrzymujemy stoper po zakończeniu sortowania
		string czasKoniec = pobierzAktualnyCzas(); // Pobieramy aktualny czas po zakończeniu sortowania

        // weryfikacja sortowania
		if (sprawdzCzyPosortowane(struktura)) cout << "Weryfikacja: struktura jest posortowana.\n";
        else cout << "Weryfikacja: struktura nie jest posortowana.\n";

		// Zapisujemy wartości do pliku wskazanego we fladze -o lub do domyślnego wyniki.txt
    	if (write(Parameters::outputFile, struktura)) {
    		cout << "Zapisano pomyslnie do pliku: " << Parameters::outputFile << "\n";
    	}
    	else {
    		cerr << "Nie udalo sie zapisac do pliku " << Parameters::outputFile << "!\n";
    	}
    }

	// Tryb badań 
    else{

		string plikWynikowy = Parameters::resultsFile; // Pobieramy nazwę pliku wynikowego z flagi -r
		// Jeśli nie podano flagi -r, ustawiamy domyślną nazwę pliku wynikowego
        if (plikWynikowy.empty()) {
            plikWynikowy = "wyniki.csv";
            cout << "Uwaga: Nie podano flagi -r! Zapisuje do: " << plikWynikowy << "\n";
        }
        else {
            cout << "Plik wynikowy CSV: " << plikWynikowy << "\n";
        }

		int liczbaPowtorzen = Parameters::iterations; // Pobieramy liczbę powtórzeń z flagi -n

        for (int i = 0; i < liczbaPowtorzen; ++i) {
            Structure struktura;

			// Wypełniamy strukture danymi testowymi (poza stoperem) 
            Tablica<DataType> bufor;
            if constexpr (is_same_v<Structure, BST<DataType>>) { // Jeżeli to BST to najpierw wypełniamy bufor, aby zamierzyc czas budowy BST
                wypelnijDaneTestowe<DataType, Tablica<DataType>>(bufor);
                if (bufor.getSize() == 0) break;
            }
			else { // Normalne wypełnianie struktury
                wypelnijDaneTestowe<DataType, Structure>(struktura);
                if (struktura.getSize() == 0) break;
            }

            string czasStart = pobierzAktualnyCzas(); // Pobieramy aktualny czas przed rozpoczęciem sortowania
            Stoper stoper;
            stoper.start(); // Uruchamiamy stoper

            // Switch zarządzający algorytmami
            switch (Parameters::algorithm) {
            case Parameters::Algorithms::quick:
                cout << "Algorytm: Quick Sort\n";
                if constexpr (is_same_v<Structure, Stos<DataType>>) {
                    uruchomQuickSortStos(struktura, Parameters::pivot);
                }
                else if constexpr (is_same_v<Structure, BST<DataType>>) {
                    for (size_t j = 0; j < bufor.getSize(); ++j) {
                        struktura.push_back(bufor[j]);
                    }
                }
                else {
                    uruchomQuickSort(struktura, Parameters::pivot);
                }
                break;

            case Parameters::Algorithms::shell:
                cout << "Algorytm: Shell Sort\n";
                uruchomShellSort(struktura, Parameters::shellParameter);
                break;

            case Parameters::Algorithms::bucket:
                cout << "Algorytm: Bucket Sort\n";
                uruchomBucketSort<DataType>(struktura);
                break;
            default:
                cout << "Nieznany algorytm\n";
                break;
            }

            stoper.stop(); // Zatrzymujemy stoper po zakończeniu sortowania
            string czasKoniec = pobierzAktualnyCzas(); // Pobieramy aktualny czas po zakończeniu sortowania

            string weryfikacja = sprawdzCzyPosortowane(struktura) ? "OK" : "BLAD"; // weryfikacja sortowania

            // Zapisujemy wyniki do pliku CSV
        	zapiszWynikDoCSV(Parameters::resultsFile, struktura.getSize(), nazwaStruktury, 
        	nazwaTypu,nazwaAlgorytmu, nazwaPivota, nazwaOdstepu, nazwaUlozenia, stoper.getCzasMikrosekundy(), 
        	stoper.getCzasMilisekundy(), stoper.getCzasSekundy(), czasStart, czasKoniec, weryfikacja);
        }
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
    case Parameters::DataTypes::tyleUnsignedInt:
        cout << "Typ danych: unsigned int\n";
        przeprowadzenieBadania<unsigned int, Container<unsigned int>>();
        break;
    case Parameters::DataTypes::typeFloat:
        cout << "Typ danych: float\n";
        przeprowadzenieBadania<float, Container<float>>();
        break;
    case Parameters::DataTypes::typeString:
        cout << "Typ danych: string\n";
        przeprowadzenieBadania<string, Container<string>>();
        break;
    default:
        cout << "Nieobslugiwany typ danych.\n";
        break;
    }
}