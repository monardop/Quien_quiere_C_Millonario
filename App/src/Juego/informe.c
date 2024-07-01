#include "juego.h"
#define  BARRA  "-----------------------------------------------------------------------------------------------------------------------------------------------" 

void sumarPuntaje(const tJugador *jugador, int *vecPuntajes, const int rounds)
{
    int resultado = 0; 
    for (int i = 0; i < rounds; i++)
    {
        resultado += jugador->puntajeFinal[i];
    }
    *vecPuntajes = resultado;
}

void obtenerNombreArchivo(char *nombreArchivo)
{
    time_t rawtime;
    struct tm *ahora;

    // Obtener el tiempo actual del sistema
    time(&rawtime);
    // Convertir a estructura tm local
    ahora = localtime(&rawtime);

    // Formatear el tiempo en el nombre del archivo
    strftime(nombreArchivo, 150, "Informe_%Y-%m-%d-%H-%M.txt", ahora);
}

void crearNombreArchivo(char* nombreArchivo)
{
    char informe[150];
    obtenerNombreArchivo(informe);
    strcpy(nombreArchivo, ARCHIVO_INFORME);
    strcat(nombreArchivo,informe);
}

void cargarVectorPuntajes(dsLista *jugadores, int *vecPuntaje, const int rounds)
{
    tJugador *jugador;
    tNodo *aux = (*jugadores)->next;
    int i = 0;

    do
    {
        jugador = (tJugador *)aux->data;
        sumarPuntaje(jugador, &vecPuntaje[i], rounds);
        aux = aux->next;
        i++;
    } while (aux != (*jugadores)->next);
    
}

int buscarMayor(const int *vec, const int ce)
{
    int mayor = vec[0],
        i;

    for (i = 0; i < ce; i++)
    {
        if (vec[i] > mayor)
        {
            mayor = vec[i];
        }
    }
    
    return mayor;
}

int declararGanadores(const int *vec, dsLista *jugadores, char *nombreArchivo, const int cantJugadores)
{
    int mayor, i = 0;
    tJugador *jugador;
    tNodo *aux;
    FILE* archivoInforme;

    mayor = buscarMayor(vec,cantJugadores);

    if((archivoInforme = fopen(nombreArchivo, "at")) == NULL)
        return FALLA_ARCHIVO_RESULTADO;
    fprintf(archivoInforme, "\n\nGanadores de la partida:\n");

    aux = (*jugadores)->next;
    do
    {
        jugador = (tJugador *)aux->data;
        if(vec[i] == mayor)
        {
            fprintf(archivoInforme, "%30s con %d puntos.\n", jugador->nombre, mayor);
            fprintf(stdout, "\t%20s con %d puntos.\n", jugador->nombre, mayor);
        }

        aux = aux->next;
        i++;
    } while ((*jugadores)->next != aux);
    
    fclose(archivoInforme);

    return OK;
}

int generarInforme(char *nombreInforme, int *resultados, dsLista *jugadores, dsLista *preguntas, const char *respuestas)
{
    FILE *archivoInforme;
    tNodo *aux;
    tPregunta *pregunta;
    tJugador *jugador;
    int i;

    if((archivoInforme = fopen(nombreInforme, "w")) == NULL)
        return FALLA_ARCHIVO_RESULTADO;
    
    aux = (*preguntas)->next;
    i = 0;
    do
    {
        pregunta = (tPregunta *)aux->data;
        fprintf(archivoInforme, "%d ", i+1);
        mostrarPregunta(pregunta, respuestas[i], archivoInforme);
        fprintf(archivoInforme, "Respuesta correcta: %c", respuestas[i]);
        fprintf(archivoInforme, "\n\n");
        aux = aux->next;
        i++;
    } while (aux != (*preguntas)->next);
    
    fprintf(archivoInforme, "\n\n");
    fprintf(archivoInforme, "%s\n", BARRA);
    fprintf(archivoInforme, "%30s|", "Jugador");
    for (int j = 0; j < i; j++)
    {
        fprintf(archivoInforme, "  Pregunta %d: [%c] |", j+1 , respuestas[j]);
    }
    fprintf(archivoInforme, "Puntaje Final   |\n");
    fprintf(archivoInforme, "%s\n", BARRA);
    aux = (*jugadores)->next;
    do
    {
        jugador = (tJugador *)aux->data;
        fprintf(archivoInforme, "%30s|", jugador->nombre);
        for (int j = 0; j < i; j++)
        {
            fprintf(archivoInforme, " [%c][%2ds][%+dptos] |", jugador->respuestas[j],
                    jugador->tiempoDeRespuesta[j], jugador->puntajeFinal[j]);
        }
        fprintf(archivoInforme, "   [%+04dptos]   |\n", *resultados);
        resultados++;
        aux = aux->next;
    } while (aux != (*jugadores)->next);
    fprintf(archivoInforme, "%s\n", BARRA);

    fclose(archivoInforme);

    return OK;
}

int crearInforme(const int cantJugadores, const int rounds, dsLista *jugadores, dsLista *preguntas, const char *respuestas)
{
    int *puntajesFinales;
    char nombreArchivo[200];

    crearNombreArchivo(nombreArchivo);
    if((puntajesFinales = (int *)malloc(sizeof(int) * cantJugadores)) == NULL)
        return FALLA_MEMORIA;

    cargarVectorPuntajes(jugadores, puntajesFinales, rounds);

    if(generarInforme(nombreArchivo,puntajesFinales,jugadores,preguntas, respuestas) != OK)
    {
        free(puntajesFinales);
        return FALLA_ARCHIVO_RESULTADO;
    }

    if(declararGanadores(puntajesFinales,jugadores,nombreArchivo,cantJugadores) != OK)
    {
        free(puntajesFinales);
        return FALLA_ARCHIVO_RESULTADO;
    }

    free(puntajesFinales);

    return OK;
}