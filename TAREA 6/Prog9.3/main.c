#include <stdio.h>

int main(void) {
    FILE *archivo = fopen("arc.txt", "w");
    if (archivo == NULL) {
        perror("No se pudo abrir arc.txt");
        return 1;
    }

    char linea[256];
    puts("Escribe varias lineas. Pulsa Enter en una linea vacia para terminar.");

    while (fgets(linea, sizeof linea, stdin) != NULL) {
        if (linea[0] == '\n') {
            break;
        }

        if (fputs(linea, archivo) == EOF) {
            perror("No se pudo escribir en arc.txt");
            fclose(archivo);
            return 1;
        }
    }

    if (fclose(archivo) == EOF) {
        perror("No se pudo guardar arc.txt");
        return 1;
    }

    puts("Lineas guardadas en arc.txt.");
    return 0;
}
