#ifndef MAZO_H
#define MAZO_H

#include <vector>
#include "Carta.h"

using namespace std;

class Mazo {
private:
    vector<Carta> cartas;

public:
    Mazo();
    Carta repartir();

    void barajar();      //Para mezclar las cartas
    bool estaVacio() const; //Para verificar si el mazo se ha quedado sin cartas
};

#endif