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
    tNodo *aux = *lista, 
          *elim;

    if(!aux)
        return;
    
    aux = (*lista)->next;
    do{
        elim = aux;
        aux  = aux->next;
        free(elim->data);
        free(elim);
    }while(aux != (*lista));

    *lista = NULL;
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
        return FALLA_MEMORIA;
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
        if(destino > origen)
            intercambio(lista, origen, destino);
        else if(origen > destino)
            intercambio(lista, destino, origen);
    }
}

void listMap(dsLista *lista, lambda func)
{
    tNodo* aux;
    if(!(*lista))
    {
        return;
    }
    aux = (*lista)->next;
    do
    {
        func(aux->data);
        aux = aux->next;
    }while(aux != (*lista)->next);

}

/******************************************************************************
* @Descripción:
* Si cmp == 1 significa que el nodo se queda.
******************************************************************************/
int listFilter(dsLista *listaDestino, dsLista *listaOrigen, const void *parametro, cmp cmp)
{
    tNodo* aux;
    
    aux = (*listaOrigen)->next;
    do
    {
        if(cmp(parametro, (const void *)aux->data) == 1)
        {
            if(agregarElemento(listaDestino, aux->data, aux->dataSize) != OK)
                return FALLA_MEMORIA;
        }
        aux = aux->next;
    }while(aux != (*listaOrigen)->next);

    return OK;
}

int contarElementos(dsLista *lista)
{
    tNodo* aux;
    int i = 0;
    if(*lista == NULL)
    {
        return 0;
    }
    aux = (*lista)->next;
    
    do
    {
        i++;
        aux = aux->next;
    }while(aux != (*lista)->next);

    return i;
}

void borrarElementoN(dsLista *lista, int elemento)
{
    tNodo *nodoBorrar;

    lista = &(*lista)->next;

    for(int i = 0; i < elemento; i++)
    {
        lista = &(*lista)->next;
    }
    nodoBorrar = *lista;
    *lista = nodoBorrar->next;
    free(nodoBorrar->data);
    free(nodoBorrar);
}

void dejarNelementos(dsLista *lista, int cantidadFinal)
{
    int cantidadElementos = contarElementos(lista), 
        elemRandom;

    for(int i = cantidadElementos - cantidadFinal; i > 0; i--)
    {
        elemRandom = rand() % i; 
        borrarElementoN(lista, elemRandom);
    }
}
