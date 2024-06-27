#include "interfazLista.h"
#include "utilidades.h"


void nuevaLista(dsLista *lista)
{
    *lista = NULL;
}

int listaVacia(dsLista *lista)
{
    return *lista == NULL;
}

void vaciarLista(dsLista *lista)
{
    tNodo *delNodo;

    while(*lista)
    {
        delNodo = *lista;
        *lista = delNodo->next;
        free(delNodo->data);
        free(delNodo);
    }
}

/******************************************************************************
* @Descripción:
* Utilizaré una lista circular. 
* @return
* OK o ERROR_MEMORIA
******************************************************************************/
int agregarElemento(dsLista *lista, void *data, unsigned dataSize)
{
    tNodo *nuevo;

    if((nuevo= (tNodo*)malloc(sizeof(tNodo))) == NULL|| 
       (nuevo->data = malloc(dataSize))       == NULL  )
    {
        free(nuevo);
        return ERROR_MEMORIA;
    }
    memcpy(nuevo->data, data, dataSize);
    nuevo->dataSize = dataSize;

    if (*lista == NULL)
    {
        nuevo->next = nuevo;
    }
    else
    {
        nuevo->next = (*lista)->next;
        (*lista)->next = nuevo;
    }

    *lista = nuevo;

    return OK;
}

/******************************************************************************
* @Descripción:
* Esta función complementa al algoritmo siguiente. 
* Intercambia la info de dos nodos.
******************************************************************************/
void intercambio(dsLista *lista, int origen, int destino)
{
    void *datoAux;
    tNodo *auxiliar;

    while(origen > 0)
    {
        lista = &(*lista)->next;
        origen--;
        destino--;
    }
    auxiliar = *lista;
    while(destino > 0)
    {
        lista = &(*lista)->next;
        destino--;
    }
    datoAux = (*lista)->data;
    (*lista)->data = auxiliar->data;
    auxiliar->data = datoAux;
    
}

/******************************************************************************
* @Descripción:
* Algoritmo existente. Baraja los elementos de una lista. 
******************************************************************************/
void algoritmoFisherYates(dsLista *lista, unsigned ce)
{
    int origen, destino;

    for(origen = ce - 1; origen > 1; origen--)
    {
        destino = rand() % origen;
        intercambio(lista, origen, destino);
    }
}

void listMap(dsLista *lista, lambda func);

void listFilter(dsLista *lista, cmp cmp);

void listReduce(dsLista *lista, void* container); 

void imprimirLista(dsLista *lista, lambda print);