#include "Estudiante.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

bool Estudiante::codigoValido(const string& codigo) {
    regex formato("T[0-9]{8}"); // T seguido de 8 digitos
    return regex_match(codigo, formato);
}

bool Estudiante::codigoRepetido(const string& codigo) {
    ifstream archivo("estudiantes.txt");
    string linea;

    while (getline(archivo, linea)) {
        size_t pos = linea.find('|');
        if (pos != string::npos) {
            string codigoExistente = linea.substr(0, pos);
            if (codigoExistente == codigo) {
                return true;
            }
        }
    }

    return false;
}

void Estudiante::crearEstudiante() {
    string codigo, nombre, carrera;

    cout << "Ingrese el codigo del estudiante: ";
    cin >> codigo;

    while (!codigoValido(codigo) || codigoRepetido(codigo)) {
        cout << "Codigo invalido o repetido. Intente de nuevo: ";
        cin >> codigo;
    }

    cin.ignore();
    cout << "Ingrese el nombre y apellido del estudiante: ";
    getline(cin, nombre);

    cout << "Ingrese la carrera del estudiante: ";
    getline(cin, carrera);

    ofstream archivo("estudiantes.txt", ios::app);
    if (archivo.is_open()) {
        archivo << codigo << "|" << nombre << "|" << carrera << endl;
        archivo.close();
        cout << "Estudiante creado exitosamente.\n";
    }
    else {
        cout << "Error al abrir el archivo para escritura.\n";
    }
}
