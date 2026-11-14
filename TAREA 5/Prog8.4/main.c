#include <stdio.h>
#include <string.h>

enum { MAX_ALUMNOS = 100, MATERIAS = 5 };

typedef struct {
    int matricula;
    char nombre[64];
    double calificaciones[MATERIAS];
} Alumno;

int leerAlumno(Alumno *alumno) {
    char linea[128];
    char extra;

    printf("Matricula: ");
    if (fgets(linea, sizeof linea, stdin) == NULL ||
        sscanf(linea, "%9d %c", &alumno->matricula, &extra) != 1 ||
        alumno->matricula <= 0) {
        return 0;
    }

    printf("Nombre y apellido: ");
    if (fgets(linea, sizeof linea, stdin) == NULL) {
        return 0;
    }

    size_t longitud = strcspn(linea, "\r\n");
    if (longitud == 0 || longitud >= sizeof alumno->nombre) {
        return 0;
    }
    linea[longitud] = '\0';
    strcpy(alumno->nombre, linea);

    printf("Escribe las cinco notas separadas por espacios: ");
    if (fgets(linea, sizeof linea, stdin) == NULL ||
        sscanf(linea, "%lf %lf %lf %lf %lf %c",
               &alumno->calificaciones[0], &alumno->calificaciones[1],
               &alumno->calificaciones[2], &alumno->calificaciones[3],
               &alumno->calificaciones[4], &extra) != MATERIAS) {
        return 0;
    }

    for (int i = 0; i < MATERIAS; i++) {
        double nota = alumno->calificaciones[i];
        if (!(nota >= 0.0 && nota <= 10.0)) {
            return 0;
        }
    }

    return 1;
}

double promedioAlumno(const Alumno *alumno) {
    double suma = 0.0;
    for (int i = 0; i < MATERIAS; i++) {
        suma += alumno->calificaciones[i];
    }
    return suma / MATERIAS;
}

int main(void) {
    Alumno alumnos[MAX_ALUMNOS];
    char linea[32];
    char extra;
    int cantidad;

    printf("Cuantos alumnos vas a ingresar (1 a 100): ");
    if (fgets(linea, sizeof linea, stdin) == NULL ||
        sscanf(linea, "%3d %c", &cantidad, &extra) != 1 ||
        cantidad < 1 || cantidad > MAX_ALUMNOS) {
        puts("Cantidad invalida.");
        return 1;
    }

    for (int i = 0; i < cantidad; i++) {
        printf("\nAlumno %d\n", i + 1);
        if (!leerAlumno(&alumnos[i])) {
            puts("Datos invalidos. Las notas deben estar entre 0 y 10.");
            return 1;
        }
    }

    puts("\nPromedio de cada alumno");
    double sumaCuarta = 0.0;
    for (int i = 0; i < cantidad; i++) {
        printf("%d | %s | %.2f\n", alumnos[i].matricula,
               alumnos[i].nombre, promedioAlumno(&alumnos[i]));
        sumaCuarta += alumnos[i].calificaciones[3];
    }

    puts("\nMatriculas con nota mayor que 9 en la tercera materia");
    int hayMatriculas = 0;
    for (int i = 0; i < cantidad; i++) {
        if (alumnos[i].calificaciones[2] > 9.0) {
            printf("%d\n", alumnos[i].matricula);
            hayMatriculas = 1;
        }
    }
    if (!hayMatriculas) {
        puts("Ninguna.");
    }

    printf("\nPromedio general de la cuarta materia: %.2f\n",
           sumaCuarta / cantidad);
    return 0;
}
