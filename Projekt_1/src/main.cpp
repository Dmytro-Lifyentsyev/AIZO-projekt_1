#include <iostream>
#include "Parameters.h"
#include "Tablica.hpp"
#include "List.hpp"
#include "Lista_dk.hpp"
#include "Eksperyment.hpp" 
#include <ctime>

using namespace std;

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(NULL)));

    Parameters::readParameters(argc - 1, argv + 1);

	// Sprawdzanie trybu działania programu
    if (Parameters::runMode == Parameters::RunModes::help) {
        Parameters::help(); // tryb pomocy
    }
    else if (Parameters::runMode == Parameters::RunModes::singleFile || Parameters::runMode == Parameters::RunModes::benchmark) {

        // Switch zarządzający strukturami danych
		switch (Parameters::structure) {
        case Parameters::Structures::array:
            cout << "\nWybrana struktura: Tablica\n";
            uruchomDlaWybranejStruktury<Tablica>();
            break;

        case Parameters::Structures::singleList:
            cout << "\nWybrana struktura: Lista Jednokierunkowa\n";
            uruchomDlaWybranejStruktury<List>();
            break;

        case Parameters::Structures::doubleList:
            cout << "\nWybrana struktura: Lista Dwukierunkowa\n";
            uruchomDlaWybranejStruktury<List_dk>();
            break;
        case Parameters::Structures::stack:
            cout << "\nWybrana struktura: Stos\n";
            uruchomDlaWybranejStruktury<Stos>();
            break;
        case Parameters::Structures::binaryTree:
            cout << "\nWybrana struktura: BST\n";
            uruchomDlaWybranejStruktury<BST>();
            break;
        default:
            cout << "Nieznana struktura\n";
            break;
        }
    }
    else {
        cout << "\nNie wybrano poprawnego trybu. Uzyj flagi -h, aby wyswietlic pomoc.\n";
    }

    return 0;
}