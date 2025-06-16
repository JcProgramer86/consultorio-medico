#include "Fecha.h"
#include "ArchivoMedico.h"
#include <iostream>
using namespace std;


ArchivoMedico::ArchivoMedico(std::string nombreArchivoMedico){
    _nombreArchivoMedico = nombreArchivoMedico;
}

bool ArchivoMedico::Guardar(Medico medico){
    FILE *pArchivoMedico = fopen(_nombreArchivoMedico.c_str(), "ab");
    if(pArchivoMedico == NULL){
        return false;
    }
    bool ok = fwrite(&medico, sizeof(medico), 1, pArchivoMedico);
    fclose(pArchivoMedico);
    return ok;
}

bool ArchivoMedico::Guardar(Medico medico, int posicion){
    FILE *pArchivoMedico = fopen(_nombreArchivoMedico.c_str(), "rb+");
    if(pArchivoMedico == NULL){
        return false;
    }
    fseek(pArchivoMedico, sizeof(medico) * posicion, SEEK_SET);
    bool ok = fwrite(&medico, sizeof(medico), 1, pArchivoMedico);
    fclose(pArchivoMedico);
    return ok;
}

int ArchivoMedico::Buscar(int IDmedico){
    FILE *pArchivoMedico = fopen(_nombreArchivoMedico.c_str(), "rb");
    if(pArchivoMedico == NULL){
        return -1;
    }
    Medico medico;
    int i = 0;
    while(fread(&medico, sizeof(medico), 1, pArchivoMedico)){
        if(medico.get_id() == IDmedico){
            fclose(pArchivoMedico);
            return i;
        }
        i++;
    }
    fclose(pArchivoMedico);
    return -1;
}
int ArchivoMedico::BuscarPorDni(const std::string& dniMedico) {
    FILE* pArchivo = fopen(_nombreArchivoMedico.c_str(), "rb");
    if (pArchivo == NULL) {
        return -1;
    }
    Medico medico;
    int i = 0;

    while (fread(&medico, sizeof(Medico), 1, pArchivo)) {
        if (medico.get_dni() == dniMedico) {
            fclose(pArchivo);
            return i;
        }
        i++;
    }

    fclose(pArchivo);
    return -1;
}


Medico ArchivoMedico::Leer(int posicion){
    FILE *pArchivoMedico = fopen(_nombreArchivoMedico.c_str(), "rb");
    if(pArchivoMedico == NULL){
        return Medico();
    }
    Medico medico;
    fseek(pArchivoMedico, sizeof(medico) * posicion, SEEK_SET);
    fread(&medico, sizeof(medico), 1, pArchivoMedico);
    fclose(pArchivoMedico);
    return medico;
}

int ArchivoMedico::CantidadRegistros(){
    FILE *pArchivoMedico = fopen(_nombreArchivoMedico.c_str(), "rb");
    if(pArchivoMedico == NULL){
        return 0;
    }
    fseek(pArchivoMedico, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivoMedico) / sizeof(Medico);
    fclose(pArchivoMedico);
    return cantidadRegistros;
}
int ArchivoMedico::generarNuevoId() {
    int cantidad = CantidadRegistros();
    if (cantidad == 0) return 1;

    Medico ultimo = Leer(cantidad - 1);
    return ultimo.get_id() + 1;
}

void ArchivoMedico::Leer(int cantidadRegistros, Medico *vector){
    FILE *pArchivoMedico = fopen(_nombreArchivoMedico.c_str(), "rb");
    if(pArchivoMedico == NULL){
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], sizeof(Medico), 1, pArchivoMedico);
    }
    fclose(pArchivoMedico);
}
bool ArchivoMedico::checkDni(std::string& dni){
    int pos = BuscarPorDni(dni);
    return (pos == -1);
}

