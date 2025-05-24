#include "Fecha.h"
#include "ArchivoMedico.h"

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

// Implementación de la función Leer que recibe un vector
void ArchivoMedico::Leer(int cantidadRegistros, Medico *vector) {
    FILE *pArchivoMedico = fopen(_nombreArchivoMedico.c_str(), "rb");
    if(pArchivoMedico == NULL){
        return; // Retornar si no se puede abrir el archivo
    }
    fread(vector, sizeof(Medico), cantidadRegistros, pArchivoMedico);
    fclose(pArchivoMedico);
}
