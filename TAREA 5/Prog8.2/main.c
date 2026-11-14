#include <stdio.h>

struct Alumno {
    int matricula;
    char nombre[60];
    char carrera[60];
    float promedio;
    char direccion[100];
};

int leerAlumno(struct Alumno *alumno) {
    printf("Matricula: ");
    if (scanf("%9d", &alumno->matricula) != 1) {
        return 0;
    }

    printf("Nombre: ");
    if (scanf(" %59[^\n]", alumno->nombre) != 1) {
        return 0;
    }

    printf("Carrera: ");
    if (scanf(" %59[^\n]", alumno->carrera) != 1) {
        return 0;
    }

    printf("Promedio: ");
    if (scanf("%f", &alumno->promedio) != 1) {
        return 0;
    }

    printf("Direccion: ");
    return scanf(" %99[^\n]", alumno->direccion) == 1;
}

void mostrarAlumno(const struct Alumno *alumno) {
    printf("Matricula: %d\n", alumno->matricula);
    printf("Nombre: %s\n", alumno->nombre);
    printf("Carrera: %s\n", alumno->carrera);
    printf("Promedio: %.2f\n", alumno->promedio);
    printf("Direccion: %s\n", alumno->direccion);
}

int main(void) {
    struct Alumno primero = {120, "Maria", "Contabilidad", 8.9f, "Queretaro"};
    struct Alumno segundo;
    struct Alumno *puntero = &primero;

    puts("Datos del primer alumno:");
    mostrarAlumno(puntero);

    puntero = &segundo;
    puts("\nIngresa los datos del segundo alumno:");
    if (!leerAlumno(puntero)) {
        puts("Datos invalidos.");
        return 1;
    }

    puts("\nDatos del segundo alumno:");
    mostrarAlumno(puntero);
    return 0;
}
