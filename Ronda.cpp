#include "Ronda.h"
#include <iostream>

using namespace std;

Ronda::Ronda(int nivel) {
    this->nivel = nivel;
}

vector<int> Ronda::getPila() const {
    return pilaCentral;
}