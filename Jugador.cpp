#include "Jugador.h"
#include <iostream>

// Constructor: guarda el nombre del jugador
Jugador::Jugador(string nombre) {
    this->nombre = nombre;
}

// Agrega una carta a la mano del jugador
void Jugador::recibirCarta(Carta carta) {
    mano.push_back(carta);
}

// El jugador juega una carta (de su preferencia)
Carta Jugador::jugarCartaPorIndice(int indice) {
    Carta c = mano[indice];
    mano.erase(mano.begin() + indice);
    return c;
}

int Jugador::cantidadCartas() const {
    return mano.size();
}

Carta Jugador::verCarta(int indice) const {
    return mano[indice];
}

void Jugador::eliminarCarta(int indice) {
    mano.erase(mano.begin() + indice);
}

// Devuelve el nombre del jugador
string Jugador::getNombre() {
    return nombre;
}

// Muestra las cartas en la mano del jugador
void Jugador::mostrarMano() const {
    cout << "Mano: ";
    for (int i = 0; i < mano.size(); i++) {
        cout << "[" << i << "]:" << mano[i].getNumero() << " ";
    }
    cout << endl;
}