#include "MostrarEstudiantes.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

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
        << std::setw(25) << "Nombre"
        << std::setw(20) << "Carrera"
        << std::setw(8) << "Nota1"
        << std::setw(8) << "Nota2"
        << std::setw(8) << "Nota3"
        << std::setw(10) << "NotaFinal" << "\n";

    std::cout << std::string(97, '-') << "\n";

    while (getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string campos[7];  // codigo, nombre, carrera, nota1, nota2, nota3, notaFinal
        std::string campo;
        int i = 0;

        // Extraer campos separados por '|'
        while (getline(ss, campo, '|') && i < 7) {
            campos[i++] = campo;
        }

        // Rellenar campos faltantes con "-"
        while (i < 7) {
            campos[i++] = "-";
        }

        std::cout << std::setw(6) << contador
            << std::setw(12) << campos[0]
            << std::setw(25) << campos[1]
            << std::setw(20) << campos[2]
            << std::setw(8) << (campos[3].empty() ? "-" : campos[3])
            << std::setw(8) << (campos[4].empty() ? "-" : campos[4])
            << std::setw(8) << (campos[5].empty() ? "-" : campos[5])
            << std::setw(10) << (campos[6].empty() ? "-" : campos[6])
            << "\n";

        contador++;
    }

    archivo.close();

    if (contador == 1) {
        std::cout << "No hay estudiantes registrados.\n";
    }
}


