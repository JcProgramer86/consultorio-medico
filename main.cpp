#include <iostream>

#include "Menu.h"
#include "Sandbox.h"
#include <clocale>

using namespace std;

int main() {

setlocale(LC_ALL, "Spanish");
    //ejecutarSandboxMedico();
    //ejecutarSandboxPaciente();

    //ejecutarBuscarPacientePorNombre("luis");
    //ejecutarSandboxMedicoEspecialidad();
    //ejecutarSandboxPrestador();

    Menu menu;
    menu.menuPrincipal();
    return 0;
}
