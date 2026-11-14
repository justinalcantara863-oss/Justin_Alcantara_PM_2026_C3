#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char entrada[128];
    double suma = 0.0;
    size_t cantidad = 0;

    for (;;) {
        printf("Deseas ingresar un numero (S/N)? ");
        if (fgets(entrada, sizeof entrada, stdin) == NULL) {
            break;
        }

        char opcion, extra;
        if (sscanf(entrada, " %c %c", &opcion, &extra) != 1) {
            puts("Responde S o N.");
            continue;
        }

        opcion = (char)toupper((unsigned char)opcion);
        if (opcion == 'N') {
            break;
        }
        if (opcion != 'S') {
            puts("Responde S o N.");
            continue;
        }

        printf("Escribe un numero de hasta 10 caracteres: ");
        if (fgets(entrada, sizeof entrada, stdin) == NULL) {
            break;
        }

        size_t longitud = strcspn(entrada, "\r\n");
        if (longitud == sizeof entrada - 1 && entrada[longitud] == '\0') {
            int caracter;
            while ((caracter = getchar()) != '\n' && caracter != EOF) {
            }
        }

        char *fin;
        errno = 0;
        double numero = strtod(entrada, &fin);

        if (longitud > 10 || fin == entrada ||
            errno == ERANGE || !isfinite(numero)) {
            puts("Numero invalido.");
            continue;
        }

        while (isspace((unsigned char)*fin)) {
            fin++;
        }
        if (*fin != '\0') {
            puts("Numero invalido.");
            continue;
        }

        double nuevaSuma = suma + numero;
        if (!isfinite(nuevaSuma)) {
            puts("La suma excede el rango permitido.");
            continue;
        }

        suma = nuevaSuma;
        cantidad++;
    }

    if (cantidad == 0) {
        puts("No se ingresaron numeros.");
        return 0;
    }

    printf("Suma: %.2f\n", suma);
    printf("Promedio: %.2f\n", suma / (double)cantidad);
    return 0;
}
