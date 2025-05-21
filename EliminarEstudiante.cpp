#include "EliminarEstudiante.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <cstdio>

using namespace std;

bool codigoValido(const string& codigo) {
    regex formato("T[0-9]{8}");
    return regex_match(codigo, formato);
}

void eliminarEstudiante(const string& archivoNombre) {
    string codigo;
    cout << "Ingrese el codigo del estudiante a eliminar: ";
    cin >> codigo;

    if (!codigoValido(codigo)) {
        cout << "Código inválido.\n";
        return;
    }

    ifstream archivoEntrada(archivoNombre);
    if (!archivoEntrada.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    ofstream archivoTemp("temp.txt");
    if (!archivoTemp.is_open()) {
        cout << "No se pudo crear el archivo temporal.\n";
        archivoEntrada.close();
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivoEntrada, linea)) {
        size_t pos = linea.find('|');
        if (pos != string::npos) {
            string codigoArchivo = linea.substr(0, pos);
            if (codigoArchivo != codigo) {
                archivoTemp << linea << endl;
            }
            else {
                encontrado = true;
            }
        }
        else {
            archivoTemp << linea << endl;
        }
    }

    archivoEntrada.close();
    archivoTemp.close();

    if (!encontrado) {
        remove("temp.txt");
        cout << "No se encontró un estudiante con ese código.\n";
        return;
    }

    if (remove(archivoNombre.c_str()) != 0) {
        cout << "Error al eliminar el archivo original.\n";
        return;
    }

    if (rename("temp.txt", archivoNombre.c_str()) != 0) {
        cout << "Error al renombrar el archivo temporal.\n";
        return;
    }

    cout << "Estudiante eliminado correctamente.\n";
}

