#include "jugadores.h"
#include "../Utilidades/utilidades.h"

int getJugadores(dsLista *pl, const int cantJugadores, const int rounds)
{
    for(int i = 0; i < cantJugadores; i++)
    {
        tJugador nuevo;
        printf("Nombre del jugador %d: ", i + 1);
        fgets(nuevo.nombre, 150, stdin);
        fflush(stdin);
        limpiarCadena(nuevo.nombre);
        if(strlen(nuevo.nombre) == 0) // 
        {
            printf("Error en el ingreso, intente otra vez.\n");
            i--;
        }else
        {
            nuevo.respuestas = (char *)malloc(rounds);
            nuevo.tiempoDeRespuesta = (int *)malloc(rounds * sizeof(int));
            if(nuevo.respuestas == NULL || nuevo.tiempoDeRespuesta == NULL)
                return ERROR_MEMORIA;
            if(agregarElemento(pl, &nuevo, sizeof(tJugador)) != OK)
                return ERROR_MEMORIA;
        } 
    }   

    algoritmoFisherYates(pl, cantJugadores);

    return OK;
}

/******************************************************************************
* @Descripción:
* Los jugadores tienen 2 vectores dinámicos, por lo que antes de vaciar la
* lista de jugadores debo liberar la memoria de cada jugador. Una vez 
* realizado, vacío la lista como cualquier otra. 
******************************************************************************/
void liberarJugador(void *jugador)
{
    tJugador *actual = (tJugador *)jugador;
    
    free(actual->respuestas);
    free(actual->tiempoDeRespuesta);
}

void vaciarListaJugadores(dsLista *pl, const int cantJugadores)
{
    listMap(pl, liberarJugador);
    vaciarLista(pl);
}

void imprimirJugador(void *jugador)
{
    tJugador *actual = (tJugador *)jugador;
    printf("%s\n", actual->nombre);
}

void mostrarJugadores(dsLista *pl)
{
    listMap(pl, imprimirJugador);
}
