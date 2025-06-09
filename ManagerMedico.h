#pragma once


class ManagerMedico
{
public:

   void registrarNuevoMedico();
    void listarMedicos();
    bool modificarMedicoPorDni();
    Medico buscarMedicoPorDni(const std::string& dni);  // ya lo tenías
    void buscarYMostrarMedicoPorDni();
};

