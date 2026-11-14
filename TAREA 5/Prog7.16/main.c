#include <stdio.h>
#include <string.h>

enum { MAX_TEXTO = 50 };

int leerCadena(const char mensaje[], char texto[], int capacidad) {
    printf("%s", mensaje);
    if (fgets(texto, capacidad, stdin) == NULL) {
        return 0;
    }

    size_t longitud = strcspn(texto, "\r\n");
    if (longitud > MAX_TEXTO) {
        return 0;
    }

    texto[longitud] = '\0';
    return 1;
}

size_t contarApariciones(const char texto[], const char buscado[]) {
    size_t total = 0;
    const char *coincidencia = strstr(texto, buscado);

    while (coincidencia != NULL) {
        total++;
        coincidencia = strstr(coincidencia + 1, buscado);
    }

    return total;
}

int main(void) {
    char texto[MAX_TEXTO + 3];
    char buscado[MAX_TEXTO + 3];

    if (!leerCadena("Escribe el texto (hasta 50 caracteres): ",
                    texto, sizeof texto) ||
        !leerCadena("Escribe la cadena que quieres buscar: ",
                    buscado, sizeof buscado) ||
        buscado[0] == '\0') {
        puts("Entrada invalida. La cadena buscada debe tener de 1 a 50 caracteres.");
        return 1;
    }

    printf("Apariciones: %zu\n", contarApariciones(texto, buscado));
    return 0;
}
