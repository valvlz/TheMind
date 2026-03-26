#ifndef JUGADOR_H
#define JUGADOR_H

#include <vector>
#include <string>
#include "Carta.h"

using namespace std;

class Jugador {
private:
    string nombre;          // nombre del jugador
    vector<Carta> mano;     // cartas que tiene el jugador

public:
    Jugador(string nombre);     // constructor
    void recibirCarta(Carta carta);  // agregar carta a la mano
    Carta jugarCarta();             // jugar (sacar) una carta
    string getNombre();             // obtener el nombre del jugador
};

#endif