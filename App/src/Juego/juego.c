#include "juego.h"
#include "../Utilidades/utilidades.h"
#include "../Utilidades/interfazLista.h"
#include "../Jugadores/jugadores.h"

int menu(void)
{
    char seleccion;
    int correcto;

    do
    {
        correcto = 0;
        system("cls");
        printf("[A] Jugar\n[B] Salir\n");
        seleccion = fgetc(stdin);
        fflush(stdin);
        seleccion = toUpper(seleccion);
        if(seleccion == 'A' || seleccion == 'B')
            correcto = 1;
    }while(!correcto);

    return (seleccion == 'A')? 1 : 0;
}

int cantidadJugadores(void)
{
    int cantidad;
    char aux[10];
    short error = 0;
    do
    {
        system("cls");
        if(error)
            printf("Por favor ingrese un numero.\n");
        error = 0;
        printf("Ingrese la cantidad de jugadores: ");
        fgets(aux, 10, stdin);
        fflush(stdin);
        limpiarCadena(aux);
        if(esNumero(aux) == 0 || strlen(aux) == 0)
            error = 1;
    }while(error);

    cantidad = atoi(aux);

    return cantidad;
}

int configurarPartida(int *rounds, int *tiempo)
{
    FILE *archivoConfig = fopen(ARCHIVO_CONFIG, "r");

    if(!archivoConfig)
        return FALLA_ARCHIVO_CONFIG;

    if (!fscanf(archivoConfig, "Rounds: %d\nTiempo: %d", rounds, tiempo))
    {
        perror("El archivo no tiene la configuracion adecuada.\n");
        fclose(archivoConfig);
        return FALLA_ARCHIVO_CONFIG;
    }

    fclose(archivoConfig);
    return OK;
}

void gui(void)
{
    int cantJugadores, error, tiempoRound, rounds;
    dsLista jugadores, preguntas;

    nuevaLista(&jugadores);
    nuevaLista(&preguntas);

    if((error = configurarPartida(&rounds, &tiempoRound)) != OK)
    {
        manejoErrores(error);
        return;
    }
    
    while (menu()) // 1 si quiere jugar, de lo contrario no se ejecuta.
    {
        // obtengo preguntas en api
        // muestro rounds y tiempo [Puede tener error]

        cantJugadores = cantidadJugadores();
        printf("La configuracion establece %d rounds de %d segundos\n", 
                rounds, tiempoRound);
        if((error = getJugadores(&jugadores, cantJugadores, rounds)) != OK)
        {
            manejoErrores(error);
            vaciarListaJugadores(&jugadores, cantJugadores);
            return;
        }
        system("cls");
        mostrarJugadores(&jugadores);
        system("pause");

        //generarInforme
        vaciarListaJugadores(&jugadores, cantJugadores);
        //vaciarListaPreguntas
    }
}
//TODO: errorEnPartida: función que imprima el error y limpie las listas.