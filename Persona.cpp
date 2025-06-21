#include "Persona.h"
#include "Fecha.h"
#include <cstring>
#include <iostream>
#include <regex>

// Constructor por defecto
Persona::Persona() {
    _id = 0;
    strcpy(_dni, "");
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_telefono, "");
    strcpy(_email, "");
    _fechaNacimiento = Fecha();
    _enabled = true;
}

// Constructor parametrizado
Persona::Persona(int id, std::string dni, std::string nombre, std::string apellido,
                 std::string telefono, std::string email,
                 Fecha fechaNacimiento, bool enabled) {
    set_id(id);
    set_dni(dni);
    set_nombre(nombre);
    set_apellido(apellido);
    set_telefono(telefono);
    set_email(email);
    set_fechaNacimiento(fechaNacimiento);
    set_enabled(enabled);
}

// Getters
int Persona::get_id() const { return _id; }
std::string Persona::get_dni() const { return std::string(_dni); }
std::string Persona::get_nombre() const { return std::string(_nombre); }
std::string Persona::get_apellido() const { return std::string(_apellido); }
std::string Persona::get_telefono() const { return std::string(_telefono); }
std::string Persona::get_email() const { return std::string(_email); }
Fecha Persona::get_fechaNacimiento() const { return _fechaNacimiento; }
bool Persona::get_enabled() const { return _enabled; }  // corregido nombre y const

// Setters
void Persona::set_id(int id) { _id = id; }

void Persona::set_dni(std::string dni) {
    strncpy(_dni, dni.c_str(), sizeof(_dni) - 1);
    _dni[sizeof(_dni) - 1] = '\0';
}

void Persona::set_nombre(std::string nombre) {
    strncpy(_nombre, nombre.c_str(), sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0';
}

void Persona::set_apellido(std::string apellido) {
    strncpy(_apellido, apellido.c_str(), sizeof(_apellido) - 1);
    _apellido[sizeof(_apellido) - 1] = '\0';
}

void Persona::set_telefono(std::string telefono) {
    strncpy(_telefono, telefono.c_str(), sizeof(_telefono) - 1);
    _telefono[sizeof(_telefono) - 1] = '\0';
}

void Persona::set_email(std::string email) {
    strncpy(_email, email.c_str(), sizeof(_email) - 1);
    _email[sizeof(_email) - 1] = '\0';
}

void Persona::set_fechaNacimiento(Fecha fechaNacimiento) {
    _fechaNacimiento = fechaNacimiento;
}

void Persona::set_enabled(bool enabled) {
    _enabled = enabled;
}

// Validaciones
bool Persona::validarDNI(std::string dni) {
    if (dni.length() < 7 || dni.length() > 8) return false;
    for (char c : dni) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

bool Persona::validarTelefono(std::string tel) {
    if (tel.length() < 10 || tel.length() > 11) return false;
    for (char c : tel) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

bool Persona::validarEmail(std::string email) {
    int arroba = -1;
    int largo = email.length();

    for (int i = 0; i < largo; i++) {
        char c = email[i];
        if (c == ' ') return false;
        if (c == '@') {
            if (arroba != -1) return false;
            arroba = i;
        }
    }
    if (arroba <= 0 || arroba >= largo - 1) return false;

    bool puntoMail = false;
    for (int i = arroba + 2; i < largo - 1; i++) {
        if (email[i] == '.') {
            puntoMail = true;
            break;
        }
    }
    return puntoMail;
}

bool Persona::validarTexto(std::string texto) {
    std::regex patron("^[A-Za-zÁÉÍÓÚáéíóúÑñüÜ'\\- ]+$");
    return std::regex_match(texto, patron) && !texto.empty();
}


