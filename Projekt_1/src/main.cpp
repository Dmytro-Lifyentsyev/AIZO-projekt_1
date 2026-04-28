#include <iostream>
#include "Parameters.h"
#include "Tablica.hpp"
#include "List.hpp"
#include "Lista_dk.hpp"
#include "Eksperyment.hpp" 

using namespace std;

int main(int argc, char** argv) {

    Parameters::readParameters(argc - 1, argv + 1);

    if (Parameters::runMode == Parameters::RunModes::help) {
        Parameters::help();
    }
    else if (Parameters::runMode == Parameters::RunModes::singleFile) {

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