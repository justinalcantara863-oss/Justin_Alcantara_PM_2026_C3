#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum { MAX_TEXTO = 50 };

int main(void) {
    char texto[MAX_TEXTO + 3];

    printf("Escribe pares de digito y letra (ejemplo: 3p2c): ");
    if (fgets(texto, sizeof texto, stdin) == NULL) {
        return 1;
    }

    size_t longitud = strcspn(texto, "\r\n");
    if (longitud == 0 || longitud > MAX_TEXTO || longitud % 2 != 0) {
        puts("Ingresa pares completos de digito y letra, hasta 50 caracteres.");
        return 1;
    }

    for (size_t i = 0; i < longitud; i += 2) {
        if (texto[i] < '0' || texto[i] > '9' ||
            !isalpha((unsigned char)texto[i + 1])) {
            puts("Cada par debe tener un digito seguido de una letra.");
            return 1;
        }
    }

    printf("Resultado: ");
    for (size_t i = 0; i < longitud; i += 2) {
        int repeticiones = texto[i] - '0';

        for (int j = 0; j < repeticiones; j++) {
            putchar((unsigned char)texto[i + 1]);
        }
    }
    putchar('\n');

    return 0;
}
