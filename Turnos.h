
#pragma once

#include "Fecha.h"
#include "Hora.h"

class Turno {
private:
    int _idTurno;
    int _idPaciente[10];
    int _idMedico[10];
    Fecha _fechaTurno;
    Hora _horaTurno;
    float _importeConsulta;

public:

    Turno();

    Turno(int idTurno, int idPaciente[], int idMedico[], Fecha fechaTurno, Hora horaTurno, float importeConsulta);

    // Getters
    int getIdTurno() const;
    const int* getIdPaciente() const;
    const int* getIdMedico() const;
    Fecha getFechaTurno() const;
    Hora getHoraTurno() const;
    float getImporteConsulta() const;

    // Setters
    void setIdTurno(int idTurno);
    void setIdPaciente(const int idPaciente[]);
    void setIdMedico(const int idMedico[]);
    void setFechaTurno(Fecha fechaTurno);
    void setHoraTurno(Hora horaTurno);
    void setImporteConsulta(float importeConsulta);

    // Método
    bool validarTurno();
};
