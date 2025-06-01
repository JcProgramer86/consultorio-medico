#include "Turnos.h"
#include <cstring>  // Para memcpy si hiciera falta
#include <string>    // Para std::string


Turno::Turno()
{
    _idTurno = 0;
    for (int i = 0; i < 10; i++)
    {
        _idPaciente[i] = 0;
        _idMedico[i] = 0;
    }
    // Si Fecha y Hora tienen constructores por defecto, se inicializan solos
    _importeConsulta = 0.0f;
    _cancelado = false;
    _sobreturno = false;
    _duracionTurno = Hora();  // Asume constructor por defecto en Hora
    _observaciones[0] = '\0'; // String vacío
}

// Constructor parametrizado utilizando setters
Turno::Turno(int idTurno, int idPaciente[], int idMedico[], Fecha fechaTurno, Hora horaTurno, float importeConsulta,
      bool cancelado, bool sobreturno, Hora duracionTurno, const std::string& observaciones)
{
    setIdTurno(idTurno);
    setIdPaciente(idPaciente);
    setIdMedico(idMedico);
    setFechaTurno(fechaTurno);
    setHoraTurno(horaTurno);
    setImporteConsulta(importeConsulta);
    setCancelado(cancelado);
    setSobreturno(sobreturno);
    setDuracionTurno(duracionTurno);
    setObservaciones(observaciones.c_str());
}

// Getters
int Turno::getIdTurno() const
{
    return _idTurno;
}

const int* Turno::getIdPaciente() const
{
    return _idPaciente;
}

const int* Turno::getIdMedico() const
{
    return _idMedico;
}

Fecha Turno::getFechaTurno() const
{
    return _fechaTurno;
}

Hora Turno::getHoraTurno() const
{
    return _horaTurno;
}

float Turno::getImporteConsulta() const
{
    return _importeConsulta;
}
bool Turno::getCancelado() const
{
    return _cancelado;
}

bool Turno::getSobreturno() const
{
    return _sobreturno
           ;
}

Hora Turno::getDuracionTurno() const
{
    return _duracionTurno;
}

const char* Turno::getObservaciones() const
{
    return _observaciones;
}

// Setters
void Turno::setIdTurno(int idTurno)
{
    _idTurno = idTurno;
}

void Turno::setIdPaciente(const int idPaciente[])
{
    for (int i = 0; i < 10; i++)
    {
        _idPaciente[i] = idPaciente[i];
    }
}

void Turno::setIdMedico(const int idMedico[])
{
    for (int i = 0; i < 10; i++)
    {
        _idMedico[i] = idMedico[i];
    }
}

void Turno::setFechaTurno(Fecha fechaTurno)
{
    _fechaTurno = fechaTurno;
}

void Turno::setHoraTurno(Hora horaTurno)
{
    _horaTurno = horaTurno;
}

void Turno::setImporteConsulta(float importeConsulta)
{
    _importeConsulta = importeConsulta;
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
    strncpy(_observaciones, observaciones, sizeof(_observaciones));
    _observaciones[sizeof(_observaciones) - 1] = '\0'; // Seguridad
}

// Método de ejemplo: validación de turno (modificá según tu lógica real)
bool Turno::validarTurno()
{
    // Por ahora devolvemos true, luego podés implementar reglas reales
    return true;
}
