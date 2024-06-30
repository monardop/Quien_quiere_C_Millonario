#include "preguntas.h"

char *copiarString(char *destino, char *origen)
{

    while (*origen != '"')
    {
        *destino = *origen;
        destino++;
        origen++;
    }
    *(destino + 1) = '\0';

    return (origen + 1);
}

int parseoPreguntas(dsLista *preguntas, char *jsonPreguntas)
{
    char dificultad;
    tPregunta aux;

    while((jsonPreguntas = strchr(jsonPreguntas, '{')) != NULL)
    {
        jsonPreguntas = copiarString(aux.pregunta, strchr(jsonPreguntas, ':') + 2);
        jsonPreguntas = copiarString(aux.resp_correcta, strchr(jsonPreguntas, ':') + 2);
        jsonPreguntas = copiarString(aux.opcion_1, strchr(jsonPreguntas, ':') + 2);
        jsonPreguntas = copiarString(aux.opcion_2, strchr(jsonPreguntas, ':') + 2);
        jsonPreguntas = copiarString(aux.opcion_3, strchr(jsonPreguntas, ':') + 2);
        jsonPreguntas = strchr(jsonPreguntas, ':') + 1;
        dificultad = *jsonPreguntas;
        aux.nivel = atoi(&dificultad);
        jsonPreguntas = copiarString(aux.id, strchr(jsonPreguntas, ':') + 2);

        if(agregarElemento(preguntas, (void*)&aux, sizeof(tPregunta)) != OK)
            return FALLA_MEMORIA;
        
    }

    return OK;
}

int obtenerPreguntas(dsLista *preguntas)
{
    tRespuesta respuesta;

    if (obtenerPreguntascURL(&respuesta) != OK)
    {
        free(respuesta.string);
        return FALLA_CURL;
    }

    if (parseoPreguntas(preguntas, respuesta.string) != OK)
    {
        vaciarLista(preguntas);
        free(respuesta.string);
        return FALLA_MEMORIA;
    }

    free(respuesta.string);
    return OK;
}

int filtrarPreguntas(const void *parametro, const void *pregunta)
{
    int *dificultad = (int *)parametro;
    tPregunta *dificultadPregunta = (tPregunta *)pregunta;

    return *dificultad == dificultadPregunta->nivel;
}

int preguntasPartida(dsLista *preguntas, dsLista *partidaActual, int rounds, int dificultad)
{
    if(listFilter(partidaActual, preguntas, (void *)&dificultad, filtrarPreguntas) != OK)
        return FALLA_MEMORIA;
    dejarNelementos(partidaActual, rounds);
    return OK;
}

void mostrarPregunta(dsLista *listaPreguntas, const char respuestaCorrecta)
{
    tPregunta *pregunta = (tPregunta *)(*listaPreguntas)->data;
    printf("%s", pregunta->pregunta);
    switch (respuestaCorrecta)
    {
    case 'A':
        printf("[A] %s\n[B] %s\n[C] %s\n[D] %s\n", pregunta->resp_correcta, 
                pregunta->opcion_3, pregunta->opcion_2, pregunta->opcion_1);
        break;
    case 'B':
        printf("[A] %s\n[B] %s\n[C] %s\n[D] %s\n", pregunta->opcion_2, 
            pregunta->resp_correcta, pregunta->opcion_3, pregunta->opcion_1);
        break;
    case 'C':
        printf("[A] %s\n[B] %s\n[C] %s\n[D] %s\n", pregunta->opcion_3, 
            pregunta->opcion_1, pregunta->resp_correcta, pregunta->opcion_2);
        break;
    case 'D':
        printf("[A] %s\n[B] %s\n[C] %s\n[D] %s\n", pregunta->opcion_1, 
            pregunta->opcion_2, pregunta->opcion_3, pregunta->resp_correcta);
        break;
    }
}

