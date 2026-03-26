#ifndef RONDA_H
#define RONDA_H

#include <vector>
#include "Jugador.h"

using namespace std;

class Ronda {
private:
    int nivel;
    vector<int> pilaCentral;

public:
    Ronda(int nivel);

    void jugar(vector<Jugador>& jugadores, int& vidas, int& estrellas);

    vector<int> getPila() const;
};

#endif