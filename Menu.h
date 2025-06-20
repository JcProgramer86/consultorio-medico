#pragma once
#include "Paciente.h"
#include "Medico.h"
#include "ManagerAdministrativo.h"

class Menu
{
public:

    void menuPrincipal();

    void menuPaciente();

    void menuMedico();

    void menuTurnos();

    void menuAdministrativo();

   void mostrarSubmenuOcupacionMedica(ManagerAdministrativo& managerAdministrativo);
//lo pasopor ref para evitar copi y que se modifique ahi directamente

    void mostrarSubmenuTurnosCancelados();
    void mostrarSubmenuPacientesAtendidos();


    void menuHeader();

};

