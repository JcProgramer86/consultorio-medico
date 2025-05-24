#include "Persona.h"
#include "Fecha.h"
#include <cstring>
#include <iostream>


Persona::Persona() {
    _id = 0;
    strcpy(_dni, "");
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_telefono, "");
    strcpy(_email, "");
    _fechaNacimiento = Fecha();
}


    Persona::Persona(int id, std::string dni, std::string nombre, std::string apellido, std::string telefono, std::string email, Fecha fechaNacimiento) {
        set_id(id);
        set_dni(dni);
        set_nombre(nombre);
        set_apellido(apellido);
        set_telefono(telefono);
        set_email(email);
        set_fechaNacimiento(fechaNacimiento);
    }


    // Getters
    int Persona::get_id() const { return _id; }
    std::string Persona::get_dni() const { return std::string(_dni); }
    std::string Persona::get_nombre() const { return std::string(_nombre); }
    std::string Persona::get_apellido() const { return std::string(_apellido); }
    std::string Persona::get_telefono() const { return std::string(_telefono); }
    std::string Persona::get_email() const { return std::string(_email); }
    Fecha Persona::get_fechaNacimiento() const { return _fechaNacimiento; }


    //Setters
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


  bool Persona::validarDNI(std::string dni) {
    // Un DNI válido tiene entre 7 y 8 dígitos.
    // Convertimos la longitud a 'int' para evitar el warning de 'signed/unsigned mismatch'.
    int largo_dni = dni.length(); // ¡Aquí está el cambio clave!

    if (largo_dni < 7 || largo_dni > 8) {
        return false;
    }
    // Ahora 'i' (int) se compara con 'largo_dni' (int), eliminando el warning.
    for (int i = 0; i < largo_dni; i++) { // Usamos largo_dni aquí
        char c = dni[i];
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

  bool Persona::validarTelefono(std::string tel) {

    int largo_tel = tel.length();

    if(largo_tel < 10 || largo_tel > 11){
        return false;
    }
    // Ahora 'i' (int) se compara con 'largo_tel' (int), eliminando el warning.
    for(int i = 0 ;i < largo_tel; i++){
        if(tel[i] < '0' || tel[i] > '9'){
            return false;
        }
    }
    return true;
}

    bool Persona::validarEmail(std::string email) {
        int arroba = -1;
        // Obtenemos la longitud como un 'int'. Esto es para evitar la advertencia
        // de comparación de tipos (signed vs unsigned), ya que 'length()' devuelve un tipo sin signo.
        // Para longitudes típicas de emails, un 'int' es suficiente.
        int largo = email.length();

        // Recorremos la cadena usando un bucle 'for' tradicional con un índice 'i'.
        for(int i = 0; i < largo; i++){
            char c = email[i]; // Accedemos al carácter en la posición 'i'.
            if(c == ' ') return false; // Si encontramos un espacio, el email no es válido.
            if(c == '@'){
                if(arroba != -1) return false; // Si ya encontramos una '@', y aparece otra, el email no es válido.
                arroba = i; // Guardamos la posición de la primera '@'.
            }
        }

        // Verificamos la posición de la '@'. No puede estar al principio o al final.
        if(arroba <= 0 || arroba >= largo - 1) return false;

        bool puntoMail = false;
        // Buscamos un punto después de la '@'. Empezamos a buscar 2 posiciones después de la '@'.
        // Esto asume que hay al menos un carácter entre la '@' y el punto, y que el punto no es el último.
        for(int i = arroba + 2 ;i < largo - 1; i++){
            if(email[i] == '.'){
                puntoMail = true;
                break; // Si encontramos un punto, ya no necesitamos buscar más.
            }
        }
        return puntoMail; // Retornamos si encontramos un punto.
    }
