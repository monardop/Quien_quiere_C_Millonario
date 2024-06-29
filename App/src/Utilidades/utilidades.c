#include "utilidades.h"

int toUpper(const char c)
{
    if(c >= 'a' && c <= 'z')
    {
        return c - 32;
    }

    return c;
}

int esNumero(char *cad)
{
    while(*cad)
    {

        if(*cad < '0' || *cad > '9')
            return 0;
        cad++;
    }
    return 1;
}

void limpiarCadena(char *cad)
{
    while(*cad && *cad != '\n') cad++;
    *cad = '\0';
}
/******************************************************************************
* @Descripción:
* Función para gestionar los errores que puede escalar con base a las 
* necesidades que vaya teniendo. Cada uno de los errores posibles será una 
* macro para ser más específico en el mensaje de salida.
******************************************************************************/
void manejoErrores(const int error)
{
    switch (error)
    {
        case ERROR_ARCHIVO_CONFIG:
            printf("Hubo un error en la lectura de la configuracion.\n");
            break;
        case ERROR_MEMORIA:
            printf("Hubo un error en la ejecucion por falta de memoria.\n");
            break;
        case ERROR_API:
            printf("Error en la obtncion de preguntas.\n");
            break;
        case ERROR_ARCHIVO_RESULTADO:
            printf("Hubo un problema al crear el informe de resultados.\n");
            break;
    }
}
