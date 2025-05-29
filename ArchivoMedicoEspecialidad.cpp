#include "Fecha.h"
#include "ArchivoMedicoEspecialidad.h"

ArchivoMedicoEspecialidad::ArchivoMedicoEspecialidad(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool ArchivoMedicoEspecialidad::Guardar(MedicoEspecialidad medicoEspecialidad){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&medicoEspecialidad, sizeof(MedicoEspecialidad), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool ArchivoMedicoEspecialidad::Guardar(MedicoEspecialidad MedicoEspecialidad, int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(MedicoEspecialidad) * posicion, SEEK_SET);
    bool ok = fwrite(&MedicoEspecialidad, sizeof(MedicoEspecialidad), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int ArchivoMedicoEspecialidad::Buscar(int IDMedicoEspecialidad){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return -1;
    }

    MedicoEspecialidad MedicoEspecialidad;
    int i = 0;

    while(fread(&MedicoEspecialidad, sizeof(MedicoEspecialidad), 1, pArchivo)){
        if(MedicoEspecialidad.getId() == IDMedicoEspecialidad){
            fclose(pArchivo);
            return i;
        }
        i++;
    }

    fclose(pArchivo);
    return -1;
}


MedicoEspecialidad ArchivoMedicoEspecialidad::Leer(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return MedicoEspecialidad();
    }

    MedicoEspecialidad MedicoEspecialidad;

    fseek(pArchivo, sizeof(MedicoEspecialidad) * posicion, SEEK_SET);
    fread(&MedicoEspecialidad, sizeof(MedicoEspecialidad), 1, pArchivo);
    fclose(pArchivo);

    return MedicoEspecialidad;
}

int ArchivoMedicoEspecialidad::CantidadRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return 0;
    }

    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(MedicoEspecialidad);
    fclose(pArchivo);

    return cantidadRegistros;
}

void ArchivoMedicoEspecialidad::Leer(int cantidadRegistros, MedicoEspecialidad *vector){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return;
    }

    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], sizeof(MedicoEspecialidad), 1, pArchivo);
    }

    fclose(pArchivo);
}

