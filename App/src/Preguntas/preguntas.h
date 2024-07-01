#ifndef PREGUNTAS_H
#define PREGUNTAS_H

    #include "../Utilidades/utilidades.h"
    #include "../Utilidades/interfazLista.h"


    int  obtenerPreguntascURL(tRespuesta *respuesta);
    int  obtenerPreguntas(dsLista *preguntas);
    int  preguntasPartida(dsLista *preguntas, dsLista *partidaActual, int rounds, int dificultad);
    void crearRespuestasCorrectas(char *vec, const int rounds);
    int  mostrarPreguntaConTiempo(tPregunta *pregunta, tJugador *jugador,  
                                     int tiempoLimite, int round, const char rta); 
    

#endif
