#include "preguntas.h"

// Función que maneja la respuesta de la solicitud HTTP
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    printf("%.*s", (int)realsize, (char *)contents);
    return realsize;
}
int curlManejo()
{
    CURL *curl;
    CURLcode res;
    // Inicializar el manejo de curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
    // Establecer la URL de la solicitud GET
    curl_easy_setopt(curl, CURLOPT_URL, "https://665617e99f970b3b36c44808.mockapi.io/questions/api/questions");
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "X-Secret: 665617e99f970b3b36c44808");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    // Establecer la función de retorno de llamada para manejar la respuesta
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    // Realizar la solicitud HTTP GET
    res = curl_easy_perform(curl);
    // Verificar si la solicitud fue exitosa
    if (res != CURLE_OK)
        fprintf(stderr, "Error en la solicitud: %s\n", curl_easy_strerror(res));
    // Limpiar y cerrar el manejo de curl
    curl_easy_cleanup(curl);
    // Finalizar el manejo global de curl
    curl_global_cleanup();
    }
    return 0;
}