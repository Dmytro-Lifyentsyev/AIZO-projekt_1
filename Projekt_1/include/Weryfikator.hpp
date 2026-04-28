#pragma once

template <typename Structure>
bool sprawdzCzyPosortowane(Structure& struktura) {
    if (struktura.getSize() <= 1) return true;

    for (size_t i = 1; i < struktura.getSize(); ++i) {
        if (struktura[i - 1] > struktura[i]) {
            return false; 
        }
    }
    return true; 
}