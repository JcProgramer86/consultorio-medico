#pragma once
#include <string>
#include "Fecha.h"

class Persona {
private:
    int _id;
    char _dni[20];
    char _nombre[30];
    char _apellido[30];
    char _telefono[20];
    char _email[40];
    Fecha _fechaNacimiento;


public:

    Persona();

    Persona(int id, std::string dni, std::string nombre, std::string apellido, std::string telefono, std::string email,Fecha fechaNacimiento);

    void set_id(int id);
    void set_dni(std::string dni);
    void set_nombre(std::string nombre);
    void set_apellido(std::string apellido);
    void set_telefono(std::string telefono);
    void set_email(std::string email);
    void set_fechaNacimiento(Fecha fechaNacimiento);

    int get_id() const;
    std::string get_dni() const;
    std::string get_nombre() const;
    std::string get_apellido() const;
    std::string get_telefono() const;
    std::string get_email() const;
    Fecha get_fechaNacimiento() const;


    static bool validarDNI(std::string dni);
    static bool validarTelefono(std::string telefono);
    static bool validarEmail(std::string email);
};

