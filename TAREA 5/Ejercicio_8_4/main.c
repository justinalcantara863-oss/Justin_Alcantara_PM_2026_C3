#include <stdio.h>
#include <string.h>

int main(void) {
    char nombreBuscado[80];

    printf("Nombre que quieres buscar: ");
    if (fgets(nombreBuscado, sizeof nombreBuscado, stdin) == NULL) {
        return 1;
    }
    nombreBuscado[strcspn(nombreBuscado, "\r\n")] = '\0';

    FILE *archivo = fopen("PERSONAL.txt", "r");
    if (archivo == NULL) {
        perror("No se pudo abrir PERSONAL.txt");
        return 1;
    }

    char registro[128];
    int encontrado = 0;

    while (fgets(registro, sizeof registro, archivo) != NULL) {
        char nombre[80];
        int edad;

        if (sscanf(registro, "%79[^\t]\t%d", nombre, &edad) == 2 &&
            strcmp(nombre, nombreBuscado) == 0) {
            printf("Nombre: %s\nEdad: %d\n", nombre, edad);
            encontrado = 1;
            break;
        }
    }

    if (ferror(archivo)) {
        perror("Error al leer PERSONAL.txt");
        fclose(archivo);
        return 1;
    }

    fclose(archivo);

    if (!encontrado) {
        puts("Persona no encontrada.");
    }

    return 0;
}
