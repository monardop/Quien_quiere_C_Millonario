#include <curl/curl.h>

#include "../Utilidades/utilidades.h"

struct MemoryStruct {
    char *memory;
    size_t size;
};

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);

    if(!ptr)
        return FALLA_MEMORIA;

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}


int curlManejo()
{
    CURL *curl;
    CURLcode result;

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

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
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    // Realizar la solicitud HTTP GET
    result = curl_easy_perform(curl);
    // Verificar si la solicitud fue exitosa
    if (result != CURLE_OK)
    {
        fprintf(stderr, "Error en la solicitud: %s\n", curl_easy_strerror(result));
        return FALLA_CURL;
    }
    printf("%s <--- Respuesta\n", chunk.memory);
    free(chunk.memory);
    // Limpiar y cerrar el manejo de curl
    curl_easy_cleanup(curl);
    // Finalizar el manejo global de curl
    curl_global_cleanup();

    return OK;
}
