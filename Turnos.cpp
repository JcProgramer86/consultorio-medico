#include "Turnos.h"
#include <cstring>  // Para memcpy si hiciera falta

// Constructor parametrizado utilizando setters
Turno::Turno(int idTurno, int idPaciente[], int idMedico[], Fecha fechaTurno, Hora horaTurno, float importeConsulta) {
    setIdTurno(idTurno);
    setIdPaciente(idPaciente);
    setIdMedico(idMedico);
    setFechaTurno(fechaTurno);
    setHoraTurno(horaTurno);
    setImporteConsulta(importeConsulta);
}

// Getters
int Turno::getIdTurno() const {
    return _idTurno;
}

const int* Turno::getIdPaciente() const {
    return _idPaciente;
}

const int* Turno::getIdMedico() const {
    return _idMedico;
}

Fecha Turno::getFechaTurno() const {
    return _fechaTurno;
}

Hora Turno::getHoraTurno() const {
    return _horaTurno;
}

float Turno::getImporteConsulta() const {
    return _importeConsulta;
}

// Setters
void Turno::setIdTurno(int idTurno) {
    _idTurno = idTurno;
}

void Turno::setIdPaciente(const int idPaciente[]) {
    for (int i = 0; i < 10; i++) {
        _idPaciente[i] = idPaciente[i];
    }
}

void Turno::setIdMedico(const int idMedico[]) {
    for (int i = 0; i < 10; i++) {
        _idMedico[i] = idMedico[i];
    }
}

void Turno::setFechaTurno(Fecha fechaTurno) {
    _fechaTurno = fechaTurno;
}

void Turno::setHoraTurno(Hora horaTurno) {
    _horaTurno = horaTurno;
}

void Turno::setImporteConsulta(float importeConsulta) {
    _importeConsulta = importeConsulta;
}

// Método de ejemplo: validación de turno (modificá según tu lógica real)
bool Turno::validarTurno() {
    // Por ahora devolvemos true, luego podés implementar reglas reales
    return true;
}
