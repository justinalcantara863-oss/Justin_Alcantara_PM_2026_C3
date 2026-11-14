#include <stdio.h>
#include <string.h>

enum { MAX_FILAS = 20, MAX_TEXTO = 30, TAM_FILA = MAX_TEXTO + 3 };

void invertirFilas(char filas[][TAM_FILA], int cantidad) {
    char temporal[TAM_FILA];

    for (int i = 0; i < cantidad / 2; i++) {
        int opuesta = cantidad - 1 - i;

        strcpy(temporal, filas[i]);
        strcpy(filas[i], filas[opuesta]);
        strcpy(filas[opuesta], temporal);
    }
}

int main(void) {
    char filas[MAX_FILAS][TAM_FILA];
    char entrada[32];
    char extra;
    int cantidad;

    printf("Cuantas lineas vas a escribir (1 a 20): ");
    if (fgets(entrada, sizeof entrada, stdin) == NULL ||
        sscanf(entrada, "%2d %c", &cantidad, &extra) != 1 ||
        cantidad < 1 || cantidad > MAX_FILAS) {
        puts("Cantidad invalida.");
        return 1;
    }

    for (int i = 0; i < cantidad; i++) {
        printf("Linea %d (hasta 30 caracteres): ", i + 1);
        if (fgets(filas[i], sizeof filas[i], stdin) == NULL) {
            return 1;
        }

        size_t longitud = strcspn(filas[i], "\r\n");
        if (longitud > MAX_TEXTO) {
            puts("La linea es demasiado larga.");
            return 1;
        }
        filas[i][longitud] = '\0';
    }

    invertirFilas(filas, cantidad);

    puts("\nLineas en orden inverso:");
    for (int i = 0; i < cantidad; i++) {
        puts(filas[i]);
    }

    return 0;
}
