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
        if(esNumero(aux) == 0 || strlen(aux) == 0)
            error = 1;
    }while(error);

    cantidad = atoi(aux);

    return cantidad;
}

int seleccionDificultad(void)
{
    int dificultad;
    char aux;
    short error = 0;
    do
    {
        system("cls");
        if(error)
            printf("Error en el ingreso.\n");
        error = 0;
        printf("Seleccionar dificultad\n\t[1] Facil\n\t[2] Medio\n\t[3] Dificil\n");
        printf("Ingrese un valor: ");
        aux = getc(stdin);
        fflush(stdin);
        if(aux < '1' || aux > '3')
            error = 1;
    }while(error);

    dificultad = atoi(&aux);

    return dificultad;
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

    printf("La configuracion establece %d rounds de %d segundos\n", 
                *rounds, *tiempo);
    return OK;
}

void gestionErrores(int error, int nroJugadores, dsLista *jugadores, dsLista *preguntas, dsLista *filtradas)
{
    manejoErrores(error);
    vaciarListaJugadores(jugadores, nroJugadores);
    vaciarLista(preguntas);
    vaciarLista(filtradas);

    printf("Lamentamos el inconveniente\n");
    system("pause");
    exit(EXIT_FAILURE);
}

void gui(void)
{
    int cantJugadores, error, tiempoRound, rounds, dificultad;
    dsLista jugadores, preguntasPartida, preguntas;

    if((error = configurarPartida(&rounds, &tiempoRound)) != OK)
    {
        manejoErrores(error);
        return;
    }
    
    nuevaLista(&jugadores);
    nuevaLista(&preguntas); // Tiene todas las preguntas
    nuevaLista(&preguntasPartida); // preguntas filtradas por dificultad y rounds
    
    //obtenerPreguntas();

    while (menu()) // 1 si quiere jugar, de lo contrario no se ejecuta.
    {

        dificultad = seleccionDificultad();
        cantJugadores = cantidadJugadores();
        if((error = getJugadores(&jugadores, cantJugadores, rounds)) != OK)
            gestionErrores(error, cantJugadores, &jugadores, &preguntas, &preguntasPartida);

        system("cls");
        mostrarJugadores(&jugadores);
        system("pause");


        //generarInforme
        vaciarListaJugadores(&jugadores, cantJugadores);
        vaciarLista(&preguntasPartida);
    }
    vaciarLista(&preguntas);
    printf("Gracias por participar!\n");
    system("pause");
}
//TODO: errorEnPartida: función que imprima el error y limpie las listas.