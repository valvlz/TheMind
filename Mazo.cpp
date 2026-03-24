#include "Mazo.h"
#include <algorithm> //para std::shuffle
#include <random> //para std::default_random_engine
#include <stdexcept> //para std::runtime_error

Mazo::Mazo() {
    for (int i = 1; i <= 100; i++) {
        cartas.push_back(Carta(i));
    }
    barajar();
}

Carta Mazo::repartir() {
    if (estaVacio()) {
    throw std::runtime_error("El mazo está vacío"); //evitar repartir cartas si el mazo se ha quedado sin cartas
    }
    Carta c = cartas.back();
    cartas.pop_back();
    return c;
}

void Mazo::barajar() {
    std::random_device rd; //semilla para el generador de números aleatorios
    std::mt19937 g(rd()); //generador de números aleatorios
    std::shuffle(cartas.begin(), cartas.end(), g); //mezcla las cartas usando el generador
}

