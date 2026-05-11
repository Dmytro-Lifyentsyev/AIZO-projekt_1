#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>   
#include <ctime>   
#include <iomanip>  
#include <sstream>

using namespace std;

// Funkcja zapisująca wyniki do pliku CSV
inline void zapiszWynikDoCSV(const string& nazwaPliku, size_t rozmiar, const string& struktura, const string& typ, const string& algorytm, 
    const string& pivot, const string& odstep, const string& ulozenie, double czasus, double czasms, double czass, const string& czasStart, const string& czasKoniec,
    const string& weryfikacja) {

	ifstream plikTest(nazwaPliku); // Sprawdzamy, czy plik już istnieje
	bool plikIstnieje = plikTest.good(); // Jeśli plik istnieje, nie zapisujemy nagłówków kolumn
	plikTest.close(); // Zamykamy plik testowy

    ofstream plik(nazwaPliku, ios::app); // Otwieramy plik w trybie dopisywania (append)

    
    if (!plik.is_open()) {
        cerr << "Blad: Nie udalo sie otworzyc pliku " << nazwaPliku << " do zapisu!\n";
        return;
    }

	// Jeśli plik nie istnieje, zapisuje nagłówki kolumn
    if (!plikIstnieje) {
        plik << "Rozmiar Danych;Struktura;Typ Danych;Algorytm;Pivot;Odstep;Ułożenie elementów;Czas us;Czas ms;Czas s;Start Sortowania;Koniec Sortowania;Weryfikacja\n";
    }

	// Zapisujemy dane do pliku
    plik << rozmiar << ";"
        << struktura << ";"
        << typ << ";"
        << algorytm << ";"
        << pivot << ";"
        << odstep << ";"
		<< ulozenie << ";"
        << czasus << ";"
        << czasms << ";"
        << czass << ";"
        << czasStart << ";"
        << czasKoniec << ";"
		<< weryfikacja << "\n";

    plik.close();
}

// Funkcja pobierająca aktualny czas w formacie "YYYY-MM-DD HH:MM:SS"
inline string pobierzAktualnyCzas() {
    auto teraz = chrono::system_clock::now();
    time_t czas_t = chrono::system_clock::to_time_t(teraz);
    tm czas_tm;

#if defined(_WIN32)
    localtime_s(&czas_tm, &czas_t);
#else
    localtime_r(&czas_t, &czas_tm);
#endif

    stringstream ss;
    ss << put_time(&czas_tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// Tłumaczenia dla czytelności wyników
inline string tlumaczAlgorytm() {
    switch (Parameters::algorithm) {
    case Parameters::Algorithms::quick:  return "Quick_Sort";
    case Parameters::Algorithms::shell:  return "Shell_Sort";
    case Parameters::Algorithms::bucket: return "Bucket_Sort";
    default: return "Inny_Algorytm";
    }
}

inline string tlumaczPivot() {
    if (Parameters::algorithm != Parameters::Algorithms::quick) return "Brak";
    switch (Parameters::pivot) {
    case Parameters::Pivots::left:   return "Lewy";
    case Parameters::Pivots::middle: return "Srodkowy";
    case Parameters::Pivots::right:  return "Prawy";
    case Parameters::Pivots::random: return "Losowy";
    default: return "Nieznany";
    }
}

inline string tlumaczOdstep() {
    if (Parameters::algorithm != Parameters::Algorithms::shell) return "Brak";
    switch (Parameters::shellParameter) {
    case Parameters::ShellParameters::option1: return "Ciag Shella";
    case Parameters::ShellParameters::option2: return "Ciag Knutha";
    default: return "Nieznany";
    }
}

inline string tlumaczUlozenie() {
    switch (Parameters::distribution) {
    case Parameters::Distribution::random: return "Losowe";
    case Parameters::Distribution::ascending: return "Posortowane rosnąco";
	case Parameters::Distribution::ascending50Per: return "50% Posortowane rosnąco";
    case Parameters::Distribution::descending: return "Posortowane malejąco";
    default: return "Nieznane";
    }
}

inline string tlumaczTyp() {
    switch (Parameters::dataType) {
    case Parameters::DataTypes::typeInt:   return "INT";
    case Parameters::DataTypes::tyleUnsignedInt:   return "UNSIGNED INT";
    case Parameters::DataTypes::typeFloat: return "FLOAT";
    case Parameters::DataTypes::typeString:return "STRING";
    default: return "INNY_TYP";
    }
}

inline string tlumaczStrukture() {
    switch (Parameters::structure) {
    case Parameters::Structures::array:      return "Tablica";
    case Parameters::Structures::singleList: return "Lista_Jednokierunkowa";
    case Parameters::Structures::doubleList: return "Lista_Dwukierunkowa";
	case Parameters::Structures::stack:       return "Stos";
	case Parameters::Structures::binaryTree:  return "BST";
    default: return "Inna_Struktura";
    }
}