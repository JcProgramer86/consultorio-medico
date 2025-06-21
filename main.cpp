#include <iostream>

#include "Menu.h"
#include "Sandbox.h"
#include <clocale>
#include "CargarDatosPrueba.h"
using namespace std;

int main()
{

    setlocale(LC_ALL, "Spanish");
    //ejecutarSandboxMedico();
    //ejecutarSandboxPaciente();

    //ejecutarBuscarPacientePorNombre("luis");
    //ejecutarSandboxMedicoEspecialidad();
    //ejecutarSandboxPrestador();
    //ejecutarSandboxFacturacionMensual();

    //ejecutarSandboxListarPacientesAtendidosPorEspecialidadYMes();
    // ejecutarSandboxOcupacionPorDiaDeMedico();
    //ejecutarSandboxOcupacionPorMesDeMedico();
    // ejecutarSandboxOcupacionPorMesEspecialidad();
    // ejecutarSandboxOcupacionTotalPorMes();
   // ejecutarCargaDatosPrueba();


    Menu menu;
    menu.menuPrincipal();
    return 0;
}
