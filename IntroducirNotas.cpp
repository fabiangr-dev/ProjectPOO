#include "IntroducirNotas.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

bool esNotaValida(double nota) {
    return nota >= 0.0 && nota <= 5.0;
}

double obtenerNota(int numero) {
    double nota;
    while (true) {
        cout << "Ingrese nota " << numero << " (0.0 - 5.0): ";
        if (cin >> nota && esNotaValida(nota)) {
            break;
        }
        else {
            cout << "Nota invalida. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return nota;
}

void introducirNotas(const string& nombreArchivo) {
    string codigoBuscado;
    cout << "Ingrese el codigo del estudiante: ";
    cin >> codigoBuscado;

    ifstream archivoOriginal(nombreArchivo);
    ofstream archivoTemporal("temp.txt");

    if (!archivoOriginal.is_open() || !archivoTemporal.is_open()) {
        cerr << "Error al abrir los archivos.\n";
        return;
    }

    string linea;
    bool encontrado = false;
    bool notasYaIngresadas = false;

    while (getline(archivoOriginal, linea)) {
        stringstream ss(linea);
        string codigo, nombre, carrera;
        string nota1, nota2, nota3, notaFinal;

        getline(ss, codigo, '|');
        getline(ss, nombre, '|');
        getline(ss, carrera, '|');
        getline(ss, nota1, '|');
        getline(ss, nota2, '|');
        getline(ss, nota3, '|');
        getline(ss, notaFinal, '|');

        if (codigo == codigoBuscado) {
            encontrado = true;

            // Verificar si ya hay notas ingresadas
            if (!nota1.empty() || !nota2.empty() || !nota3.empty()) {
                notasYaIngresadas = true;
                // Reescribir la línea original sin modificar
                archivoTemporal << linea << "\n";
                continue;
            }

            double n1 = obtenerNota(1);
            double n2 = obtenerNota(2);
            double n3 = obtenerNota(3);
            double final = (n1 * 0.30) + (n2 * 0.35) + (n3 * 0.35);

            archivoTemporal << codigo << "|" << nombre << "|" << carrera << "|"
                << fixed << setprecision(2)
                << n1 << "|" << n2 << "|" << n3 << "|" << final << "\n";
        }
        else {
            archivoTemporal << linea << "\n";
        }
    }

    archivoOriginal.close();
    archivoTemporal.close();

    if (!encontrado) {
        remove("temp.txt");
        cout << "\nEstudiante no encontrado.\n";
    }
    else if (notasYaIngresadas) {
        remove("temp.txt");
        cout << "\nEl estudiante ya tiene notas registradas. No se puede sobrescribir.\n";
    }
    else {
        remove(nombreArchivo.c_str());
        rename("temp.txt", nombreArchivo.c_str());
        cout << "\nNotas registradas exitosamente.\n";
    }
}

