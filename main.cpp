#include <iostream>
#include "Carta.h"
#include "Mazo.h"
#include "Jugador.h"

using namespace std;

int main() {
    Mazo mazo;
    Jugador jugador1("Valen");

    // Repartir 2 cartas
    jugador1.recibirCarta(mazo.repartir());
    jugador1.recibirCarta(mazo.repartir());

    // Jugar cartas
    Carta c1 = jugador1.jugarCarta();
    Carta c2 = jugador1.jugarCarta();

    cout << "Jugador jugo: " << c1.getNumero() << endl;
    cout << "Jugador jugo: " << c2.getNumero() << endl;

    return 0;
}