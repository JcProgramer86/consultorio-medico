#include "MedicoEspecialidad.h"

// Constructor por defecto
MedicoEspecialidad::MedicoEspecialidad() : _id(0), _idEspecialidad(0), _idMedico(0) {}

// Constructor parametrizado
MedicoEspecialidad::MedicoEspecialidad(int id, int idEspecialidad, int idMedico)
    : _id(id), _idEspecialidad(idEspecialidad), _idMedico(idMedico) {}

// Getters
int MedicoEspecialidad::getId() const {
    return _id;
}

int MedicoEspecialidad::getIdEspecialidad() const {
    return _idEspecialidad;
}

int MedicoEspecialidad::getIdMedico() const {
    return _idMedico;
}

// Setters
void MedicoEspecialidad::setId(int id) {
    _id = id;
}

void MedicoEspecialidad::setIdEspecialidad(int idEspecialidad) {
    _idEspecialidad = idEspecialidad;
}

void MedicoEspecialidad::setIdMedico(int idMedico) {
    _idMedico = idMedico;
}
