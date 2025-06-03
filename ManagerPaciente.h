#pragma once
#include "Paciente.h"
#include <string>

class ManagerPaciente
{
private:
    char _nombreArchivo[50];
    Paciente pacientes[100];
    int cantidad;

public:
    ManagerPaciente(const std::string& nombreArchivo);

    // CRUD básico
    bool crearPaciente(const Paciente& paciente);
    bool buscarPacientePorID(int id, Paciente& pacienteEncontrado);
    bool buscarPacientePorDNI(const std::string& dni, Paciente& pacienteEncontrado);
    bool modificarPaciente(const Paciente& pacienteModificado);
    bool eliminarPaciente(int id);

    // Consultas y listados
    void listarPacientes() const;
    void buscarPacientesPorNombre(const std::string& nombre) const;
    void listarPacientesPorPrestador(int idPrestador) const;

    // Relación con prestador
    bool asignarPrestadorAPaciente(int idPaciente, int idPrestador);
    bool cambiarPrestadorDePaciente(int idPaciente, int nuevoIdPrestador);

    // Activar / Desactivar pacientes
    bool activarPaciente(int idPaciente);
    bool desactivarPaciente(int idPaciente);
};
