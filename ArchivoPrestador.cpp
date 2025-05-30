#include "Fecha.h"
#include "ArchivoPrestador.h"

ArchivoPrestador::ArchivoPrestador(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool ArchivoPrestador::Guardar(Prestador Prestador){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&Prestador, sizeof(Prestador), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool ArchivoPrestador::Guardar(Prestador Prestador, int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(Prestador) * posicion, SEEK_SET);
    bool ok = fwrite(&Prestador, sizeof(Prestador), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int ArchivoPrestador::Buscar(int IDPrestador){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return -1;
    }
    Prestador Prestador;
    int i = 0;
    while(fread(&Prestador, sizeof(Prestador), 1, pArchivo)){
        if(Prestador.getId() == IDPrestador){
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}

Prestador ArchivoPrestador::Leer(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return Prestador();
    }
    Prestador Prestador;
    fseek(pArchivo, sizeof(Prestador) * posicion, SEEK_SET);
    fread(&Prestador, sizeof(Prestador), 1, pArchivo);
    fclose(pArchivo);
    return Prestador;
}

int ArchivoPrestador::CantidadRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(Prestador);
    fclose(pArchivo);
    return cantidadRegistros;
}

void ArchivoPrestador::Leer(int cantidadRegistros, Prestador *vector){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], sizeof(Prestador), 1, pArchivo);
    }
    fclose(pArchivo);
}
