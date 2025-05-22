#pragma once


void ejecutarSandboxMedico();
void ejecutarSandboxPaciente();
void ejecutarBuscarPacientePorNombre(const std::string& nombreBuscado);


// Métodos para testear Turnos
void ejecutarSandboxTurno();  // Guarda y lista turnos
void ejecutarBuscarTurnoPorId(int idBuscado);  // Buscar turno por ID específico
