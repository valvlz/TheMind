#include <iostream>
#include "Juego.h"

using namespace std;

Juego::Juego() {
    nivel = 1;
    vidas = 3;
    ultimaCarta = 0;
}

void Juego::iniciarJuego() {
    int numJugadores;
    cout << "Ingrese numero de jugadores: ";
    cin >> numJugadores;

    for (int i = 0; i < numJugadores; i++) {
        string nombre;
        cout << "Nombre del jugador " << i + 1 << ": ";
        cin >> nombre;
        jugadores.push_back(Jugador(nombre));
    }
}

void Juego::repartirCartas() {
    for (int i = 0; i < nivel; i++) {
        for (int j = 0; j < jugadores.size(); j++) {
            jugadores[j].recibirCarta(mazo.repartir());
        }
    }
}

void Juego::jugarRonda() {
    cout << "Jugando ronda nivel " << nivel << endl;

    for (int i = 0; i < jugadores.size(); i++) {
        Carta c = jugadores[i].jugarCarta();

        cout << "Jugador " << i + 1 << " jugó: " << c.getNumero() << endl;

        if (c.getNumero() < ultimaCarta) {
            cout << "¡Error! Se perdió una vida" << endl;
            vidas--;
        }

        ultimaCarta = c.getNumero();
    }

    cout << "Vidas restantes: " << vidas << endl;
}