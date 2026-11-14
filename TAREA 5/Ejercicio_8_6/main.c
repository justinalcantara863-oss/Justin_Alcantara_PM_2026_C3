#include <stdio.h>
#include <string.h>
#include <windows.h>

int main(void) {
    char buscado[80];
    char entrada[32];
    char registro[128];
    char extra;
    int nuevaEdad;

    printf("Nombre que quieres buscar: ");
    if (fgets(buscado, sizeof buscado, stdin) == NULL) {
        return 1;
    }
    buscado[strcspn(buscado, "\r\n")] = '\0';

    printf("Nueva edad: ");
    if (fgets(entrada, sizeof entrada, stdin) == NULL ||
        sscanf(entrada, "%d %c", &nuevaEdad, &extra) != 1 ||
        nuevaEdad < 0 || nuevaEdad > 130) {
        puts("Edad invalida.");
        return 1;
    }

    FILE *original = fopen("PERSONAL.txt", "r");
    if (original == NULL) {
        perror("No se pudo abrir PERSONAL.txt");
        return 1;
    }

    FILE *temporal = fopen("PERSONAL.tmp", "w");
    if (temporal == NULL) {
        perror("No se pudo crear PERSONAL.tmp");
        fclose(original);
        return 1;
    }

    int encontrado = 0;
    int error = 0;

    while (fgets(registro, sizeof registro, original) != NULL) {
        char nombre[80];
        int edad;
        int escrito;

        if (!encontrado &&
            sscanf(registro, "%79[^\t]\t%d", nombre, &edad) == 2 &&
            strcmp(nombre, buscado) == 0) {
            escrito = fprintf(temporal, "%s\t%d\n", nombre, nuevaEdad);
            encontrado = 1;
        } else {
            escrito = fputs(registro, temporal);
        }

        if (escrito < 0) {
            error = 1;
            break;
        }
    }

    if (ferror(original)) {
        error = 1;
    }
    fclose(original);

    if (fclose(temporal) != 0) {
        error = 1;
    }

    if (error || !encontrado) {
        remove("PERSONAL.tmp");
        puts(error ? "Error al procesar el archivo." : "Persona no encontrada.");
        return error ? 1 : 0;
    }

    if (!MoveFileExA("PERSONAL.tmp", "PERSONAL.txt", MOVEFILE_REPLACE_EXISTING)) {
        remove("PERSONAL.tmp");
        puts("No se pudo actualizar PERSONAL.txt.");
        return 1;
    }

    puts("Registro actualizado.");
    return 0;
}
