#ifndef LISTA_H
#define LISTA_H

    typedef struct _nodo 
    {
        void *data;
        unsigned dataSize;
        struct _nodo *next;
    }tNodo;

    typedef tNodo *dsLista;
    typedef int  (*cmp)(const void *, const void *);
    typedef void (*lambda)(void *);
    typedef void (*reduceFunc)(void *container, void *); 

    // Funciones generales
    void nuevaLista(dsLista *lista);
    void vaciarLista(dsLista *lista);
    int  listaVacia(dsLista *lista);
    int  agregarElemento(dsLista *lista, void *data, unsigned dataSize);

    // Funciones particulares para la app
    void algoritmoFisherYates(dsLista *lista, unsigned ce);
    void listMap(dsLista *lista, lambda func);
    int  listFilter(dsLista *listaDestino, dsLista *listaOrigen, const void *parametro, cmp cmp);
    void listReduce(dsLista *lista, void* container, reduceFunc func); 
    void dejarNelementos(dsLista *lista, int cantidadFinal);

#endif