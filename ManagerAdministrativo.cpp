#include "ManagerAdministrativo.h"
#include "ArchivoTurno.h"
#include <iostream>
using namespace std;

ManagerAdministrativo::ManagerAdministrativo() {
    // Constructor vacío
}
float ManagerAdministrativo::obtenerFacturacionDelMes() {
    int mes, anio;
    cout << "Ingrese el mes (1-12): ";
    cin >> mes;
    cout << "Ingrese el anio: ";
    cin >> anio;

    ArchivoTurno archivoTurno("turnos.dat");
    float totalFacturacion = 0.0f;

    int cantidadTurnos = archivoTurno.CantidadRegistros();

    for (int i = 0; i < cantidadTurnos; i++) {
        Turno turno = archivoTurno.Leer(i);
        Fecha fecha = turno.getFechaAtencion();

        if (fecha.getMes() == mes && fecha.getAnio() == anio && !turno.getCancelado()) {
            totalFacturacion += turno.getImporteConsulta();
        }
    }

    cout << "La facturacion del mes " << mes << "/" << anio << " es: $" << totalFacturacion << endl;
    system("pause");

    return totalFacturacion;
}
