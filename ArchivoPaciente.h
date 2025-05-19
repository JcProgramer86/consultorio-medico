#pragma once
#include <string>
#include "Paciente.h"

class ArchivoPaciente{
    private:
        std::string _nombreArchivo;

    public:
        ArchivoPaciente(std::string nombreArchivo);
        bool Guardar(Paciente paciente);
        bool Guardar(Paciente paciente, int posicion);
        int Buscar(int IDPaciente);
        BuscarPorNombre(std::string& pacienteNombre);
        Paciente Leer(int posicion);
        int CantidadRegistros();
        void Leer(int cantidadRegistros, Paciente *vector);

};

