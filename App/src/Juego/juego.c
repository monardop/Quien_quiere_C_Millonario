#include "juego.h"

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
        if(esNumero(aux) == 0 || strLength(aux) == 0)
            error = 1;
    }while(error);

    cantidad = atoi(aux);

    return cantidad;
}

int configurarPartida(int *rounds, int *tiempo)
{
    FILE *archivoConfig = fopen(ARCHIVO_CONFIG, "r");

    if(!archivoConfig)
        return ERROR_ARCHIVO_CONFIG;

    if (!fscanf(archivoConfig, "Rounds: %d\nTiempo: %d", rounds, tiempo))
    {
        perror("El archivo no tiene la configuracion adecuada.\n");
        fclose(archivoConfig);
        return ERROR_ARCHIVO_CONFIG;
    }

    fclose(archivoConfig);
    return OK;
}

void gui(void)
{
    int cantJugadores, error, tiempoRound, rounds;

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
        printf("Se seleccionaron %d jugadores\n", cantJugadores);
        system("pause");
        // cargo los jugadores en lista de jugadores [Puede tener error]



    }

    //limpiar la lista de Jugadores y preguntas.
}
