#include <ctype.h>
#include <stdio.h>

int main(void) {
    char caracter;

    printf("Escribe un caracter para comprobar si es un digito: ");
    if (scanf(" %c", &caracter) != 1) {
        return 1;
    }
    printf("%c %s un digito.\n", caracter,
           isdigit((unsigned char)caracter) ? "es" : "no es");

    printf("Escribe un caracter para comprobar si es una letra: ");
    if (scanf(" %c", &caracter) != 1) {
        return 1;
    }
    printf("%c %s una letra.\n", caracter,
           isalpha((unsigned char)caracter) ? "es" : "no es");

    printf("Escribe un caracter para comprobar si es minuscula: ");
    if (scanf(" %c", &caracter) != 1) {
        return 1;
    }
    printf("%c %s una letra minuscula.\n", caracter,
           islower((unsigned char)caracter) ? "es" : "no es");

    printf("Escribe una letra para pasarla a minuscula: ");
    if (scanf(" %c", &caracter) != 1) {
        return 1;
    }
    if (isalpha((unsigned char)caracter)) {
        printf("Minuscula: %c\n", tolower((unsigned char)caracter));
    } else {
        puts("El caracter ingresado no es una letra.");
    }

    printf("Escribe una letra para pasarla a mayuscula: ");
    if (scanf(" %c", &caracter) != 1) {
        return 1;
    }
    if (isalpha((unsigned char)caracter)) {
        printf("Mayuscula: %c\n", toupper((unsigned char)caracter));
    } else {
        puts("El caracter ingresado no es una letra.");
    }

    return 0;
}
