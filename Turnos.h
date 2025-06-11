#ifndef TURNOS_H
#define TURNOS_H

#include "Fecha.h"
#include "Hora.h"
#include <string>
#include <cstring>

class Turno {
private:
    int _id;
    int _idPaciente;
    int _idMedicoEspecialidad;
    Fecha _fechaAtencion;
    Hora _horaAtencion;
    float _importeConsulta;
    bool _cancelado;
    bool _sobreturno;
    Hora _duracionTurno;
    char _observaciones[100];

public:
    Turno();
    Turno(int, int, int, Fecha, Hora, float, bool, bool, Hora, const std::string&);

    int getId() const;
    int getIdPaciente() const;
    int getIdMedicoEspecialidad() const;
    Fecha getFechaAtencion() const;
    Hora getHoraAtencion() const;
    float getImporteConsulta() const;
    bool getCancelado() const;
    bool getSobreturno() const;
    Hora getDuracionTurno() const;
    const char* getObservaciones() const;

    void setId(int);
    void setIdPaciente(int);
    void setIdMedicoEspecialidad(int);
    void setFechaAtencion(Fecha);
    void setHoraAtencion(Hora);
    void setImporteConsulta(float);
    void setCancelado(bool);
    void setSobreturno(bool);
    void setDuracionTurno(Hora);
    void setObservaciones(const std::string&);
};

#endif // TURNOS_H
