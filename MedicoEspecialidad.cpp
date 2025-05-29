#include "MedicoEspecialidad.h"

// — Constructor por defecto con lista de inicialización
MedicoEspecialidad::MedicoEspecialidad(){
    _id = 0;
    _idEspecialidad = 0;
    _idMedico = 0;
}

// — Constructor parametrizado
MedicoEspecialidad::MedicoEspecialidad(int id, int idEsp, int idMed){
     _id = id;
     _idEspecialidad = idEsp;
     _idMedico = idMed;
}

// — Getters
int MedicoEspecialidad::getId() const {
    return _id;
}

int MedicoEspecialidad::getIdEspecialidad() const {
    return _idEspecialidad;
}

int MedicoEspecialidad::getIdMedico() const {
    return _idMedico;
}

// — Setters
void MedicoEspecialidad::setId(int id) {
    _id = id;
}

void MedicoEspecialidad::setIdEspecialidad(int idEsp) {
    _idEspecialidad = idEsp;
}

void MedicoEspecialidad::setIdMedico(int idMed) {
    _idMedico = idMed;
}
