#ifndef UTILIDADES_H
#define UTILIDADES_H

    #define ERROR_ARCHIVO_CONFIG    -5
    #define ERROR_MEMORIA           -4
    #define ERROR_API               -3
    #define ERROR_ARCHIVO_RESULTADO -2
    #define OK                       1


    int toLower(const char c);
    int esNumero(const char *cad);
    void manejoErrores(const int error);

#endif