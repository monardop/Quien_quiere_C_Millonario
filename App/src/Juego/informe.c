#include "juego.h"

//sumar puntajes.
//leer puntajeJugador que cargue el vector puntajes
// definir ganador y mostrar en pantalla.
// crear el .txt


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
    fprintf(archivoInforme, "Ganadores de la partida:");
    fprintf(archivoInforme, "\n");

    aux = (*jugadores)->next;
    do
    {
        jugador = (tJugador *)aux->data;
        if(vec[i] == mayor)
        {
            fprintf(archivoInforme, "%s con %d puntos.", jugador->nombre, mayor);
            fprintf(archivoInforme, "\n");
            fprintf(stdout, "\t%s con %d puntos.\n", jugador->nombre, mayor);
        }

        aux = aux->next;
        i++;
    } while ((*jugadores)->next != aux);
    
    fclose(archivoInforme);

    return OK;
}

int crearInforme(const int cantJugadores, const int rounds, dsLista *jugadores, dsLista *preguntas)
{
    int *puntajesFinales;
    char nombreArchivo[200];

    crearNombreArchivo(nombreArchivo);
    if((puntajesFinales = (int *)malloc(sizeof(int) * cantJugadores)) == NULL)
        return FALLA_MEMORIA;

    cargarVectorPuntajes(jugadores, puntajesFinales, rounds);

    if(declararGanadores(puntajesFinales,jugadores,nombreArchivo,cantJugadores) != OK)
        return FALLA_ARCHIVO_RESULTADO;

    free(puntajesFinales);



    return OK;
}