#include "juego.h"

int menu(void)
{
    char seleccion;
    do
    {
        printf("[A] Jugar\n[B] Salir\n");
        seleccion = fgetc(stdin);
        seleccion = toLower(seleccion);
    }while(seleccion != 'A' || seleccion != 'B');
    
    return (seleccion == 'A')? 1 : 0;
}
