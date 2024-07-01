#include <windows.h>
#include <conio.h>

#include "preguntas.h"

char *copiarString(char *destino, char *origen)
{

    while (*origen != '"')
    {
        *destino = *origen;
        destino++;
        origen++;
    }
    *(destino + 1) = '\0';

    return (origen + 1);
}

int parseoPreguntas(dsLista *preguntas, char *jsonPreguntas)
{
    char dificultad;
    tPregunta aux;

    while((jsonPreguntas = strchr(jsonPreguntas, '{')) != NULL)
    {
        jsonPreguntas = copiarString(aux.pregunta, strchr(jsonPreguntas, ':') + 2);
        jsonPreguntas = copiarString(aux.resp_correcta, strchr(jsonPreguntas, ':') + 2);
        jsonPreguntas = copiarString(aux.opcion_1, strchr(jsonPreguntas, ':') + 2);
        jsonPreguntas = copiarString(aux.opcion_2, strchr(jsonPreguntas, ':') + 2);
        jsonPreguntas = copiarString(aux.opcion_3, strchr(jsonPreguntas, ':') + 2);
        jsonPreguntas = strchr(jsonPreguntas, ':') + 1;
        dificultad = *jsonPreguntas;
        aux.nivel = atoi(&dificultad);
        jsonPreguntas = copiarString(aux.id, strchr(jsonPreguntas, ':') + 2);

        if(agregarElemento(preguntas, (void*)&aux, sizeof(tPregunta)) != OK)
            return FALLA_MEMORIA;
        
    }

    return OK;
}

int obtenerPreguntas(dsLista *preguntas)
{
    tRespuesta respuesta;

    if (obtenerPreguntascURL(&respuesta) != OK)
    {
        free(respuesta.string);
        return FALLA_CURL;
    }

    if (parseoPreguntas(preguntas, respuesta.string) != OK)
    {
        vaciarLista(preguntas);
        free(respuesta.string);
        return FALLA_MEMORIA;
    }

    free(respuesta.string);
    return OK;
}

int filtrarPreguntas(const void *parametro, const void *pregunta)
{
    int *dificultad = (int *)parametro;
    tPregunta *dificultadPregunta = (tPregunta *)pregunta;

    return *dificultad == dificultadPregunta->nivel;
}

int preguntasPartida(dsLista *preguntas, dsLista *partidaActual, int rounds, int dificultad)
{
    if(listFilter(partidaActual, preguntas, (void *)&dificultad, filtrarPreguntas) != OK)
        return FALLA_MEMORIA;
    dejarNelementos(partidaActual, rounds);
    return OK;
}

void mostrarPregunta(tPregunta *pregunta, const char respuestaCorrecta)
{
    printf("%s", pregunta->pregunta);
    switch (respuestaCorrecta)
    {
    case 'A':
        printf("[A] %s\n[B] %s\n[C] %s\n[D] %s\n", pregunta->resp_correcta, 
                pregunta->opcion_3, pregunta->opcion_2, pregunta->opcion_1);
        break;
    case 'B':
        printf("[A] %s\n[B] %s\n[C] %s\n[D] %s\n", pregunta->opcion_2, 
            pregunta->resp_correcta, pregunta->opcion_3, pregunta->opcion_1);
        break;
    case 'C':
        printf("[A] %s\n[B] %s\n[C] %s\n[D] %s\n", pregunta->opcion_3, 
            pregunta->opcion_1, pregunta->resp_correcta, pregunta->opcion_2);
        break;
    case 'D':
        printf("[A] %s\n[B] %s\n[C] %s\n[D] %s\n", pregunta->opcion_1, 
            pregunta->opcion_2, pregunta->opcion_3, pregunta->resp_correcta);
        break;
    }
}

void crearRespuestasCorrectas(char *vec, const int rounds)
{
    int numRandom;
    for(int i = rounds; i > 0; i--)
    {
        numRandom = rand() % 4;
        switch (numRandom)
        {
        case 0:
            vec[i] = 'A';
            break;
        case 1:
            vec[i] = 'B';
            break;
        case 2:
            vec[i] = 'C';
            break;
        case 3:
            vec[i] = 'D';
            break;
        }
    }
    vec[rounds] = '\0';
}

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    printf("\nTiempo agotado. Pasando a la siguiente pregunta.\n");
    PostQuitMessage(0); // Finaliza el bucle de mensajes
}

int mostrarPreguntaConTiempo(tPregunta *pregunta,tJugador *jugador,  int tiempoLimite, int round, const char rta) 
{
    MSG msg;
    UINT_PTR timerId = SetTimer(NULL, 0, tiempoLimite * 1000, TimerProc); // Configura el temporizador

    char respuesta;
    int tiempoRestante = tiempoLimite;
    DWORD startTime = GetTickCount();
    DWORD currentTime;
    int tiempoTranscurrido;

    if (timerId == 0) {
        fprintf(stderr, "Error al configurar el temporizador.\n");
        return FALLA_TEMPORIZADOR;
    }

    mostrarPregunta(pregunta,rta);

    while (1) {
        if (_kbhit()) {
            respuesta = _getch();
            currentTime = GetTickCount();
            if (respuesta == 'A' || respuesta == 'B' || respuesta == 'C' || respuesta == 'D') {
                KillTimer(NULL, timerId); // Cancela el temporizador si se responde a tiempo
                tiempoTranscurrido = (currentTime - startTime) / 1000;
                printf("\nRespuesta recibida: %c en %d segundos\n", respuesta, tiempoTranscurrido);
                jugador->respuestas[round] = respuesta;
                jugador->tiempoDeRespuesta[round] = tiempoTranscurrido;
                
                return OK;
            } else {
                tiempoRestante = tiempoLimite - (currentTime - startTime) / 1000;
                if (tiempoRestante <= 0) {
                    break;
                }
                printf("\nError al ingresar. Por favor ingrese A/B/C/D. Le quedan %d segundos: ", tiempoRestante);
            }
        }

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_TIMER) {
                break;
            }
        }

        currentTime = GetTickCount();
        tiempoRestante = tiempoLimite - (currentTime - startTime) / 1000;
        if (tiempoRestante <= 0) {
            break;
        }
    }

    KillTimer(NULL, timerId); // Cancela el temporizador
    jugador->respuestas[round] = '-';
    jugador->tiempoDeRespuesta[round] = -1;
    return OK;
}