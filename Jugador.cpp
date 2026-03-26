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

// El jugador juega una carta (la última de su mano)
Carta Jugador::jugarCarta() {
    Carta c = mano.front(); // en vez de back()
    mano.erase(mano.begin());
    return c;
}

// Devuelve el nombre del jugador
string Jugador::getNombre() {
    return nombre;
}

// Muestra las cartas en la mano del jugador
void Jugador::mostrarMano() const {
    cout << "Mano: ";
    for (const auto& carta : mano) {
        cout << carta.getNumero() << " ";
    }
    cout << endl;
}