#pragma once

class Hora {
private:
    int _hora;
    int _minuto;

public:

    Hora();
    Hora(int hora, int minuto);

    // Setters
    void setHoraAtencion(int hora);
    void setMinutoAtencion(int minuto);

    // Getters
    int getHoraAtencion() const;
    int getMinutoAtencion() const;
};
