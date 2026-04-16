#include "Jugador.h"

Jugador::Jugador(string nombre) {
    this->nombre = nombre;
}


void Jugador::recibirCarta(Carta carta) {
    mano.push_back(carta);
}

Carta Jugador::jugarCarta() {
    Carta c = mano.back();
    mano.pop_back();
    return c;
}