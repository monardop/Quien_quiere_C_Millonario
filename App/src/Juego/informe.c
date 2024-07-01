#include "juego.h"

//sumar puntajes.
//leer puntajeJugador que cargue el vector puntajes
// definir ganador y mostrar en pantalla.
// crear el .txt


void sumarPuntaje(const tJugador *jugador, int *vecPuntajes, const int rounds, const int nroJugador)
{
    int resultado = 0; 
    for (int i = 0; i < rounds; i++)
    {
        resultado += jugador->puntajeFinal[i];
    }
    vecPuntajes[nroJugador] = resultado;
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





int crearInforme(const int cantJugadores, const int rounds, dsLista *jugadores, dsLista *preguntas)
{
    int *puntajesFinales;
    char nombreArchivo[200];

    crearNombreArchivo(nombreArchivo);
    if((puntajesFinales = (int *)malloc(sizeof(int) * cantJugadores)) == NULL)
        return FALLA_MEMORIA;



    free(puntajesFinales);



    return OK;
}