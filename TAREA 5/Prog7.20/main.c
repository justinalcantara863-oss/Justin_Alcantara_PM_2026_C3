#include <stdio.h>

enum { MAX_FILAS = 20, MAX_TEXTO = 50 };

size_t contarCaracteres(const char texto[]) {
    size_t longitud = 0;
    while (texto[longitud] != '\0' &&
           texto[longitud] != '\n' &&
           texto[longitud] != '\r') {
        longitud++;
    }
    return longitud;
}

int main(void) {
    char filas[MAX_FILAS][MAX_TEXTO + 3];
    char entrada[32];
    char extra;
    int cantidad;
    int filaMayor = 0;
    size_t longitudMayor = 0;

    printf("Cuantas lineas vas a escribir (1 a 20): ");
    if (fgets(entrada, sizeof entrada, stdin) == NULL ||
        sscanf(entrada, "%2d %c", &cantidad, &extra) != 1 ||
        cantidad < 1 || cantidad > MAX_FILAS) {
        puts("Cantidad invalida.");
        return 1;
    }

    for (int i = 0; i < cantidad; i++) {
        printf("Linea %d (hasta 50 caracteres): ", i + 1);
        if (fgets(filas[i], sizeof filas[i], stdin) == NULL) {
            return 1;
        }

        size_t longitud = contarCaracteres(filas[i]);
        if (longitud > MAX_TEXTO) {
            puts("La linea es demasiado larga.");
            return 1;
        }
        filas[i][longitud] = '\0';

        if (longitud > longitudMayor) {
            longitudMayor = longitud;
            filaMayor = i;
        }
    }

    printf("Cadena mas larga: %s\n", filas[filaMayor]);
    printf("Longitud: %zu\n", longitudMayor);
    return 0;
}
