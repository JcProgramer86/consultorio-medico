#pragma once


class ManagerMedico
{
public:

    void registrarNuevoMedico();
    Medico buscarMedicoPorDni(const std::string& dni);  // ← Método que devuelve un objeto Medico
    bool modificarMedicoPorDni(const std::string& dni);//Tengo que actualizar el .dat
    void listarMedicos();//mostrar lo medicos
};

