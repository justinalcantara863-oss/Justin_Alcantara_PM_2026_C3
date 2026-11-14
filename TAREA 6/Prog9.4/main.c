#include <stdio.h>

int main(void) {
    FILE *archivo = fopen("arc.txt", "r");
    if (archivo == NULL) {
        perror("No se pudo abrir arc.txt");
        return 1;
    }

    char linea[256];
    while (fgets(linea, sizeof linea, archivo) != NULL) {
        fputs(linea, stdout);
    }

    if (ferror(archivo)) {
        perror("Error al leer arc.txt");
        fclose(archivo);
        return 1;
    }

    fclose(archivo);
    return 0;
}
