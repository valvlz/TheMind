#include "Juego.h"
#include <iostream>

using namespace std;

int main() {
    Juego juego;

    int opcion;
    cout << "1. Nueva partida\n2. Cargar partida\n";
    cin >> opcion;

    if (opcion == 2) {
        juego.cargarPartida(); // ya carga jugadores
    } else {
        juego.iniciarJuego();
    }

    int maxRondas = 3;

    for (int i = 1; i <= maxRondas; i++) {

        if (juego.getVidas() <= 0) {
            cout << "GAME OVER" << endl;
            return 0;
        }

        juego.repartirCartas();
        juego.jugarRonda();

        int opcion2;
        cout << "1. Continuar\n2. Guardar y salir\n";
        cin >> opcion2;

        if (opcion2 == 2) {
            juego.guardarPartida();
            cout << "Saliendo..." << endl;
            return 0;
        }
    }

    cout << "GANASTE!" << endl;

    return 0;
}