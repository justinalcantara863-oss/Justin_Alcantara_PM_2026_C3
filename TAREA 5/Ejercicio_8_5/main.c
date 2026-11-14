#include <stdio.h>
#include <string.h>
#include <windows.h>

int main(void) {
    char nombreBuscado[80];
    char registro[128];
    int encontrado = 0;
    int errorEscritura = 0;

    printf("Nombre de la persona que quieres eliminar: ");
    if (fgets(nombreBuscado, sizeof nombreBuscado, stdin) == NULL) {
        return 1;
    }
    nombreBuscado[strcspn(nombreBuscado, "\r\n")] = '\0';

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

    while (fgets(registro, sizeof registro, original) != NULL) {
        char nombre[80];
        int edad;

        if (sscanf(registro, "%79[^\t]\t%d", nombre, &edad) == 2 &&
            strcmp(nombre, nombreBuscado) == 0) {
            encontrado = 1;
            continue;
        }

        if (fputs(registro, temporal) == EOF) {
            errorEscritura = 1;
            break;
        }
    }

    int errorLectura = ferror(original);
    fclose(original);
    if (fclose(temporal) != 0) {
        errorEscritura = 1;
    }

    if (errorLectura || errorEscritura) {
        remove("PERSONAL.tmp");
        puts("Error al copiar los registros.");
        return 1;
    }

    if (!encontrado) {
        remove("PERSONAL.tmp");
        puts("Persona no encontrada.");
        return 0;
    }

    if (!MoveFileExA("PERSONAL.tmp", "PERSONAL.txt", MOVEFILE_REPLACE_EXISTING)) {
        remove("PERSONAL.tmp");
        puts("No se pudo actualizar PERSONAL.txt.");
        return 1;
    }

    puts("Registro eliminado.");
    return 0;
}
