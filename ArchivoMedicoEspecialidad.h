#pragma once
#include <string>
#include "MedicoEspecialidad.h"


class ArchivoMedicoEspecialidad {
private:
    std::string _nombreArchivo;

public:
    ArchivoMedicoEspecialidad(std::string nombreArchivo);
    bool Guardar(MedicoEspecialidad link);
    bool Guardar(MedicoEspecialidad link, int posicion); // Añadido para completitud
    MedicoEspecialidad Leer(int posicion); // Para leer un registro específico por posición
    int Buscar(int idMedico, int idEspecialidad); // Busca un enlace específico (médico-especialidad)
    int CantidadRegistros(); // Para obtener el total de registros

    // Eliminado: int getEspecialidadesForMedico(int idMedico, MedicoEspecialidad* linksArray, int maxArraySize);
    // La lógica para obtener todas las especialidades de un médico se hará iterando el archivo
    // y filtrando en el código que llama a esta clase.
};
