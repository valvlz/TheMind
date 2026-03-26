#ifndef JUGADOR_H
#define JUGADOR_H

#include <vector>
#include <string>
#include "Carta.h"

using namespace std;

class Jugador {
private:
    string nombre;          // nombre del jugador
    vector<Carta> mano;     // cartas del jugador

public:
    Jugador(string nombre);         // constructor
    void recibirCarta(Carta carta); // agregar carta

    Carta jugarCartaPorIndice(int indice);
    int cantidadCartas() const;
    Carta verCarta(int indice) const;
    void eliminarCarta(int indice);

    string getNombre();             // obtener nombre
    void mostrarMano() const;
};

#endif