#include "ModificarEstudiante.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip> 

using namespace std;

void mostrarMenuModificar();
void mostrarMenuNotas();
void modificarNombreCarrera(string& nombre, string& carrera);
void modificarNotas(string& nota1, string& nota2, string& nota3);
float calcularNotaFinal(const string& nota1, const string& nota2, const string& nota3);

void modificarEstudiante(const string& nombreArchivo) {
    string codigoBuscar;
    cout << "Ingrese el codigo del estudiante a modificar: ";
    cin >> codigoBuscar;

    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile.is_open()) {
        cout << "No se pudo crear el archivo temporal.\n";
        archivo.close();
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string codigo, nombre, carrera, nota1, nota2, nota3, notaFinal;
        getline(ss, codigo, '|');
        getline(ss, nombre, '|');
        getline(ss, carrera, '|');
        getline(ss, nota1, '|');
        getline(ss, nota2, '|');
        getline(ss, nota3, '|');
        getline(ss, notaFinal);

        if (codigo == codigoBuscar) {
            encontrado = true;
            bool salir = false;

            while (!salir) {
                system("cls");
                mostrarMenuModificar();
                int opcion;
                cin >> opcion;

                switch (opcion) {
                case 1:
                    system("cls");
                    cout << "Nuevo nombre y apellido: ";
                    cin.ignore();
                    getline(cin, nombre);
                    break;
                case 2:
                    system("cls");
                    cout << "Nueva carrera: ";
                    cin.ignore();
                    getline(cin, carrera);
                    break;
                case 3:
                    system("cls");
                    modificarNotas(nota1, nota2, nota3);
                    break;
                case 4:
                    system("cls");
                    modificarNombreCarrera(nombre, carrera);
                    system("cls");
                    modificarNotas(nota1, nota2, nota3);
                    break;
                case 5:
                    salir = true;
                    break;
                default:
                    cout << "Opcion invalida.\n";
                    break;
                }
            }

            // Recalcular nota final
            float notaFinalFloat = calcularNotaFinal(nota1, nota2, nota3);
            stringstream ssNotaFinal;
            ssNotaFinal << fixed << setprecision(2) << notaFinalFloat;
            notaFinal = ssNotaFinal.str();

            string nuevaLinea = codigo + "|" + nombre + "|" + carrera + "|" + nota1 + "|" + nota2 + "|" + nota3 + "|" + notaFinal;
            tempFile << nuevaLinea << endl;
        }
        else {
            tempFile << linea << endl;
        }
    }

    archivo.close();
    tempFile.close();

    if (!encontrado) {
        remove("temp.txt");
        cout << "Estudiante no encontrado.\n";
    }
    else {
        if (remove(nombreArchivo.c_str()) != 0) {
            perror("Error al eliminar el archivo original");
        }

        if (rename("temp.txt", nombreArchivo.c_str()) != 0) {
            perror("Error al renombrar el archivo");
        }
        else {
            cout << "Estudiante modificado exitosamente.\n";
        }
    }
}

void mostrarMenuModificar() {
    cout << "\nMODIFICAR ESTUDIANTE\n";
    cout << "---------------------\n";
    cout << "1. Modificar nombre y apellido\n";
    cout << "2. Modificar carrera\n";
    cout << "3. Modificar notas\n";
    cout << "4. Modificar todo\n";
    cout << "5. Volver al menu principal\n";
    cout << "Seleccione una opcion: ";
}

void mostrarMenuNotas() {
    cout << "\nMODIFICAR NOTAS\n";
    cout << "----------------\n";
    cout << "1. Modificar Nota 1\n";
    cout << "2. Modificar Nota 2\n";
    cout << "3. Modificar Nota 3\n";
    cout << "4. Modificar todas las notas\n";
    cout << "5. Volver al menu de modificar estudiante\n";
    cout << "Seleccione una opcion: ";
}

void modificarNotas(string& nota1, string& nota2, string& nota3) {
    int opcion;
    do {
        mostrarMenuNotas();
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Nueva Nota 1: ";
            cin >> nota1;
            break;
        case 2:
            cout << "Nueva Nota 2: ";
            cin >> nota2;
            break;
        case 3:
            cout << "Nueva Nota 3: ";
            cin >> nota3;
            break;
        case 4:
            cout << "Nueva Nota 1: ";
            cin >> nota1;
            cout << "Nueva Nota 2: ";
            cin >> nota2;
            cout << "Nueva Nota 3: ";
            cin >> nota3;
            break;
        case 5:
            return;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 5);
}

void modificarNombreCarrera(string& nombre, string& carrera) {
    cout << "Nuevo nombre y apellido: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "Nueva carrera: ";
    getline(cin, carrera);
}

float calcularNotaFinal(const string& n1, const string& n2, const string& n3) {
    try {
        float nota1 = stof(n1);
        float nota2 = stof(n2);
        float nota3 = stof(n3);
        return nota1 * 0.30f + nota2 * 0.35f + nota3 * 0.35f;
    }
    catch (...) {
        return 0.0f; // Si hay error en la conversión, retornar 0
    }
}


