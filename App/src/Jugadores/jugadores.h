#ifndef JUGADORES_H
#define JUGADORES_H

    #include "../Utilidades/interfazLista.h"

    int getJugadores(dsLista *pl, const int cantJugadores, const int rounds);
    void vaciarListaJugadores(dsLista *pl, const int cantJugadores);
    void mostrarJugadores(dsLista *pl);    
    void modificarPuntaje(char respuestaCorrecta, dsLista *jugadores, const int round);

#endif