#include <iostream>
#include "Juego.h"
#include "Carta.h"
#include <algorithm>
#include <fstream>

using namespace std;

// Función para ordenar cartas
bool compararCartas(Carta a, Carta b) {
    return a.getNumero() < b.getNumero();
}

// Constructor
Juego::Juego() : nivel(1), vidas(3), ultimaCarta(0) {}

// Configurar jugadores
void Juego::configurarJugadores() {
    int numJugadores;
    cout << "Ingrese número de jugadores: ";
    cin >> numJugadores;

    jugadores.clear();

    for (int i = 0; i < numJugadores; i++) {
        string nombre;
        cout << "Nombre del jugador " << i + 1 << ": ";
        cin >> nombre;
        jugadores.push_back(Jugador(nombre));
    }
}

// Reiniciar mazo
void Juego::reiniciarMazo() {
    mazo = Mazo();
    mazo.barajar();
}

// Iniciar juego
void Juego::iniciarJuego() {
    configurarJugadores();
    reiniciarMazo();
}

// Repartir cartas
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

// Jugar una ronda
void Juego::jugarRonda() {
    cout << "Jugando ronda nivel " << nivel << endl;

    vector<Carta> jugadas;

    for (int i = 0; i < jugadores.size(); i++) {
        jugadas.push_back(jugadores[i].jugarCarta());
    }

    // Ordenar cartas
    sort(jugadas.begin(), jugadas.end(), compararCartas);

    // Mostrar cartas
    for (int i = 0; i < jugadas.size(); i++) {
        cout << "Carta jugada: " << jugadas[i].getNumero() << endl;
    }

    cout << "Ronda correcta!" << endl;

    // Avanzar nivel
    nivel++;
    ultimaCarta = 0;
}

// Obtener vidas
int Juego::getVidas() {
    return vidas;
}

// Guardar partida
void Juego::guardarPartida() {
    ofstream archivo("partida.txt");

    if (archivo.is_open()) {
        // Guardar jugadores
        archivo << jugadores.size() << endl;
        for (int i = 0; i < jugadores.size(); i++) {
            archivo << jugadores[i].getNombre() << endl;
        }

        // Guardar estado
        archivo << nivel << endl;
        archivo << vidas << endl;

        archivo.close();
        cout << "Partida guardada" << endl;
    }
}

// Cargar partida
void Juego::cargarPartida() {
    ifstream archivo("partida.txt");

    if (archivo.is_open()) {
        int numJugadores;
        archivo >> numJugadores;

        jugadores.clear();

        // Cargar jugadores
        for (int i = 0; i < numJugadores; i++) {
            string nombre;
            archivo >> nombre;
            jugadores.push_back(Jugador(nombre));
        }

        // Cargar estado
        archivo >> nivel;
        archivo >> vidas;

        archivo.close();
        cout << "Partida cargada" << endl;
    } else {
        cout << "No hay partida guardada" << endl;
    }
}