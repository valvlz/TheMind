#include <iostream>
#include "Juego.h"
#include "Carta.h"
#include <algorithm>
#include <fstream>

using namespace std;

bool compararCartas(Carta a, Carta b) {
    return a.getNumero() < b.getNumero();
}

Juego::Juego() {
    nivel = 1;
    vidas = 3;
    ultimaCarta = 0;
}

void Juego::iniciarJuego() {
    int numJugadores;
    cout << "Ingrese numero de jugadores: ";
    cin >> numJugadores;

    jugadores.clear(); // limpiar por si acaso

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

    vector<Carta> jugadas;

    for (int i = 0; i < jugadores.size(); i++) {
        jugadas.push_back(jugadores[i].jugarCarta());
    }

    sort(jugadas.begin(), jugadas.end(), compararCartas);

    for (int i = 0; i < jugadas.size(); i++) {
        cout << "Carta jugada: " << jugadas[i].getNumero() << endl;
    }

    cout << "Ronda correcta!" << endl;

    //AVANZA EL JUEGO
    nivel++;
    ultimaCarta = 0;
}

int Juego::getVidas() {
    return vidas;
}

void Juego::guardarPartida() {
    ofstream archivo("partida.txt");

    if (archivo.is_open()) {
        //guardar jugadores
        archivo << jugadores.size() << endl;
        for (int i = 0; i < jugadores.size(); i++) {
            archivo << jugadores[i].getNombre() << endl;
        }

        //guardar estado
        archivo << nivel << endl;
        archivo << vidas << endl;

        archivo.close();
        cout << "Partida guardada" << endl;
    }
}

void Juego::cargarPartida() {
    ifstream archivo("partida.txt");

    if (archivo.is_open()) {
        int numJugadores;
        archivo >> numJugadores;

        jugadores.clear();

        // cargar jugadores
        for (int i = 0; i < numJugadores; i++) {
            string nombre;
            archivo >> nombre;
            jugadores.push_back(Jugador(nombre));
        }

        // cargar estado
        archivo >> nivel;
        archivo >> vidas;

        archivo.close();
        cout << "Partida cargada" << endl;
    } else {
        cout << "No hay partida guardada" << endl;
    }
}