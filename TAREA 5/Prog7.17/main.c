#include <stdio.h>
#include <string.h>

enum { MAX_TEXTO = 50 };

void invertirCadena(const char texto[], char invertido[]) {
    size_t longitud = strlen(texto);

    for (size_t i = 0; i < longitud; i++) {
        invertido[i] = texto[longitud - 1 - i];
    }
    invertido[longitud] = '\0';
}

int main(void) {
    char texto[MAX_TEXTO + 3];
    char invertido[MAX_TEXTO + 1];

    printf("Escribe una linea de hasta 50 caracteres: ");
    if (fgets(texto, sizeof texto, stdin) == NULL) {
        return 1;
    }

    size_t longitud = strcspn(texto, "\r\n");
    if (longitud > MAX_TEXTO) {
        puts("La linea es demasiado larga.");
        return 1;
    }

    texto[longitud] = '\0';
    invertirCadena(texto, invertido);
    printf("Texto invertido: %s\n", invertido);

    return 0;
}
