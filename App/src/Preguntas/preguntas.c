#include "preguntas.h"


int obtenerPreguntas()
{
    tRespuesta respuesta;

    if (obtenerPreguntascURL(&respuesta) != OK)
    {
        free(respuesta.string);
        return FALLA_CURL;
    }

    // Acá proceso las preguntas
    free(respuesta.string);
    return OK;
}