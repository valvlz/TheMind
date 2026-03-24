#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include "Jugador.h"
#include "Mazo.h"

using namespace std;

class Juego {
private:
    vector<Jugador> jugadores;
    Mazo mazo;
    int nivel;
    int vidas;
    int ultimaCarta;

public:
    Juego();
    void configurarJugadores();
    void repartirCartas();
    void jugarRonda();
    int getVidas() const;
    void reiniciarMazo();
    void iniciarJuego();
    bool gameOver() const;
};

#endif