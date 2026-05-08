#pragma once
#include <string>
#include <type_traits> 

using namespace std;

template <typename DataType, typename Structure>

// Funkcja sortujaca wewnetrznie kubelki (insertion sort)
void sortowanieWewnetrzne(Structure& bucket) {
    int n = static_cast<int>(bucket.getSize());
    if (n <= 1) return;

    for (int i = 1; i < n; ++i) {
        DataType temp = bucket[i];
        int j = i - 1;

        while (j >= 0 && bucket[j] > temp) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = temp;
    }
}

template <typename DataType, typename Structure>
void bucketSort(Structure& struktura) {
	size_t n = struktura.getSize(); // Pobieramy rozmiar struktury
	if (n <= 1) return; // Jeśli struktura jest pusta lub zawiera jeden element, jest już posortowana

	// sprawdzamy czy typ danych to string, jesli tak to sortujemy na podstawie pierwszego znaku, jesli nie to sortujemy numerycznie
    if constexpr (is_same_v<DataType, string>) {

		// Tworzymy dynamiczną tablice 256 kubelkow - kazdy kubelek to struktura
        Structure* buckets = new Structure[256];

		// Rozdzielamy elementy do kubelków na podstawie pierwszego znaku
        for (size_t i = 0; i < n; ++i) {
            string val = struktura[i];
            unsigned char indeks = val.empty() ? 0 : val[0];
            buckets[indeks].push_back(val);
        }

		// Zsypujemy z powrotem do głównej struktury po posortowaniu każdego kubelka
        size_t idx = 0;
        for (int i = 0; i < 256; ++i) {
			sortowanieWewnetrzne<DataType, Structure>(buckets[i]); // sortujemy każdy kubełek
            for (size_t j = 0; j < buckets[i].getSize(); ++j) {
                struktura[idx++] = buckets[i][j];
            }
        }

		delete[] buckets; // Usunięcie kubelków z pamięci
    }
	// Dla typów numerycznych
    else {
		DataType min_val = struktura[0];
        DataType max_val = struktura[0];

        for (size_t i = 1; i < n; ++i) {
			if (struktura[i] < min_val) min_val = struktura[i]; // Znajdujemy minimum
			if (struktura[i] > max_val) max_val = struktura[i]; // Znajdujemy maksimum
        }

        if (min_val == max_val) return;

		size_t bucketCount = n; // Ustawiamy liczbę kubelkow rowną liczbie elementow

		// Tworzymy dynamiczną tablice kubelkow - kazdy kubelek to struktura 
        Structure* buckets = new Structure[bucketCount];

        for (size_t i = 0; i < n; ++i) {
			DataType val = struktura[i]; // Pobieramy wartość elementu

			// Obliczamy stosunek pozycji elementu w zakresie [min_val, max_val]
            double stosunek = static_cast<double>(val - min_val) / static_cast<double>(max_val - min_val);
			size_t b_idx = static_cast<size_t>(stosunek * (bucketCount - 1)); // Obliczamy indeks kubelka, do którego nalezy element

			buckets[b_idx].push_back(val); // Dodajemy element do odpowiedniego kubelka
        }

        // Zsypujemy z powrotem do głównej struktury po posortowaniu każdego kubelka
		size_t idx = 0; 
        for (size_t i = 0; i < bucketCount; ++i) {
            sortowanieWewnetrzne<DataType, Structure>(buckets[i]); // Sortujemy każdy kubełek
            for (size_t j = 0; j < buckets[i].getSize(); ++j) { 
                struktura[idx++] = buckets[i][j]; 
            }
        }

		delete[] buckets; // Usunięcie kubelków z pamięci
    }
}

// Funkcja wywołująca
template <typename DataType, typename Structure>
void uruchomBucketSort(Structure& struktura) {
    if (struktura.getSize() > 0) {
        bucketSort<DataType, Structure>(struktura);
    }
}