#pragma once

class MedicoEspecialidad {
private:
    int _id;           // ID único para el registro de la relación (opcional, pero útil para archivos)
    int _idEspecialidad; // ID de la especialidad
    int _idMedico;     // ID del médico

public:
    // Constructor por defecto
    MedicoEspecialidad();
    // Constructor parametrizado
    MedicoEspecialidad(int id, int idEspecialidad, int idMedico);

    // Getters (métodos const para no modificar el objeto)
    int getId() const;
    int getIdEspecialidad() const;
    int getIdMedico() const;

    // Setters
    void setId(int id);
    void setIdEspecialidad(int idEspecialidad);
    void setIdMedico(int idMedico);
};
