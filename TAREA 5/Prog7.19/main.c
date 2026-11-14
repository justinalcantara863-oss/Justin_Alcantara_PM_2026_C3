#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum { MAX_TEXTO = 50 };

size_t contarPalabras(const char texto[]) {
    size_t total = 0;
    int dentroDePalabra = 0;

    for (size_t i = 0; texto[i] != '\0'; i++) {
        if (isspace((unsigned char)texto[i])) {
            dentroDePalabra = 0;
        } else if (!dentroDePalabra) {
            total++;
            dentroDePalabra = 1;
        }
    }

    return total;
}

int main(void) {
    char texto[MAX_TEXTO + 3];

    printf("Escribe una frase de hasta 50 caracteres: ");
    if (fgets(texto, sizeof texto, stdin) == NULL) {
        return 1;
    }

    size_t longitud = strcspn(texto, "\r\n");
    if (longitud > MAX_TEXTO) {
        puts("La frase es demasiado larga.");
        return 1;
    }

    texto[longitud] = '\0';
    printf("Numero de palabras: %zu\n", contarPalabras(texto));
    return 0;
}
