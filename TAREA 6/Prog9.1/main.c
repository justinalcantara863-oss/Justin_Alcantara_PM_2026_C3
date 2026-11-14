#include <stdio.h>

int main(void) {
    FILE *archivo = fopen("arc.txt", "w");
    if (archivo == NULL) {
        perror("No se pudo abrir arc.txt");
        return 1;
    }

    printf("Escribe una linea y pulsa Enter: ");

    int caracter;
    while ((caracter = getchar()) != '\n' && caracter != EOF) {
        if (fputc(caracter, archivo) == EOF) {
            perror("No se pudo escribir en arc.txt");
            fclose(archivo);
            return 1;
        }
    }

    if (fclose(archivo) == EOF) {
        perror("No se pudo guardar arc.txt");
        return 1;
    }

    puts("Texto guardado en arc.txt.");
    return 0;
}
