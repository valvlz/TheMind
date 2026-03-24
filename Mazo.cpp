#include "Mazo.h"

Mazo::Mazo() {
    for (int i = 1; i <= 100; i++) {
        cartas.push_back(Carta(i));
    }
}

Carta Mazo::repartir() {
    Carta c = cartas.back();
    cartas.pop_back();
    return c;
}