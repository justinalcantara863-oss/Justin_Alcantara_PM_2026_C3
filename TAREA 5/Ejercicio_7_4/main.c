#include <stdio.h>
#include <string.h>

int esPalindromo(const char texto[]) {
    size_t longitud = strlen(texto);

    for (size_t i = 0; i < longitud / 2; i++) {
        if (texto[i] != texto[longitud - 1 - i]) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    char texto[256];

    printf("Escribe un texto: ");
    if (fgets(texto, sizeof texto, stdin) == NULL) {
        return 1;
    }

    texto[strcspn(texto, "\r\n")] = '\0';

    if (esPalindromo(texto)) {
        printf("Es un palindromo.\n");
    } else {
        printf("No es un palindromo.\n");
    }

    return 0;
}
