#include "EliminarEstudiante.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <filesystem>

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
        cout << "Codigo invalido.\n";
        return;
    }

    ifstream archivo(archivoNombre);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    vector<string> lineas;
    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        size_t pos = linea.find('|');
        if (pos != string::npos) {
            string codigoArchivo = linea.substr(0, pos);
            if (codigoArchivo != codigo) {
                lineas.push_back(linea);
            }
            else {
                encontrado = true;
            }
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "No se encontró un estudiante con ese código.\n";
        return;
    }

    ofstream archivoSalida(archivoNombre, ios::trunc);
    for (const string& l : lineas) {
        archivoSalida << l << endl;
    }

    archivoSalida.close();
    cout << "Estudiante eliminado correctamente.\n";
}
