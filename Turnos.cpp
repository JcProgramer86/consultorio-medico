#include "Turnos.h"
#include <cstring>

using namespace std;

Turno::Turno() {
    _id = 0;
    for (int i = 0; i < 10; i++) {
        _idPaciente[i] = -1;
        _idMedicoEspecialidad[i] = -1;
    }
    _importeConsulta = 0.0;
    _cancelado = false;
    _sobreturno = false;
    _duracionTurno.setHoraAtencion(0);
    _duracionTurno.setMinutoAtencion(15);
    strcpy(_observaciones, "");
}

Turno::Turno(int id, const int idPaciente[], const int idMedicoEspecialidad[],
             Fecha fechaAtencion, Hora horaAtencion, float importeConsulta,
             bool cancelado, bool sobreturno, const char observaciones[]) {
    _id = id;
    for (int i = 0; i < 10; i++) {
        _idPaciente[i] = idPaciente[i];
        _idMedicoEspecialidad[i] = idMedicoEspecialidad[i];
    }
    _fechaAtencion = fechaAtencion;
    _horaAtencion = horaAtencion;
    _importeConsulta = importeConsulta;
    _cancelado = cancelado;
    _sobreturno = sobreturno;
    _duracionTurno.setHoraAtencion(0);
    _duracionTurno.setMinutoAtencion(15);
    strncpy(_observaciones, observaciones, sizeof(_observaciones) - 1);
    _observaciones[sizeof(_observaciones) - 1] = '\0';
}

// Getters
int Turno::getIdTurno() const {
    return _id;
}

const int* Turno::getIdPaciente() const {
    return _idPaciente;
}

const int* Turno::getIdMedicoEspecialidad() const {
    return _idMedicoEspecialidad;
}

Fecha Turno::getFechaAtencion() const {
    return _fechaAtencion;
}

Hora Turno::getHoraAtencion() const {
    return _horaAtencion;
}

float Turno::getImporteConsulta() const {
    return _importeConsulta;
}

bool Turno::getCancelado() const {
    return _cancelado;
}

bool Turno::getSobreturno() const {
    return _sobreturno;
}

Hora Turno::getDuracionTurno() const {
    return _duracionTurno;
}

const char* Turno::getObservaciones() const {
    return _observaciones;
}

// Setters
void Turno::setId(int id) {
    _id = id;
}

void Turno::setIdPaciente(const int idPaciente[]) {
    for (int i = 0; i < 10; i++) {
        _idPaciente[i] = idPaciente[i];
    }
}

void Turno::setIdMedicoEspecialidad(const int idMedicoEspecialidad[]) {
    for (int i = 0; i < 10; i++) {
        _idMedicoEspecialidad[i] = idMedicoEspecialidad[i];
    }
}

void Turno::setFechaAtencion(Fecha fecha) {
    _fechaAtencion = fecha;
}

void Turno::setHoraAtencion(Hora hora) {
    _horaAtencion = hora;
}

void Turno::setImporteConsulta(float importe) {
    _importeConsulta = importe;
}

void Turno::setCancelado(bool cancelado) {
    _cancelado = cancelado;
}

void Turno::setSobreturno(bool sobreturno) {
    _sobreturno = sobreturno;
}

void Turno::setDuracionTurno(Hora duracion) {
    _duracionTurno = duracion;
}

void Turno::setObservaciones(const char* observaciones) {
    strncpy(_observaciones, observaciones, sizeof(_observaciones) - 1);
    _observaciones[sizeof(_observaciones) - 1] = '\0';
}
