#pragma once

class MedicoEspecialidad {
private:
    int _id;
    int _idEspecialidad;
    int _idMedico;

public:
    // Constructores
    MedicoEspecialidad();
    MedicoEspecialidad(int id, int idEsp, int idMed);

    // Getters
    int getId() const;
    int getIdEspecialidad() const;
    int getIdMedico() const;

    // Setters
    void setId(int id);
    void setIdEspecialidad(int idEsp);
    void setIdMedico(int idMed);
};

