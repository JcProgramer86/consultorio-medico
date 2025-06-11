#pragma once
#include <sstream>

class Hora {
private:
    int _hora;
    int _minuto;

public:

    Hora();
    Hora(int hora, int minuto);

    // Setters
    void setHora(int hora);
    void setMinuto(int minuto);

    // Getters
    int getHora() const;
    int getMinuto() const;

    bool operator==(const Hora& other) const;
    std::string toString() const;

};
