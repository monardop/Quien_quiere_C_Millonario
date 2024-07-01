#include "jugadores.h"
#include "../Utilidades/utilidades.h"

int getJugadores(dsLista *pl, const int cantJugadores, const int rounds)
{
    for(int i = 0; i < cantJugadores; i++)
    {
        tJugador nuevo;
        printf("Nombre del jugador %d: ", i + 1);
        fgets(nuevo.nombre, 50, stdin);
        fflush(stdin);
        limpiarCadena(nuevo.nombre);
        if(strlen(nuevo.nombre) == 0) // 
        {
            printf("Error en el ingreso, intente otra vez.\n");
            i--;
        }else
        {
            nuevo.respuestas = (char *)malloc(rounds + 1);
            nuevo.tiempoDeRespuesta = (int *)malloc(rounds * sizeof(int));
            nuevo.puntajeFinal = (int *)malloc(rounds * sizeof(int));
            if(nuevo.respuestas == NULL || nuevo.tiempoDeRespuesta == NULL || nuevo.puntajeFinal == NULL)
                return FALLA_MEMORIA;
            
            memset(nuevo.puntajeFinal, 0, rounds);
            memset(nuevo.tiempoDeRespuesta, 0, rounds);
            if(agregarElemento(pl, &nuevo, sizeof(tJugador)) != OK)
                return FALLA_MEMORIA;
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
    free(actual->puntajeFinal);
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

/******************************************************************************
* @Descripción:
* Recorro la lista de jugadores cargando el tiempo que tardaron. Una vez 
* cargados, busco el menor. Si hay un tiempo menor, lo guardo y asigno el 
* extra de puntos a quien corresponda.
******************************************************************************/
int menorTiempo(const int *vec, const int cantElem)
{
    int menorTiempo = 0;

    for(int i = 0; i < cantElem; i++)
    {
        if(vec[i] > -1 && vec[i] < menorTiempo)
            menorTiempo = vec[i];
    }
    
    return menorTiempo;
}

int cargarVectorTiempos(dsLista *jugadores, int *vec, const int round)
{   
    int i = 0;
    tNodo *aux = (*jugadores)->next; 
    tJugador *jugador;

    do
    {
        jugador = (tJugador *)aux->data;
        
        if(jugador->puntajeFinal[round] == 1)
            vec[i] = jugador->tiempoDeRespuesta[round];
        else    
            vec[i] = -1;
        aux = aux->next;
        i++;
    }while(aux != (*jugadores)->next);

    return i; // esto es la cantidad de jugadores.
}

void actualizarPuntaje(dsLista *jugadores, const int masRapido, const int cantidadCorrectas, const int *vec, const int round)
{
    int i = 0;
    tNodo *aux = (*jugadores)->next; 
    tJugador *jugador;

    do
    {
        jugador = (tJugador *)aux->data;
        
        if(vec[i] == masRapido)
        {
            if(cantidadCorrectas > 1)
            {
                jugador->puntajeFinal[round] += 1;
            }
            else
            {
                jugador->puntajeFinal[round] += 2;
            }
        }
            
        aux = aux->next;
        i++;
    }while(aux != (*jugadores)->next);
}

void modificarPuntaje(char respuestaCorrecta, dsLista *jugadores, const int round)
{
    int tiempos[7], // no puede haber más de 7 rounds
        masRapido, 
        elementos,
        cantidadCorrecta = 0;

    elementos = cargarVectorTiempos(jugadores, tiempos,  round);

    masRapido = menorTiempo(tiempos, elementos);
    
    for (size_t j = 0; j < elementos; j++)
    {
        if(tiempos[j] == masRapido){
            cantidadCorrecta++; // chequeo cuantos respondieron en ese tiempo
        }
    }

    if(cantidadCorrecta > 0)
        actualizarPuntaje(jugadores, masRapido, cantidadCorrecta, tiempos, round);
    
}
