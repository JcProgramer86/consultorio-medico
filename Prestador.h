#pragma once
#include <string>

class Prestador {
private:
    int   _id;
    char  _codPrestador[10];
    char  _nombrePrestador[100];
    bool  _enabled;

    static int _globalCounter;

public:
    // Constructores
    Prestador();
    Prestador(int id,std::string codPrestador,std::string nombrePrestador,bool enabled);

    // Getters
    int   getId();
    std::string getCodPrestador();
    std::string getNombrePrestador();
    bool  isEnabled();

    // Setters
    void setId(int id);
    void setCodPrestador(std::string codPrestador);
    void setNombrePrestador(std::string nombrePrestador);
    void setEnabled(bool enabled);

    void generarCodigo(std::string& nombreObraSocial);
};

