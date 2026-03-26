#include "Ronda.h"
#include <iostream>
#include <cstdlib> // para limpiar pantalla

using namespace std;

// función para limpiar consola
void limpiarPantalla() {
    system("cls"); // Windows
}

Ronda::Ronda(int nivel) {
    this->nivel = nivel;
}

vector<int> Ronda::getPila() const {
    return pilaCentral;
}

void Ronda::jugar(vector<Jugador>& jugadores, int& vidas, int& estrellas)
{
    while (true) {

        limpiarPantalla();

        cout << "====================================\n";
        cout << "          THE MIND (Nivel " << nivel << ")\n";
        cout << "====================================\n\n";

        cout << "Vidas: " << vidas << " | Estrellas: " << estrellas << "\n\n";

        cout << "Pila central: ";
        if (pilaCentral.empty()) {
            cout << "(vacia)";
        } else {
            for (int v : pilaCentral) {
                cout << v << " ";
            }
        }
        cout << "\n\n";

        // DERROTA
        if (vidas <= 0) {
            cout << "GAME OVER\n";
            return;
        }

        // VICTORIA DE RONDA
        bool todosSinCartas = true;
        for (auto& j : jugadores) {
            if (j.cantidadCartas() > 0) {
                todosSinCartas = false;
                break;
            }
        }

        if (todosSinCartas) {
            cout << "\n*** NIVEL SUPERADO ***\n";

            if (nivel == 2 || nivel == 5 || nivel == 8) {
                estrellas++;
                cout << "Recompensa: Ganaste una estrella ninja!\n";
            } else if (nivel == 3 || nivel == 6 || nivel == 9) {
                vidas++;
                cout << "Recompensa: Ganaste una vida!\n";
            }

            return;
        }

        cout << "------------------------------------\n";
        cout << "Acciones disponibles:\n";
        cout << "1. Jugar carta\n";
        cout << "2. Usar estrella ninja\n";
        cout << "3. Salir de la ronda\n";
        cout << "------------------------------------\n";
        cout << "Seleccion: ";

        int opcion;
        cin >> opcion;

        // ========================
        // OPCION 1: JUGAR CARTA
        // ========================
        if (opcion == 1) {

            int jugadorIndex;
            cout << "Seleccione jugador (1-" << jugadores.size() << "): ";
            cin >> jugadorIndex;
            jugadorIndex--;

            if (jugadorIndex < 0 || jugadorIndex >= jugadores.size()) {
                cout << "Jugador invalido\n";
                continue;
            }

            Jugador& j = jugadores[jugadorIndex];

            if (j.cantidadCartas() == 0) {
                cout << "Ese jugador no tiene cartas\n";
                continue;
            }

            cout << "Cartas de " << j.getNombre() << ":\n";
            j.mostrarMano();
            cout << endl;

            int indiceCarta;
            cout << "Seleccione indice de carta: ";
            cin >> indiceCarta;

            if (indiceCarta < 0 || indiceCarta >= j.cantidadCartas()) {
                cout << "Indice invalido\n";
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
                cout << "\n*** ERROR! ***\n";
                cout << "Se pierde una vida\n";
                vidas--;

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

            cout << "\nPresiona Enter para continuar...";
            cin.ignore();
            cin.get();
        }

        // ========================
        // OPCION 2: ESTRELLA
        // ========================
        else if (opcion == 2) {

            if (estrellas <= 0) {
                cout << "No tienes estrellas disponibles\n";
                continue;
            }

            cout << "\nSe propone usar una estrella ninja...\n";

            bool todosAceptan = true;

            for (auto& j : jugadores) {
                char respuesta;
                cout << j.getNombre() << ", aceptas? (s/n): ";
                cin >> respuesta;

                if (respuesta != 's' && respuesta != 'S') {
                    todosAceptan = false;
                }
            }

            if (!todosAceptan) {
                cout << "No todos aceptaron. No se usa la estrella.\n";
                continue;
            }

            estrellas--;

            cout << "\n*** ESTRELLA NINJA ACTIVADA ***\n";

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

            cout << "\nPresiona Enter para continuar...";
            cin.ignore();
            cin.get();
        }

        // ========================
        // OPCION 3: SALIR
        // ========================
        else if (opcion == 3) {
            cout << "Saliendo de la ronda...\n";
            return;
        }
    }
}
