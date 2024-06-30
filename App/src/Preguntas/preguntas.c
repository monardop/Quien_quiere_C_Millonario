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