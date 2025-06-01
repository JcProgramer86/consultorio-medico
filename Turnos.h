
#pragma once
#include <string>
#include "Fecha.h"
#include "Hora.h"

class Turno
{
private:
    int _idTurno;
    int _idPaciente[10];
    int _idMedico[10];
    Fecha _fechaTurno;
    Hora _horaTurno;
    float _importeConsulta;
    bool _cancelado;
    bool _sobreturno;
    Hora _duracionTurno;
    char _observaciones[100];


public:

    Turno();

    Turno(int idTurno, int idPaciente[], int idMedico[], Fecha fechaTurno, Hora horaTurno, float importeConsulta,
      bool cancelado, bool sobreturno, Hora duracionTurno, const std::string& observaciones);


    // Getters
    int getIdTurno() const;
    const int* getIdPaciente() const;
    const int* getIdMedico() const;
    Fecha getFechaTurno() const;
    Hora getHoraTurno() const;
    float getImporteConsulta() const;
     bool getCancelado() const;
    bool getSobreturno() const;
    Hora getDuracionTurno() const;
    const char* getObservaciones() const;

    // Setters
    void setIdTurno(int idTurno);
    void setIdPaciente(const int idPaciente[]);
    void setIdMedico(const int idMedico[]);
    void setFechaTurno(Fecha fechaTurno);
    void setHoraTurno(Hora horaTurno);
    void setImporteConsulta(float importeConsulta);
    void setCancelado(bool cancelado);
    void setSobreturno(bool sobreturno);
    void setDuracionTurno(Hora duracion);
    void setObservaciones(const char* observaciones);


    // Método
    bool validarTurno();
};
