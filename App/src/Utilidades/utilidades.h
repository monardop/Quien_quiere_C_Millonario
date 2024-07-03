#ifndef UTILIDADES_H
#define UTILIDADES_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>

    #define FALLA_ARCHIVO_CONFIG    -5
    #define FALLA_MEMORIA           -4
    #define FALLA_CURL              -3
    #define FALLA_ARCHIVO_RESULTADO -2
    #define FALLA_TEMPORIZADOR      -1
    #define OK                       1

    #define URL_API_PREGUNTAS "https://665617e99f970b3b36c44808.mockapi.io/questions/api/questions"
    #define PASS_API_PREGUNTAS "X-Secret: 665617e99f970b3b36c44808"

    typedef struct
    {
        char  nombre[50];
        char *respuestas;
        int  *tiempoDeRespuesta,
             *puntajeFinal;
    }tJugador;

    typedef struct{
        char  *string;
        size_t size;
    }tRespuesta;

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

#endif