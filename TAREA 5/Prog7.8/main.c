#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum { MAX_FILAS = 20, MAX_CARACTERES = 50 };

void contarLetras(const char texto[], int *mayusculas, int *minusculas) {
    *mayusculas = 0;
    *minusculas = 0;

    for (size_t i = 0; texto[i] != '\0'; i++) {
        unsigned char caracter = (unsigned char)texto[i];

        if (isupper(caracter)) {
            (*mayusculas)++;
        } else if (islower(caracter)) {
            (*minusculas)++;
        }
    }
}

int main(void) {
    char filas[MAX_FILAS][MAX_CARACTERES + 3];
    char entrada[32];
    char extra;
    int cantidad;

    printf("Cuantas lineas vas a escribir (1 a 20): ");
    if (fgets(entrada, sizeof entrada, stdin) == NULL ||
        sscanf(entrada, "%d %c", &cantidad, &extra) != 1 ||
        cantidad < 1 || cantidad > MAX_FILAS) {
        puts("Cantidad invalida.");
        return 1;
    }

    for (int i = 0; i < cantidad; i++) {
        printf("Linea %d (hasta 50 caracteres): ", i + 1);
        if (fgets(filas[i], sizeof filas[i], stdin) == NULL) {
            return 1;
        }

        size_t longitud = strcspn(filas[i], "\r\n");
        if (longitud > MAX_CARACTERES) {
            puts("La linea es demasiado larga.");
            return 1;
        }
        filas[i][longitud] = '\0';
    }

    for (int i = 0; i < cantidad; i++) {
        int mayusculas;
        int minusculas;

        contarLetras(filas[i], &mayusculas, &minusculas);
        printf("Linea %d: %d mayusculas, %d minusculas\n",
               i + 1, mayusculas, minusculas);
    }

    return 0;
}
