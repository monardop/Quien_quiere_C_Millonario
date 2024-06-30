#ifndef PREGUNTAS_H
#define PREGUNTAS_H

    #include "../Utilidades/utilidades.h"
    #include "../Utilidades/interfazLista.h"


    int  obtenerPreguntascURL(tRespuesta *respuesta);
    int  obtenerPreguntas(dsLista *preguntas);
    int  preguntasPartida(dsLista *preguntas, dsLista *partidaActual, int rounds, int dificultad);
    void mostrarPregunta(dsLista *listaPreguntas, const char respuestaCorrecta);

#endif
