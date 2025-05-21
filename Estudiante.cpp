#include "Estudiante.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

const size_t MAX_LONGITUD = 50;

bool Estudiante::codigoValido(const string& codigo) {
    regex formato("T[0-9]{8}");
    return regex_match(codigo, formato);
}

bool Estudiante::codigoRepetido(const string& codigo) {
    ifstream archivo("estudiantes.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para verificar códigos repetidos.\n";
        return false;
    }

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

    // Solicitar y validar código
    do {
        cout << "Ingrese el codigo del estudiante (formato T12345678): ";
        cin >> codigo;

        if (!codigoValido(codigo)) {
            cout << "Formato inválido. Debe comenzar con 'T' seguido de 8 dígitos.\n";
        }
        else if (codigoRepetido(codigo)) {
            cout << "Ese código ya está registrado. Ingrese uno diferente.\n";
        }
        else {
            break;
        }
    } while (true);

    cin.ignore();

    // Solicitar y validar nombre
    do {
        cout << "Ingrese el nombre y apellido del estudiante: ";
        getline(cin, nombre);

        if (nombre.empty()) {
            cout << "El nombre no puede estar vacío.\n";
        }
        else if (nombre.length() > MAX_LONGITUD) {
            cout << "El nombre es demasiado largo. Máximo " << MAX_LONGITUD << " caracteres.\n";
        }
        else {
            break;
        }
    } while (true);

    // Solicitar y validar carrera
    do {
        cout << "Ingrese la carrera del estudiante: ";
        getline(cin, carrera);

        if (carrera.empty()) {
            cout << "La carrera no puede estar vacía.\n";
        }
        else if (carrera.length() > MAX_LONGITUD) {
            cout << "La carrera es demasiado larga. Máximo " << MAX_LONGITUD << " caracteres.\n";
        }
        else {
            break;
        }
    } while (true);

    // Guardar estudiante en archivo
    ofstream archivo("estudiantes.txt", ios::app);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para escritura.\n";
        return;
    }

    archivo << codigo << "|" << nombre << "|" << carrera << "||||" << endl;
    archivo.close();

    if (archivo.fail()) {
        cerr << "Error al cerrar el archivo después de escribir.\n";
    }
    else {
        cout << "Estudiante creado exitosamente.\n";
    }
}


