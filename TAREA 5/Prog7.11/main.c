#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum { MAX_TEXTO = 50 };

int main(void) {
    char texto[MAX_TEXTO + 3];
    char entrada[32];
    char extra;
    int posicion;

    printf("Escribe un texto de hasta 50 caracteres: ");
    if (fgets(texto, sizeof texto, stdin) == NULL) {
        return 1;
    }

    size_t longitud = strcspn(texto, "\r\n");
    if (longitud == 0 || longitud > MAX_TEXTO) {
        puts("El texto debe tener entre 1 y 50 caracteres.");
        return 1;
    }
    texto[longitud] = '\0';

    printf("Escribe la posicion (1 a %zu): ", longitud);
    if (fgets(entrada, sizeof entrada, stdin) == NULL ||
        sscanf(entrada, "%2d %c", &posicion, &extra) != 1 ||
        posicion < 1 || (size_t)posicion > longitud) {
        puts("Posicion invalida.");
        return 1;
    }

    unsigned char caracter = (unsigned char)texto[posicion - 1];
    printf("'%c' %s una letra minuscula.\n",
           caracter, islower(caracter) ? "es" : "no es");

    return 0;
}
