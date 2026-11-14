#include <stdio.h>

typedef struct {
    int matricula;
    char nombre[60];
    char carrera[60];
    float promedio;
    char direccion[100];
} Alumno;

int leerAlumno(Alumno *alumno) {
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

void mostrarAlumno(int numero, const Alumno *alumno) {
    printf("\nAlumno %d\n", numero);
    printf("Matricula: %d\n", alumno->matricula);
    printf("Nombre: %s\n", alumno->nombre);
    printf("Carrera: %s\n", alumno->carrera);
    printf("Promedio: %.2f\n", alumno->promedio);
    printf("Direccion: %s\n", alumno->direccion);
}

int main(void) {
    const Alumno primero = {120, "Maria", "Contabilidad", 8.9f, "Queretaro"};
    Alumno segundo;
    Alumno auxiliar;

    puts("Ingresa los datos del alumno 2.");
    if (!leerAlumno(&segundo)) {
        puts("Datos invalidos.");
        return 1;
    }

    puts("\nIngresa los datos del alumno 3.");
    if (!leerAlumno(&auxiliar)) {
        puts("Datos invalidos.");
        return 1;
    }

    Alumno tercero = auxiliar;

    mostrarAlumno(1, &primero);
    mostrarAlumno(2, &segundo);
    mostrarAlumno(3, &tercero);
    return 0;
}
