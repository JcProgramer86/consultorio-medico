#pragma once


void ejecutarSandboxMedico();
void ejecutarSandboxPaciente();
void ejecutarBuscarPacientePorNombre(const std::string& nombreBuscado);
void ejecutarSandboxMedicoEspecialidad();
void ejecutarSandboxPrestador();

// Métodos para testear Turnos
void ejecutarSandboxTurno();  // Guarda y lista turnos
void ejecutarBuscarTurnoPorId(int idBuscado);  // Buscar turno por ID específico
// Metodo para testear facturacion
void ejecutarSandboxFacturacionMensual();
// metodo para lsitr pac x espex mes
void ejecutarSandboxListarPacientesAtendidosPorEspecialidadYMes();
//metodos de submenues de ocupacion medica
void ejecutarSandboxOcupacionPorDiaDeMedico();
void ejecutarSandboxOcupacionPorMesDeMedico();
