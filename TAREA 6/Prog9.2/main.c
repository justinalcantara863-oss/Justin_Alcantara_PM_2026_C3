#include <stdio.h>

int main(void) {
    FILE *archivo = fopen("arc.txt", "r");
    if (archivo == NULL) {
        perror("No se pudo abrir arc.txt");
        return 1;
    }

    int caracter;
    while ((caracter = fgetc(archivo)) != EOF) {
        putchar(caracter);
    }

    if (ferror(archivo)) {
        perror("Error al leer arc.txt");
        fclose(archivo);
        return 1;
    }

    fclose(archivo);
    putchar('\n');
    return 0;
}
