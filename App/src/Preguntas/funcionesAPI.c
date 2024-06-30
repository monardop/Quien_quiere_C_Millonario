#include <curl/curl.h>

#include "preguntas.h"

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realSize = size * nmemb;
    tRespuesta *respuesta = (tRespuesta *)userp;
    char *ptr= realloc(respuesta->string, respuesta->size + realSize + 1);
    // el +1 es por el \0

    if ( ptr == NULL)
        return CURL_WRITEFUNC_ERROR;

    respuesta->string = ptr;
    memcpy(&(respuesta->string[respuesta->size]), contents, realSize);
    respuesta->size += realSize;
    respuesta->string[respuesta->size] = '\0';

    return realSize; // es algo que viene por parte de la doc.
}

int obtenerPreguntascURL(tRespuesta *respuesta)
{
    CURL *curl;
    CURLcode result;


    respuesta->string = malloc(1);
    respuesta->size = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl == NULL)
    {
        fprintf(stderr, "Falla en HTTP request\n");
        return FALLA_CURL;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "https://665617e99f970b3b36c44808.mockapi.io/questions/api/questions");

    struct curl_slist *headers = NULL;

    headers = curl_slist_append(headers, "X-Secret: 665617e99f970b3b36c44808");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // guardo la información obtenida en el struct
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)respuesta);

    result = curl_easy_perform(curl);
    // Verificar si la solicitud fue exitosa
    if (result != CURLE_OK)
    {
        fprintf(stderr, "Error en la solicitud: %s\n", curl_easy_strerror(result));
        return FALLA_CURL;
    }

    // Limpiar y cerrar el manejo de curl
    curl_easy_cleanup(curl);
    // Finalizar el manejo global de curl
    curl_global_cleanup();

    return OK;
}
