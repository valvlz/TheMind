#include <iostream>
#include "Juego.h"

using namespace std; //

Juego::Juego() : nivel(1), vidas(3), ultimaCarta(0) {}

void Juego::configurarJugadores() {
    int numJugadores;
    cout << "Ingrese número de jugadores: ";
    cin >> numJugadores;

    for (int i = 0; i < numJugadores; i++) {
        string nombre;
        cout << "Nombre del jugador " << i + 1 << ": ";
        cin >> nombre;
        jugadores.push_back(Jugador(nombre));
    }
}

void Juego::reiniciarMazo() {
    mazo = Mazo();
    mazo.barajar();
}

void Juego::iniciarJuego() {
    configurarJugadores();
    reiniciarMazo();
}

void Juego::repartirCartas() {

    reiniciarMazo();

    for (int i = 0; i < nivel; i++) {
        for (int j = 0; j < jugadores.size(); j++) {
            if (!mazo.estaVacio()) {
                jugadores[j].recibirCarta(mazo.repartir());
            }
        }
    }
}

void Juego::jugarRonda() {
    cout << "Jugando ronda nivel " << nivel << endl;

    for (int i = 0; i < jugadores.size(); i++) {

        if (gameOver()) {
            cout << "GAME OVER" << endl;
            return;
        }

        if (!jugadores[i].tieneCartas()) {
            continue; //si el jugador no tiene cartas, pasa al siguiente
        }

        Carta c = jugadores[i].jugarCarta();

        cout << "Jugador " << i + 1 << " jugó: " << c.getNumero() << endl;

        if (c.getNumero() < ultimaCarta) {
            cout << "Error! Se perdió una vida" << endl;
            vidas--;
        }

        ultimaCarta = c.getNumero();

    }

    cout << "Vidas restantes: " << vidas << endl;

    nivel++;
    ultimaCarta = 0;

}

int Juego::getVidas() const {
    return vidas;
}
bool Juego::gameOver() const {
    return vidas <= 0;
}