#include "Jugador.h"

// Constructor: guarda el nombre del jugador
Jugador::Jugador(string nombre) {
    this->nombre = nombre;
}

// Agrega una carta a la mano del jugador
void Jugador::recibirCarta(Carta carta) {
    mano.push_back(carta);
}

// El jugador juega una carta (la última de su mano)
Carta Jugador::jugarCarta() {
    Carta c = mano.back(); // toma la última carta
    mano.pop_back();       // la elimina de la mano
    return c;
}

// Devuelve el nombre del jugador
string Jugador::getNombre() {
    return nombre;
}