#ifndef JUGADOR_H
#define JUGADOR_H

#include <vector>
#include <string>
#include "Carta.h"

using namespace std;

class Jugador {
private:
    string nombre;
    vector<Carta> mano;

public:
    Jugador(string nombre);
    void recibirCarta(Carta carta);
    Carta jugarCarta();
    bool tieneCartas() const;
    void ordenarMano();
};

#endif