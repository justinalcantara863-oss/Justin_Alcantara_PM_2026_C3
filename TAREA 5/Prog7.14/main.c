#include <stdio.h>

enum { MAX_TEXTO = 50 };

size_t longitudRecursiva(const char texto[]) {
    if (texto[0] == '\0' || texto[0] == '\n' || texto[0] == '\r') {
        return 0;
    }

    return 1 + longitudRecursiva(texto + 1);
}

int main(void) {
    char texto[MAX_TEXTO + 3];

    printf("Escribe un texto de hasta 50 caracteres: ");
    if (fgets(texto, sizeof texto, stdin) == NULL) {
        return 1;
    }

    size_t longitud = longitudRecursiva(texto);
    if (longitud > MAX_TEXTO) {
        puts("El texto es demasiado largo.");
        return 1;
    }

    printf("Longitud de la cadena: %zu\n", longitud);
    return 0;
}
