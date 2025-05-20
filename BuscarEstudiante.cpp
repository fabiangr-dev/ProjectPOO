#include "BuscarEstudiante.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void buscarEstudiantePorCodigo(const string& nombreArchivo) {
    string codigoBuscar;

    do {
        cout << "Ingrese el codigo del estudiante a buscar: ";
        cin >> codigoBuscar;

        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
            return;
        }

        string linea;
        bool encontrado = false;

        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string codigo, nombre, carrera;

            if (getline(ss, codigo, '|') &&
                getline(ss, nombre, '|') &&
                getline(ss, carrera)) {

                if (codigo == codigoBuscar) {
                    cout << "\n✅ Estudiante encontrado:\n";
                    cout << "Codigo  : " << codigo << endl;
                    cout << "Nombre  : " << nombre << endl;
                    cout << "Carrera : " << carrera << endl;
                    encontrado = true;
                    break;
                }
            }
        }

        archivo.close();

        if (!encontrado) {
            cout << "\n❌ No se encontro un estudiante con el codigo ingresado.\n";
            cout << "¿Desea:\n1. Ingresar otro codigo\n2. Volver al menu principal\n";
            cout << "Seleccione una opcion (1 o 2): ";
            int opcion;
            cin >> opcion;

            if (opcion == 2) {
                return;  // salir de la función
            }

        }
        else {
            return;  // estudiante encontrado, salir
        }

    } while (true);
}
