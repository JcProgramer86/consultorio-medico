#include "ManagerPaciente.h"
#include <iostream>

using namespace std;

ManagerPaciente::ManagerPaciente(const string& nombreArchivo) {
    int len = nombreArchivo.size();
    if (len >= 50) len = 49;
    for (int i = 0; i < len; i++) {
        _nombreArchivo[i] = nombreArchivo[i];
    }
    _nombreArchivo[len] = '\0';

    cantidad = 0;
}

bool ManagerPaciente::crearPaciente(const Paciente& paciente) {
    if (cantidad >= 100) {
        cout << "No hay espacio para más pacientes\n";
        return false;
    }
    for (int i = 0; i < cantidad; i++) {
        if (pacientes[i].get_id() == paciente.get_id()) {
            cout << "Paciente con ese ID ya existe\n";
            return false;
        }
    }
    pacientes[cantidad] = paciente;
    cantidad++;
    return true;
}

bool ManagerPaciente::buscarPacientePorID(int id, Paciente& pacienteEncontrado) {
    for (int i = 0; i < cantidad; i++) {
        if (pacientes[i].get_id() == id) {
            pacienteEncontrado = pacientes[i];
            return true;
        }
    }
    return false;
}

bool ManagerPaciente::buscarPacientePorDNI(const string& dni, Paciente& pacienteEncontrado) {
    for (int i = 0; i < cantidad; i++) {
        if (pacientes[i].get_dni() == dni) {
            pacienteEncontrado = pacientes[i];
            return true;
        }
    }
    return false;
}

bool ManagerPaciente::modificarPaciente(const Paciente& pacienteModificado) {
    for (int i = 0; i < cantidad; i++) {
        if (pacientes[i].get_id() == pacienteModificado.get_id()) {
            pacientes[i] = pacienteModificado;
            return true;
        }
    }
    cout << "Paciente no encontrado para modificar\n";
    return false;
}

bool ManagerPaciente::eliminarPaciente(int id) {
    for (int i = 0; i < cantidad; i++) {
        if (pacientes[i].get_id() == id) {
            pacientes[i] = pacientes[cantidad - 1];
            cantidad--;
            return true;
        }
    }
    cout << "Paciente no encontrado para eliminar\n";
    return false;
}

void ManagerPaciente::buscarPacientesPorNombre(const string& nombre) const {
    bool encontrado = false;
    for (int i = 0; i < cantidad; i++) {
        if (pacientes[i].get_nombre().find(nombre) != string::npos && pacientes[i].get_enabled()) {
            cout << "ID: " << pacientes[i].get_id()
                 << " | Nombre: " << pacientes[i].get_nombre()
                 << " | DNI: " << pacientes[i].get_dni()
                 << " | Prestador: " << pacientes[i].get_idPrestador()
                 << endl;
            cout << "--------------\n";
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "No se encontraron pacientes con ese nombre\n";
    }
}

void ManagerPaciente::listarPacientes() const {
    for (int i = 0; i < cantidad; i++) {
        if (pacientes[i].get_enabled()) {
            cout << "ID: " << pacientes[i].get_id()
                 << " | DNI: " << pacientes[i].get_dni()
                 << " | Prestador: " << pacientes[i].get_idPrestador()
                 << endl;
        }
    }
}

bool ManagerPaciente::asignarPrestadorAPaciente(int idPaciente, int idPrestador) {
    for (int i = 0; i < cantidad; i++) {
        if (pacientes[i].get_id() == idPaciente) {
            pacientes[i].set_idPrestador(idPrestador);  // CORREGIDO
            return true;
        }
    }
    cout << "Paciente no encontrado para asignar prestador\n";
    return false;
}

bool ManagerPaciente::cambiarPrestadorDePaciente(int idPaciente, int nuevoIdPrestador) {
    return asignarPrestadorAPaciente(idPaciente, nuevoIdPrestador);
}

bool ManagerPaciente::activarPaciente(int idPaciente) {
    for (int i = 0; i < cantidad; i++) {
        if (pacientes[i].get_id() == idPaciente) {
            pacientes[i].set_enabled(true);
            return true;
        }
    }
    cout << "Paciente no encontrado para activar\n";
    return false;
}

bool ManagerPaciente::desactivarPaciente(int idPaciente) {
    for (int i = 0; i < cantidad; i++) {
        if (pacientes[i].get_id() == idPaciente) {
            pacientes[i].set_enabled(false);
            return true;
        }
    }
    cout << "Paciente no encontrado para desactivar\n";
    return false;
}
