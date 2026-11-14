#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char texto[100];
    char *restoReal;
    char *restoEntero;

    printf("Escribe un entero decimal para atoi (por ejemplo, 12): ");
    if (fgets(texto, sizeof texto, stdin) == NULL) {
        return 1;
    }

    errno = 0;
    long entero = strtol(texto, &restoEntero, 10);
    if (restoEntero == texto || errno == ERANGE ||
        entero < INT_MIN || entero > INT_MAX) {
        puts("El valor no se puede convertir a int.");
        return 1;
    }
    printf("atoi: %d\n", atoi(texto));

    printf("Escribe un numero con texto al final (por ejemplo, 7.89kg): ");
    if (fgets(texto, sizeof texto, stdin) == NULL) {
        return 1;
    }
    texto[strcspn(texto, "\r\n")] = '\0';

    errno = 0;
    double real = strtod(texto, &restoReal);
    if (restoReal == texto || errno == ERANGE) {
        puts("El valor no se puede convertir a double.");
        return 1;
    }
    printf("atof: %.2f\n", atof(texto));
    printf("strtod: %.2f | Resto: [%s]\n", real, restoReal);

    errno = 0;
    entero = strtol(texto, &restoEntero, 10);
    if (restoEntero != texto && errno != ERANGE) {
        printf("atol: %ld\n", atol(texto));
    }

    errno = 0;
    entero = strtol(texto, &restoEntero, 0);
    if (restoEntero != texto && errno != ERANGE) {
        printf("strtol: %ld | Resto: [%s]\n", entero, restoEntero);
    }

    return 0;
}
