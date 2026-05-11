#pragma once
#include "Parameters.h"

// Algorytm Shell sort z 2 wersjami odstepamu: ciag Shella i ciag Knutha
template <typename Structure>
void shellSort(Structure& struktura, Parameters::ShellParameters rodzajOstepu) {
    int n = (int)struktura.getSize();
    if (n <= 1) return;

	// Odstepy dla opcji 1: ciag Shella
    if (rodzajOstepu == Parameters::ShellParameters::option1) {
        for (int odstep = n / 2; odstep > 0; odstep /= 2) {
            // Standardowe sortowanie przez wstawianie dla danego odstepu
            for (int i = odstep; i < n; i += 1) {
                auto temp = struktura[i];
                int j;
                for (j = i; j >= odstep && struktura[j - odstep] > temp; j -= odstep) {
                    struktura[j] = struktura[j - odstep];
                }
                struktura[j] = temp;
            }
        }
    }
	// Odstepy dla opcji 2: ciag Knutha
    else if (rodzajOstepu == Parameters::ShellParameters::option2) {
		int odstep = 1; // Inicjalizacja odstepu zgodnie z ciągiem Knutha 

		// Obliczamy największy odstep z ciągu Knutha 
        while (odstep < n / 3) {
            odstep = 3 * odstep + 1;
        }

		// Sortowanie przez wstawianie dla każdego odstepu z ciągu Knutha
        for (; odstep > 0; odstep /= 3) {
            for (int i = odstep; i < n; i += 1) {
                auto temp = struktura[i];
                int j;
                for (j = i; j >= odstep && struktura[j - odstep] > temp; j -= odstep) {
                    struktura[j] = struktura[j - odstep];
                }
                struktura[j] = temp;
            }
        }
    }
}

// Funkcja uruchamiająca sortowanie Shella
template <typename Structure>
void uruchomShellSort(Structure& struktura, Parameters::ShellParameters rodzajOstepu) {
    if (struktura.getSize() > 0) {
        shellSort(struktura, rodzajOstepu);
    }
}