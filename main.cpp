#include "Juego.h"

int main() {
    Juego juego;

    juego.iniciarJuego();

    for (int i = 0; i < 3; i++) {
        if (juego.getVidas() <= 0) {
            break;
        }

        juego.repartirCartas();
        juego.jugarRonda();
}

    return 0;
}