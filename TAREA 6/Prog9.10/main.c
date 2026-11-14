#include <limits.h>
#include <stdio.h>

typedef struct {
    int matricula;
    char nombre[60];
    int carrera;
    float promedio;
} Alumno;

int modificarPromedio(FILE *archivo) {
    Alumno alumno;
    long registro;
    float promedioNuevo;

    printf("Numero de registro (el primero es 1): ");
    if (scanf("%9ld", &registro) != 1 || registro < 1 ||
        registro - 1 > LONG_MAX / (long)sizeof alumno) {
        puts("Numero de registro invalido.");
        return 0;
    }

    long posicion = (registro - 1) * (long)sizeof alumno;
    if (fseek(archivo, posicion, SEEK_SET) != 0) {
        perror("No se pudo ubicar el registro");
        return 0;
    }

    if (fread(&alumno, sizeof alumno, 1, archivo) != 1) {
        puts("No se pudo leer un registro completo en esa posicion.");
        return 0;
    }

    printf("Alumno: %.60s | Promedio actual: %.2f\n",
           alumno.nombre, alumno.promedio);
    printf("Nuevo promedio (0 a 10): ");
    if (scanf("%f", &promedioNuevo) != 1 ||
        !(promedioNuevo >= 0.0f && promedioNuevo <= 10.0f)) {
        puts("Promedio invalido.");
        return 0;
    }

    alumno.promedio = promedioNuevo;
    if (fseek(archivo, posicion, SEEK_SET) != 0 ||
        fwrite(&alumno, sizeof alumno, 1, archivo) != 1) {
        perror("No se pudo actualizar el registro");
        return 0;
    }

    return 1;
}

int main(void) {
    FILE *archivo = fopen("ad1.dat", "r+b");
    if (archivo == NULL) {
        perror("No se pudo abrir ad1.dat");
        return 1;
    }

    int actualizado = modificarPromedio(archivo);
    if (fclose(archivo) == EOF) {
        perror("No se pudo guardar ad1.dat");
        return 1;
    }

    if (!actualizado) {
        return 1;
    }

    puts("Promedio actualizado.");
    return 0;
}
