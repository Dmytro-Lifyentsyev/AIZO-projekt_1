#pragma once

template <typename Structure>
int partition(Structure& struktura, int low, int high) {
    auto pivot = struktura[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; ++j) {
        if (struktura[j] <= pivot) {
            i++;
            auto temp = struktura[i];
            struktura[i] = struktura[j];
            struktura[j] = temp;
        }
    }
    auto tempPivot = struktura[i + 1];
    struktura[i + 1] = struktura[high];
    struktura[high] = tempPivot;

    return (i + 1);
}

template <typename Structure>
void quickSort(Structure& struktura, int low, int high) {
    if (low < high) {
        int pi = partition(struktura, low, high);
        quickSort(struktura, low, pi - 1);
        quickSort(struktura, pi + 1, high);
    }
}

template <typename Structure>
void uruchomQuickSort(Structure& struktura) {
    if (struktura.getSize() > 0) {
        quickSort(struktura, 0, (int)struktura.getSize() - 1);
    }
}