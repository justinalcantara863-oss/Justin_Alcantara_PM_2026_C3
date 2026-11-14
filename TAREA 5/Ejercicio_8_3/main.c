#include <stdio.h>

int main(void) {
    FILE *archivo = fopen("PERSONAL.txt", "r");
    if (archivo == NULL) {
        perror("No se pudo abrir PERSONAL.txt");
        return 1;
    }

    char registro[128];

    puts("Nombre\tEdad");
    while (fgets(registro, sizeof registro, archivo) != NULL) {
        fputs(registro, stdout);
    }

    if (ferror(archivo)) {
        perror("Error al leer PERSONAL.txt");
        fclose(archivo);
        return 1;
    }

    fclose(archivo);
    return 0;
}
