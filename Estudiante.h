#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>

using namespace std;

class Estudiante {
private:
    string nombre;
    string apellido;
    string codigo;
    string carrera;

public:
    void crearEstudiante();
    bool codigoValido(const string& codigo);
    bool codigoRepetido(const string& codigo);
};

#endif

