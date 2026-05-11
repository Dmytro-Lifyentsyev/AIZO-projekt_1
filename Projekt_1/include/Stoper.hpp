#pragma once
#include <chrono>

// Klasa Stoper do pomiaru czasu
class Stoper {
private:
    // Zmienne przechowujące moment startu i końca
    std::chrono::time_point<std::chrono::high_resolution_clock> punkt_startu;
    std::chrono::time_point<std::chrono::high_resolution_clock> punkt_konca;

public:
    // Włącza stoper
    void start() {
        punkt_startu = std::chrono::high_resolution_clock::now();
    }

    // Wyłącza stoper
    void stop() {
        punkt_konca = std::chrono::high_resolution_clock::now();
    }

    // Zwraca czas w mikrosekundach
    double getCzasMikrosekundy() {
        std::chrono::duration<double, std::micro> czas_trwania = punkt_konca - punkt_startu;
        return czas_trwania.count();
    }

	// Zwraca czas w milisekundach
    double getCzasMilisekundy() {
        std::chrono::duration<double, std::milli> czas_trwania = punkt_konca - punkt_startu;
        return czas_trwania.count();
    }

    // Zwraca czas w sekundach
    double getCzasSekundy() {
        std::chrono::duration<double> czas_trwania = punkt_konca - punkt_startu;
        return czas_trwania.count();
    }
};