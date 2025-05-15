#include <iostream>
#include <limits>
#include <cstdlib> // Para system()
using namespace std;

class Menu {
public:
    void mostrarMenu() {
        int opcion = 0;
        while (opcion != 7) {
            limpiarPantalla();
            imprimirMenu();

            if (!(cin >> opcion) || opcion < 1 || opcion > 7) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                opcion = 0;
                continue; // Vuelve al inicio del ciclo mostrando el menú limpio
            }

            limpiarPantalla(); // Limpia antes de mostrar la opción seleccionada

            switch (opcion) {
            case 1:
                crearEstudiante();
                break;
            case 2:
                mostrarEstudiantes();
                break;
            case 3:
                buscarEstudiante();
                break;
            case 4:
                borrarEstudiante();
                break;
            case 5:
                modificarEstudiante();
                break;
            case 6:
                introducirNotas();
                break;
            case 7:
                cout << "\nSaliendo del programa..." << endl;
                break;
            }

            if (opcion != 7) {
                esperarParaContinuar();
            }
        }
    }

private:
    void limpiarPantalla() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void imprimirMenu() {
        cout << "M E N U   P R I N C I P A L\n";
        cout << "---------------------------\n";
        cout << "1. Crear Estudiante\n";
        cout << "2. Mostrar Estudiantes\n";
        cout << "3. Buscar Estudiante\n";
        cout << "4. Borrar Estudiante\n";
        cout << "5. Modificar Estudiante\n";
        cout << "6. Introducir Notas\n";
        cout << "7. Salir\n";
        cout << "Ingrese la opción (1-7): ";
    }

    void esperarParaContinuar() {
        cout << "\nPresione ENTER para volver al menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void crearEstudiante() {
        cout << "[Funcion en progreso: Crear Estudiante]\n";
    }

    void mostrarEstudiantes() {
        cout << "[Funcion en progreso: Mostrar Estudiantes]\n";
    }

    void buscarEstudiante() {
        cout << "[Funcion en progreso: Buscar Estudiante]\n";
    }

    void borrarEstudiante() {
        cout << "[Funcion en progreso: Borrar Estudiante]\n";
    }

    void modificarEstudiante() {
        cout << "[Funcion en progreso: Modificar Estudiante]\n";
    }

    void introducirNotas() {
        cout << "[Funcion en progreso: Introducir Notas]\n";
    }
};

int main() {
    Menu menuPrincipal;
    menuPrincipal.mostrarMenu();
    return 0;
}
