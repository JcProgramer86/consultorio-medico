#pragma once

#include "Fecha.h"
#include "Hora.h"

class Turno {
private:
    int _id;                             // ID del turno
    int _idPaciente[10];                // Pacientes involucrados (si hay varios)
    int _idMedicoEspecialidad[10];      // ID médico+especialidad
    Fecha _fechaAtencion;               // Fecha del turno
    Hora _horaAtencion;                 // Hora del turno
    float _importeConsulta;             // Importe de la consulta
    bool _cancelado;                    // Estado del turno
    bool _sobreturno;                   // Si es sobreturno
    Hora _duracionTurno;               // Duración del turno (por defecto 15 min)
    char _observaciones[200];           // Texto libre para notas médicas

public:
    Turno();

    Turno(int id, const int idPaciente[], const int idMedicoEspecialidad[],
          Fecha fechaAtencion, Hora horaAtencion, float importeConsulta,
          bool cancelado, bool sobreturno, const char observaciones[]);

    // Getters
    int getIdTurno() const;
    const int* getIdPaciente() const;
    const int* getIdMedicoEspecialidad() const;
    Fecha getFechaAtencion() const;
    Hora getHoraAtencion() const;
    float getImporteConsulta() const;
    bool getCancelado() const;
    bool getSobreturno() const;
    Hora getDuracionTurno() const;
    const char* getObservaciones() const;

    // Setters
    void setId(int id);
    void setIdPaciente(const int idPaciente[]);
    void setIdMedicoEspecialidad(const int idMedicoEspecialidad[]);
    void setFechaAtencion(Fecha fecha);
    void setHoraAtencion(Hora hora);
    void setImporteConsulta(float importe);
    void setCancelado(bool cancelado);
    void setSobreturno(bool sobreturno);
    void setDuracionTurno(Hora duracion); // por defecto 15 minutos
    void setObservaciones(const char* observaciones);

    // Validación
    bool validarTurno();  // Incluye verificar si el paciente ya tiene turno ese día y hora con otro médico
};
