#include <stdio.h>

int main(void) {
    const char frase[] = "Fin del texto\n";
    FILE *archivo = fopen("libro.txt", "a");

    if (archivo == NULL) {
        perror("No se pudo abrir libro.txt");
        return 1;
    }

    for (size_t i = 0; frase[i] != '\0'; i++) {
        if (fputc(frase[i], archivo) == EOF) {
            perror("Error al escribir en libro.txt");
            fclose(archivo);
            return 1;
        }
    }

    if (fclose(archivo) == EOF) {
        perror("No se pudo guardar libro.txt");
        return 1;
    }

    puts("Frase agregada a libro.txt.");
    return 0;
}
