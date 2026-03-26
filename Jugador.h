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
    Carta jugarCarta();             // jugar carta
    string getNombre();             // obtener nombre
};

#endif