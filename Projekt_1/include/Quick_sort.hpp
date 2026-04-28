#pragma once
#include "Parameters.h" 
#include <cstdlib>      

// Funkcja do podziału tablicy na dwie części i zwrócenia indeksu pivotu
template <typename Structure>
int partition(Structure& struktura, int low, int high, Parameters::Pivots rodzajPivota) {

	// Wybór pivota w zależności od ustawienia 
    if (rodzajPivota == Parameters::Pivots::left) {
        // Skrajny lewy
        std::swap(struktura[low], struktura[high]);
    }
    else if (rodzajPivota == Parameters::Pivots::middle) {
        // Środkowy
        int mid = low + (high - low) / 2;
        std::swap(struktura[mid], struktura[high]);
    }
    else if (rodzajPivota == Parameters::Pivots::random) {
        // Losowy
        int randIdx = low + rand() % (high - low + 1);
        std::swap(struktura[randIdx], struktura[high]);
    }

	// Skrajny prawy jest domyślny
	auto pivot = struktura[high]; 
	int i = (low - 1); // granica, wszystko po lewej jest mniejsze lub równe pivotowi

	for (int j = low; j <= high - 1; ++j) { // iterujemy po elementach od low do high-1
		if (struktura[j] <= pivot) { // jeśli element jest mniejszy lub równy pivotowi
			i++; // przesuwamy granicę w prawo
			std::swap(struktura[i], struktura[j]); // zamieniamy element na pozycji i z elementem na pozycji j
        }
    }
	std::swap(struktura[i + 1], struktura[high]); // umieszczamy pivot na właściwej pozycji

	return (i + 1); // zwracamy indeks pivotu, który jest teraz na swoim miejscu
}

// Rekurencyjna funkcja Quick Sorta
template <typename Structure>
void quickSort(Structure& struktura, int low, int high, Parameters::Pivots rodzajPivota) { 
    if (low < high) {   
        int pi = partition(struktura, low, high, rodzajPivota); 
		quickSort(struktura, low, pi - 1, rodzajPivota); // Rekurencyjne sortowanie elementów przed i po podziale
        quickSort(struktura, pi + 1, high, rodzajPivota); // Rekurencyjne sortowanie elementów przed i po podziale
    }
}

// Funkcja pomocnicza do uruchomienia Quick Sorta na całej strukturze
template <typename Structure> 
void uruchomQuickSort(Structure& struktura, Parameters::Pivots rodzajPivota) {
    if (struktura.getSize() > 0) {
        quickSort(struktura, 0, (int)struktura.getSize() - 1, rodzajPivota); 
    }
}