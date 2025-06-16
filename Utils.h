#pragma once
#include <iostream>
#include <string>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
inline void limpiarPantalla() { system("cls"); }
#else
inline void limpiarPantalla() { system("clear"); }
#endif

inline void esperarEnter() {
    std::cout << "\nPresione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();
}

inline void printHeader(const std::string& titulo) {
    int ancho = 38;
    std::string padding((ancho - titulo.length()) / 2, '=');
    std::cout << "\n" << padding << " " << titulo << " " << padding;
    if ((ancho - titulo.length()) % 2 != 0) std::cout << "=";
    std::cout << std::endl;
}
