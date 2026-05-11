#pragma once
#include <cstdlib>
#include <Stos.hpp>

// Sortowanie Quick Sort przerobione specjalnie dla Stosu 
template <typename T>
void uruchomQuickSortStos(Stos<T>& s, Parameters::Pivots rodzajPivota) {
    size_t size = s.getSize();
    if (size <= 1) return;

	size_t krok = 0; // Ile kroków od szczytu do pivota (domyślnie 0 dla right)
    if (rodzajPivota == Parameters::Pivots::random) krok = rand() % size;         // Losowy
    else if (rodzajPivota == Parameters::Pivots::middle) krok = size / 2;         // Środkowy
    else if (rodzajPivota == Parameters::Pivots::left) krok = size - 1;           // Skrajny (sam dol)

	Stos<T> temp; // Tymczasowy stos do przechowania elementów powyżej pivota
	for (size_t i = 0; i < krok; ++i) { // Przenosimy elementy powyżej pivota na tymczasowy stos
        temp.push(s.top());
        s.pop();
    }

	T pivot = s.top(); // Pobieramy pivota
    s.pop();

	while (temp.getSize() > 0) { // Przywracamy elementy powyżej pivota z powrotem na główny stos
        s.push(temp.top());
        temp.pop();
    }

    Stos<T> stos_mniejszy; // Stos dla elementów mniejszych od pivota
    Stos<T> stos_wiekszy; // Stos dla elementów większych od pivota

	// Podział na mniejszy i większy stos względem pivota
    while (s.getSize() > 0) {
        T val = s.top();
        s.pop();
        if (val <= pivot) {
            stos_mniejszy.push(val);
        }
        else {
            stos_wiekszy.push(val);
        }
    }

	uruchomQuickSortStos(stos_mniejszy, rodzajPivota); // Rekurencyjne sortowanie mniejszego stosu
	uruchomQuickSortStos(stos_wiekszy, rodzajPivota); // Rekurencyjne sortowanie większego stosu

	Stos<T> reverser; // Stos pomocniczy do odwracania kolejności elementów 

	// Pakujemy posortowane większe elementy
    while (stos_wiekszy.getSize() > 0) {
        reverser.push(stos_wiekszy.top());
        stos_wiekszy.pop();
    }
    while (reverser.getSize() > 0) {
        s.push(reverser.top());
        reverser.pop();
    }

	s.push(pivot); // Pakujemy pivota

	// Pakujemy posortowane mniejsze elementy
    while (stos_mniejszy.getSize() > 0) {
        reverser.push(stos_mniejszy.top());
        stos_mniejszy.pop();
    }
    while (reverser.getSize() > 0) {
        s.push(reverser.top());
        reverser.pop();
    }
}