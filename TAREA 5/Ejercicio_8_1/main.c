#include <stdio.h>
#include <string.h>

typedef struct {
    char nombre[80];
    int edad;
} Persona;

int main(void) {
    FILE *archivo = fopen("PERSONAL.txt", "w");
    if (archivo == NULL) {
        perror("No se pudo crear PERSONAL.txt");
        return 1;
    }

    Persona persona;
    char lineaEdad[32];

    for (;;) {
        printf("Nombre (Enter para terminar): ");
        if (fgets(persona.nombre, sizeof persona.nombre, stdin) == NULL) {
            break;
        }

        persona.nombre[strcspn(persona.nombre, "\r\n")] = '\0';
        if (persona.nombre[0] == '\0') {
            break;
        }

        printf("Edad: ");
        if (fgets(lineaEdad, sizeof lineaEdad, stdin) == NULL) {
            break;
        }

        char extra;
        if (sscanf(lineaEdad, "%d %c", &persona.edad, &extra) != 1 ||
            persona.edad < 0 || persona.edad > 130) {
            puts("Edad invalida. Vuelve a ingresar el registro.");
            continue;
        }

        if (fprintf(archivo, "%s\t%d\n", persona.nombre, persona.edad) < 0) {
            perror("Error al guardar el registro");
            fclose(archivo);
            return 1;
        }
    }

    if (fclose(archivo) != 0) {
        perror("Error al cerrar el archivo");
        return 1;
    }

    puts("Registros guardados en PERSONAL.txt.");
    return 0;
}
