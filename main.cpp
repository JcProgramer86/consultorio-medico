#include <iostream>
#include <locale>
#include "Sandbox.h"

using namespace std;

int main() {
    setlocale(LC_ALL, ""); // Para mostrar acentos correctamente en consola

    // ejecutarSandboxMedico();
    // ejecutarSandboxPaciente();

    ejecutarBuscarPacientePorNombre("Luis");
    // ejecutarSandboxTurno();
    // ejecutarBuscarTurnoPorId(1);

    return 0;
}
