#include "Turnos.h"
#include <cstring>
#include <string>

Turno::Turno() {
    _id = 0;
    _idPaciente = 0;
    _idMedicoEspecialidad = 0;
    _importeConsulta = 0.0f;
    _cancelado = false;
    _sobreturno = false;
    _fechaAtencion = Fecha();
    _horaAtencion = Hora();
    _duracionTurno = Hora();
    _observaciones[0] = '\0';
}

Turno::Turno(int id, int idPaciente, int idMedicoEspecialidad, Fecha fechaAtencion, Hora horaAtencion, float importeConsulta,
             bool cancelado, bool sobreturno, Hora duracionTurno, const std::string& observaciones) {
    setId(id);
    setIdPaciente(idPaciente);
    setIdMedicoEspecialidad(idMedicoEspecialidad);
    setFechaAtencion(fechaAtencion);
    setHoraAtencion(horaAtencion);
    setImporteConsulta(importeConsulta);
    setCancelado(cancelado);
    setSobreturno(sobreturno);
    setDuracionTurno(duracionTurno);
    setObservaciones(observaciones.c_str());
}

// Getters
int Turno::getId() const { return _id; }
int Turno::getIdPaciente() const { return _idPaciente; }
int Turno::getIdMedicoEspecialidad() const { return _idMedicoEspecialidad; }
Fecha Turno::getFechaAtencion() const { return _fechaAtencion; }
Hora Turno::getHoraAtencion() const { return _horaAtencion; }
float Turno::getImporteConsulta() const { return _importeConsulta; }
bool Turno::getCancelado() const { return _cancelado; }
bool Turno::getSobreturno() const { return _sobreturno; }
Hora Turno::getDuracionTurno() const { return _duracionTurno; }
const char* Turno::getObservaciones() const { return _observaciones; }

// Setters
void Turno::setId(int id) { _id = id; }
void Turno::setIdPaciente(int idPaciente) { _idPaciente = idPaciente; }
void Turno::setIdMedicoEspecialidad(int idMedico) { _idMedicoEspecialidad = idMedico; }
void Turno::setFechaAtencion(Fecha fecha) { _fechaAtencion = fecha; }
void Turno::setHoraAtencion(Hora hora) { _horaAtencion = hora; }
void Turno::setImporteConsulta(float importe) { _importeConsulta = importe; }
void Turno::setCancelado(bool cancelado) { _cancelado = cancelado; }
void Turno::setSobreturno(bool sobreturno) { _sobreturno = sobreturno; }
void Turno::setDuracionTurno(Hora duracion) { _duracionTurno = duracion; }
void Turno::setObservaciones(const std::string& obs) {
    strncpy(_observaciones, obs.c_str(), sizeof(_observaciones) - 1);
    _observaciones[sizeof(_observaciones) - 1] = '\0'; // Siempre terminada
}


