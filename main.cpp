#include <iostream>
#include "Carta.h"
#include "Mazo.h"

using namespace std;

int main() {
    Mazo mazo;

    Carta c1 = mazo.repartir();
    Carta c2 = mazo.repartir();

    cout << "Carta 1: " << c1.getNumero() << endl;
    cout << "Carta 2: " << c2.getNumero() << endl;

    return 0;
}