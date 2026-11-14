#include <stdio.h>

int main(void) {
    char segundo;

    printf("Escribe un caracter: ");
    int primero = getchar();
    if (primero == EOF) {
        return 1;
    }

    printf("Primer caracter: ");
    putchar(primero);
    putchar('\n');

    printf("Caracter fijo: ");
    putchar('$');
    putchar('\n');

    printf("Escribe otro caracter: ");
    if (scanf(" %c", &segundo) != 1) {
        return 1;
    }

    printf("Segundo caracter: %c\n", segundo);
    return 0;
}
