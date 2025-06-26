#pragma once

#include <string>
#include "Paciente.h"

class ArchivoPaciente {
private:
    std::string _nombreArchivo;

public:
    ArchivoPaciente(std::string nombreArchivo);

    bool Guardar(Paciente paciente);
    bool Guardar(Paciente paciente, int posicion);

    int Buscar(int IDPaciente);
   int BuscarPorNombre(const std::string& pacienteNombre);
    int BuscarPorDni(const std::string& dniPaciente);
    Paciente Leer(int posicion);
    void Leer(int cantidadRegistros, Paciente* vector);
    int CantidadRegistros();
    int generarNuevoId();
    bool checkDni(const std::string& dni);
};
