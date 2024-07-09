#include "juego.h"
#include <stdio.h>

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
    char aux[2];
    short error = 0;
    do
    {
        system("cls");
        if(error)
            printf("Error en el ingreso.\n");
        error = 0;
        printf("Seleccionar dificultad\n\t[1] Facil\n\t[2] Medio\n\t[3] Dificil\n");
        printf("Ingrese un valor: ");
        fgets(aux,2,stdin);
        fflush(stdin);
        if(aux[0] < '1' || aux[0] > '3')
            error = 1;
    }while(error);

    dificultad = atoi(aux);

    return dificultad;
}

int manejoArchivoConfig(int *rounds, int *tiempo)
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

    if(*rounds < 4 || *rounds > 7)
    {
        perror("La cantidad de rounds excede los limites\n");
        return FALLA_ARCHIVO_CONFIG;
    }

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

void configurarPartida(int *rounds, int *tiempo, dsLista *preguntas)
{
    int error;
    
    if((error = manejoArchivoConfig(rounds, tiempo)) != OK ||(error = obtenerPreguntas(preguntas)) != OK)
    {
        manejoErrores(error);
        printf("Lamentamos el inconveniente\n");
        system("pause");
        exit(EXIT_FAILURE);
    }
}

int seccionPreguntas(dsLista *preguntas, dsLista *jugadores, const int rounds, const int nJugadores, const int tiempo, char *respuestasCorrectas)
{
    int i, j;
    tPregunta *preguntaActual;
    tJugador *jugadorActual;

    crearRespuestasCorrectas(respuestasCorrectas, rounds);

    for(i = 0; i < nJugadores; i++)
    {
        system("cls");
        jugadores = &(*jugadores)->next;
        jugadorActual = (tJugador *)(*jugadores)->data;
        printf("Turno de: %s\n", jugadorActual->nombre);
        system("pause");
        for(j = 0; j < rounds; j++)
        {
            system("cls");
            preguntas = &(*preguntas)->next;
            preguntaActual = (tPregunta *)(*preguntas)->data;
            if(mostrarPreguntaConTiempo(preguntaActual,jugadorActual,tiempo, j, respuestasCorrectas[j]) != OK)
                return FALLA_TEMPORIZADOR;
            
            system("pause"); 
        }
    }

    for (i = 0; i < rounds; i++)
    {
        modificarPuntaje(respuestasCorrectas[i], jugadores, i, nJugadores);
    }
    
    system("pause");
    return OK;
}

void gui(void)
{
    char respuestasCorrectas[8];
    int cantJugadores, error, tiempoRound, rounds, dificultad;
    dsLista jugadores, preguntasActuales, preguntas;
 
    nuevaLista(&preguntas); // Tiene todas las preguntas
    configurarPartida(&rounds, &tiempoRound, &preguntas); 

    nuevaLista(&jugadores);
    nuevaLista(&preguntasActuales); // preguntas filtradas por dificultad y rounds  

    while (menu()) // 1 si quiere jugar, de lo contrario no se ejecuta.
    {
        dificultad = seleccionDificultad();
        cantJugadores = cantidadJugadores();
        if((error = getJugadores(&jugadores, cantJugadores, rounds)) != OK)
            gestionErrores(error, cantJugadores, &jugadores, &preguntas, &preguntasActuales);

        system("cls");
        mostrarJugadores(&jugadores);
        system("pause");
        // Obtengo preguntas específicas para esta partida, creo una segunda lista desde la original.
        if((error = preguntasPartida(&preguntas, &preguntasActuales, rounds, dificultad)) != OK)
            gestionErrores(error, cantJugadores, &jugadores, &preguntas, &preguntasActuales);
        
        // Empieza el juego.
        if((error = seccionPreguntas(&preguntasActuales,&jugadores,rounds, cantJugadores, tiempoRound , respuestasCorrectas)) != OK)
            gestionErrores(error, cantJugadores, &jugadores, &preguntas, &preguntasActuales);

        if((error = crearInforme(cantJugadores, rounds, &jugadores, &preguntasActuales, respuestasCorrectas)) != OK)
            gestionErrores(error, cantJugadores, &jugadores, &preguntas, &preguntasActuales);

        system("pause");
        vaciarListaJugadores(&jugadores, cantJugadores);
        vaciarLista(&preguntasActuales);
    }
    
    vaciarLista(&preguntas);
    printf("Gracias por participar!\n");
    system("pause");
}
