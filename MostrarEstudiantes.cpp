#include "MostrarEstudiantes.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream> // Para std::stringstream

void mostrarEstudiantes(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo de estudiantes.\n";
        return;
    }

    std::string linea;
    int contador = 1;

    // Encabezado de la tabla
    std::cout << std::left;
    std::cout << std::setw(6) << "No."
        << std::setw(12) << "Codigo"
        << std::setw(30) << "Nombre"
        << std::setw(25) << "Carrera" << "\n";
    std::cout << std::string(73, '-') << "\n";

    while (getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string codigo, nombre, carrera;

        if (getline(ss, codigo, '|') &&
            getline(ss, nombre, '|') &&
            getline(ss, carrera)) {

            std::cout << std::setw(6) << contador
                << std::setw(12) << codigo
                << std::setw(30) << nombre
                << std::setw(25) << carrera << "\n";
            contador++;
        }
    }

    archivo.close();

    if (contador == 1) {
        std::cout << "No hay estudiantes registrados.\n";
    }
}
