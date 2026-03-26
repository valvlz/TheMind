## The Mind - Proyecto en C++

# Descripción

Este proyecto es una simulación en consola del juego de cartas "The Mind", desarrollada en C++.
La idea del juego es que dos jugadores cooperen para jugar sus cartas en orden ascendente, sin comunicarse directamente entre ellos.

El programa permite jugar varias rondas, manejar vidas y estrellas ninja, y también guardar o cargar la partida.

Cómo funciona el juego
Cada nivel representa una ronda.
En cada ronda, a cada jugador se le reparten cartas según el nivel.
Los jugadores deben jugar las cartas en orden ascendente.
Si se juega una carta incorrecta (cuando alguien tenía una menor), se pierde una vida.
Se pueden usar estrellas ninja para descartar la carta más baja de cada jugador (solo si todos aceptan).
En ciertos niveles se ganan recompensas:
    Nivel 2, 5, 8: estrella ninja
    Nivel 3, 6, 9: vida

# Estructura del proyecto

El código está organizado en varias clases:

    Juego: controla el flujo general del programa
    Ronda: maneja la lógica de cada nivel
    Jugador: representa a cada jugador y sus cartas
    Mazo: contiene y reparte las cartas
    Carta: representa una carta individual

Cada clase está separada en archivos .h y .cpp.

# Compilación
    En Windows (MSYS2 o MinGW)
        g++ main.cpp Juego.cpp Jugador.cpp Mazo.cpp Carta.cpp Ronda.cpp -o juego.exe
        ./juego.exe
    En Linux
        g++ main.cpp Juego.cpp Jugador.cpp Mazo.cpp Carta.cpp Ronda.cpp -o juego
        ./juego

# Guardar y cargar partida

El juego permite guardar la partida en un archivo llamado partida.txt.
También se puede cargar una partida previamente guardada desde el menú inicial.

# Notas
    El juego está diseñado para 2 jugadores.
    Todo se juega desde una sola consola.
    Las decisiones se toman manualmente (no hay turnos automáticos).

# Autores

    Juan Pablo Quintero Goez
    Valentina Velez

# Comentario final

    Este proyecto fue desarrollado como parte de un curso de programación en C++, con el objetivo de aplicar conceptos de programación orientada a objetos y estructuración de código en múltiples archivos.

Juego basado en el reglamento oficial: https://lajuganera.cat/wp-content/uploads/2020/08/Reglament-the-mind.pdf

## Diagrama UML
![Diagrama UML](docs/uml.png)
Mejora
![alt text](uml.png)