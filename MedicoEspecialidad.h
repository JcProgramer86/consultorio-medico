#pragma once


class MedicoEspecialidad{
private:
    int _id;
    int _idEspecialidad;
    int _idMedico;

public:
    MedicoEspecialidad();

    MedicoEspecialidad(int id, int idEsp, int idMed){

    void set_id(int id);
    void set_idEspecialidad(int idEsp);
    void set_idMedico(int idMed);

    int getId ();
    int getIdEspecialidad();
    int getIdMedico();

};
