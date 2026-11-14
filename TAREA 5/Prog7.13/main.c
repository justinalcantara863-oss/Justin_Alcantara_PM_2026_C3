#include <stdio.h>

enum { MAX_TEXTO = 50 };

size_t contarCaracteres(const char texto[]) {
    size_t longitud = 0;

    while (texto[longitud] != '\0' &&
           texto[longitud] != '\n' &&
           texto[longitud] != '\r') {
        longitud++;
    }

    return longitud;
}

int main(void) {
    char texto[MAX_TEXTO + 3];

    printf("Escribe un texto de hasta 50 caracteres: ");
    if (fgets(texto, sizeof texto, stdin) == NULL) {
        return 1;
    }

    size_t longitud = contarCaracteres(texto);
    if (longitud > MAX_TEXTO) {
        puts("El texto es demasiado largo.");
        return 1;
    }

    printf("Longitud de la cadena: %zu\n", longitud);
    return 0;
}
