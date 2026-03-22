#include "Juego.h"

int main() {
    Juego juego;

    juego.iniciarJuego();
    juego.repartirCartas();
    juego.jugarRonda();

    return 0;
}