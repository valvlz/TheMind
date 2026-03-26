#include <iostream>
#include "Juego.h"
#include "Carta.h"
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include "Ronda.h"

using namespace std;

// Función para ordenar cartas
bool compararCartas(Carta a, Carta b) {
    return a.getNumero() < b.getNumero();
}

// Constructor
Juego::Juego() : nivel(1), vidas(2), estrellas(1) {}

// Configurar jugadores
void Juego::configurarJugadores() {
int numJugadores;

    do {
        cout << "Ingrese numero de jugadores (2-2): ";
        cin >> numJugadores;

        if (numJugadores != 2) {
            cout << "Este juego solo permite 2 jugadores.\n";
        }

    } while (numJugadores != 2);

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
    pilaCentral.clear();

    for (int i = 0; i < nivel; i++) {
        for (int j = 0; j < jugadores.size(); j++) {
            if (!mazo.estaVacio()) {
                jugadores[j].recibirCarta(mazo.repartir());
            }
        }
    }
    cout << "\n--- Cartas repartidas ---" << endl;

    for (size_t i = 0; i < jugadores.size(); i++) {
        cout << "Jugador " << i + 1 << ": ";
        jugadores[i].mostrarMano();
    }
}

void Juego::jugarRonda() {
    Ronda ronda(nivel);
    ronda.jugar(jugadores, vidas, estrellas);
    nivel++;
}

// Obtener vidas
int Juego::getVidas() const{
    return vidas;
}

int Juego::getEstrellas() const {
    return estrellas;
}

// Guardar partida
void Juego::guardarPartida() {
    ofstream archivo("partida.txt");

    if (!archivo.is_open()) {
        cout << "Error al guardar\n";
        return;
    }

    // jugadores
    archivo << jugadores.size() << endl;
    for (auto& j : jugadores) {
        archivo << j.getNombre() << endl;
    }

    // Guardar estado
    archivo << nivel << endl;
    archivo << vidas << endl;
    archivo << estrellas << endl;

     // pila central
    archivo << pilaCentral.size() << endl;
    for (int v : pilaCentral) {
        archivo << v << " ";
    }
    archivo << endl;

    // manos de jugadores
    for (auto& j : jugadores) {
        archivo << j.cantidadCartas() << endl;
        for (int i = 0; i < j.cantidadCartas(); i++) {
            archivo << j.verCarta(i).getNumero() << " ";
        }
        archivo << endl;
    }

    archivo.close();
    cout << "Partida guardada correctamente\n" << endl;
}


// Cargar partida
void Juego::cargarPartida() {
    ifstream archivo("partida.txt");

    if (!archivo.is_open()) {
        cout << "No hay partida guardada\n";
        return;
    }
    
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
    archivo >> estrellas;

    // pila central
    int tamanoPila;
    archivo >> tamanoPila;
    pilaCentral.clear();

    for (int i = 0; i < tamanoPila; i++) {
        int valor;
        archivo >> valor;
        pilaCentral.push_back(valor);
    }

    // manos
    for (auto& j : jugadores) {
        int cantidad;
        archivo >> cantidad;

        for (int i = 0; i < cantidad; i++) {
            int num;
            archivo >> num;
            j.recibirCarta(Carta(num));
        }
    }
    archivo.close();
    cout << "Partida cargada correctamente\n" << endl;
    
}