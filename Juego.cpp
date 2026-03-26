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
Juego::Juego() : nivel(1), vidas(2), estrellas(1) {}

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

// Jugar una ronda
void Juego::jugarRonda() {
    cout << "\n--- Nivel " << nivel << " ---" << endl;

    while (true) {

        // Verificar si todos los jugadores se quedaron sin cartas
        bool todosSinCartas = true;
        for (auto& j : jugadores) {
            if (j.cantidadCartas() > 0) {
                todosSinCartas = false;
                break;
            }
        }

        if (todosSinCartas) {
            cout << "Nivel superado!" << endl;

            // Recompensas
            if (nivel == 2 || nivel == 5 || nivel == 8) {
                estrellas++;
                cout << "Ganaste una estrella ninja!" << endl;
            } else if (nivel == 3 || nivel == 6 || nivel == 9) {
                vidas++;
                cout << "Ganaste una vida!" << endl;
            }

            nivel++;
            return;
        }

        cout << "\nVidas: " << vidas << " | Estrellas: " << estrellas << endl;

        cout << "¿Qué deseas hacer?\n";
        cout << "1. Jugar carta\n";
        cout << "2. Usar estrella ninja\n";

        int opcion;
        cin >> opcion;

        if (opcion == 1) {

            int jugadorIndex;
            cout << "Seleccione jugador (1-" << jugadores.size() << "): ";
            cin >> jugadorIndex;
            jugadorIndex--;

            if (jugadorIndex < 0 || jugadorIndex >= jugadores.size()) {
                cout << "Jugador inválido\n";
                continue;
            }

            Jugador& j = jugadores[jugadorIndex];

            if (j.cantidadCartas() == 0) {
                cout << "Ese jugador no tiene cartas\n";
                continue;
            }

            cout << "Cartas de " << j.getNombre() << ": ";
            j.mostrarMano();

            int indiceCarta;
            cout << "Seleccione índice de carta: ";
            cin >> indiceCarta;

            if (indiceCarta < 0 || indiceCarta >= j.cantidadCartas()) {
                cout << "Índice inválido\n";
                continue;
            }

            Carta jugada = j.jugarCartaPorIndice(indiceCarta);
            int valor = jugada.getNumero();

            cout << j.getNombre() << " juega: " << valor << endl;

            // VALIDAR ERROR
            bool error = false;

            for (auto& otro : jugadores) {
                for (int i = 0; i < otro.cantidadCartas(); i++) {
                    if (otro.verCarta(i).getNumero() < valor) {
                        error = true;
                    }
                }
            }

            if (error) {
                cout << "ERROR! Se pierde una vida\n";
                vidas--;

                // eliminar cartas menores
                for (auto& otro : jugadores) {
                    for (int i = otro.cantidadCartas() - 1; i >= 0; i--) {
                        if (otro.verCarta(i).getNumero() < valor) {
                            cout << "Se descarta " << otro.verCarta(i).getNumero() << endl;
                            otro.eliminarCarta(i);
                        }
                    }
                }
            }

            pilaCentral.push_back(valor);
        }

        else if (opcion == 2) {

            if (estrellas <= 0) {
                cout << "No tienes estrellas disponibles\n";
                continue;
            }

            estrellas--;

            cout << "Usando estrella ninja...\n";

            for (auto& j : jugadores) {

                int menor = 101;
                int indice = -1;

                for (int i = 0; i < j.cantidadCartas(); i++) {
                    if (j.verCarta(i).getNumero() < menor) {
                        menor = j.verCarta(i).getNumero();
                        indice = i;
                    }
                }

                if (indice != -1) {
                    cout << j.getNombre() << " descarta: " << menor << endl;
                    j.eliminarCarta(indice);
                }
            }
        }
    }
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