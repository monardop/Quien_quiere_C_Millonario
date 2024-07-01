#ifndef JUEGO_H
#define JUEGO_H

    #include "../Utilidades/utilidades.h"
    #include "../Utilidades/interfazLista.h"
    #include "../Jugadores/jugadores.h"
    #include "../Preguntas/preguntas.h"

    #define ARCHIVO_CONFIG  "config.txt"
    #define ARCHIVO_INFORME "Resultados/"

    void gui(void);
    int crearInforme(const int cantJugadores, const int rounds, dsLista *jugadores, dsLista *preguntas, const char *respuestas);

    
#endif