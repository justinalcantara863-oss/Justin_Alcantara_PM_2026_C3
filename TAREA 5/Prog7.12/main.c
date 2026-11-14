#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum { MAX_FRASE = 50 };

int main(void) {
    char frase[MAX_FRASE + 3];
    int mayusculas = 0;
    int minusculas = 0;

    printf("Escribe una frase de hasta 50 caracteres: ");
    if (fgets(frase, sizeof frase, stdin) == NULL) {
        return 1;
    }

    size_t longitud = strcspn(frase, "\r\n");
    if (longitud > MAX_FRASE) {
        puts("La frase es demasiado larga.");
        return 1;
    }

    for (size_t i = 0; i < longitud; i++) {
        unsigned char letra = (unsigned char)frase[i];

        if (isupper(letra)) {
            mayusculas++;
        } else if (islower(letra)) {
            minusculas++;
        }
    }

    printf("Mayusculas: %d\n", mayusculas);
    printf("Minusculas: %d\n", minusculas);
    return 0;
}
