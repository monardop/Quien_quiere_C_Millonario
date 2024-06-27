#ifndef UTILIDADES_H
#define UTILIDADES_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>

    #define ERROR_ARCHIVO_CONFIG    -5
    #define ERROR_MEMORIA           -4
    #define ERROR_API               -3
    #define ERROR_ARCHIVO_RESULTADO -2
    #define OK                       1

    typedef struct
    {
        char  nombre[150];
        char *respuestas;
        int  *tiempoDeRespuesta,
              puntajeFinal;
    }tJugador;

    typedef struct
    {
        char pregunta[150],
             resp_correcta[150],
             opcion_1[150],
             opcion_2[150],
             opcion_3[150],
             id[10];
        int  nivel;

    }tPregunta;

    int  toUpper(const char c);
    int  esNumero(char *cad);
    void manejoErrores(const int error);
    void limpiarCadena(char *cad);
    int  strLength(const char *cad);

#endif