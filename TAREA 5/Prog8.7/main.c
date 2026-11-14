#include <stdio.h>
#include <string.h>

enum { MAX_ALUMNOS = 50, NUM_MATERIAS = 5 };

typedef struct {
    char nombre[60];
    int nota;
} Materia;

typedef struct {
    int matricula;
    char nombre[60];
    Materia materias[NUM_MATERIAS];
} Alumno;

int leerTexto(const char mensaje[], char texto[], int capacidad) {
    printf("%s", mensaje);
    if (fgets(texto, capacidad, stdin) == NULL) {
        return 0;
    }

    size_t longitud = strcspn(texto, "\r\n");
    if (texto[longitud] == '\0' && !feof(stdin)) {
        return 0;
    }

    texto[longitud] = '\0';
    return longitud > 0;
}

int leerEntero(const char mensaje[], int minimo, int maximo, int *valor) {
    char linea[32];
    char extra;

    return leerTexto(mensaje, linea, sizeof linea) &&
           sscanf(linea, "%9d %c", valor, &extra) == 1 &&
           *valor >= minimo && *valor <= maximo;
}

int leerAlumno(Alumno *alumno) {
    if (!leerEntero("Matricula: ", 1, 999999999, &alumno->matricula) ||
        !leerTexto("Nombre: ", alumno->nombre, sizeof alumno->nombre)) {
        return 0;
    }

    for (int i = 0; i < NUM_MATERIAS; i++) {
        Materia *materia = &alumno->materias[i];
        printf("Materia %d\n", i + 1);

        if (!leerTexto("Nombre de la materia: ", materia->nombre,
                       sizeof materia->nombre) ||
            !leerEntero("Nota (0 a 10): ", 0, 10, &materia->nota)) {
            return 0;
        }
    }

    return 1;
}

double promedioAlumno(const Alumno *alumno) {
    int suma = 0;

    for (int i = 0; i < NUM_MATERIAS; i++) {
        suma += alumno->materias[i].nota;
    }

    return (double)suma / NUM_MATERIAS;
}

int main(void) {
    Alumno alumnos[MAX_ALUMNOS];
    int cantidad;

    if (!leerEntero("Cuantos alumnos (1 a 50): ", 1, MAX_ALUMNOS, &cantidad)) {
        puts("Cantidad invalida.");
        return 1;
    }

    for (int i = 0; i < cantidad; i++) {
        printf("\nAlumno %d\n", i + 1);
        if (!leerAlumno(&alumnos[i])) {
            puts("Datos invalidos.");
            return 1;
        }
    }

    int sumaCuarta = 0;
    puts("\nPromedio de cada alumno");
    for (int i = 0; i < cantidad; i++) {
        printf("%d | %s | %.2f\n", alumnos[i].matricula,
               alumnos[i].nombre, promedioAlumno(&alumnos[i]));
        sumaCuarta += alumnos[i].materias[3].nota;
    }

    int hayMatriculas = 0;
    puts("\nMatriculas con nota mayor que 9 en la tercera materia");
    for (int i = 0; i < cantidad; i++) {
        if (alumnos[i].materias[2].nota > 9) {
            printf("%d\n", alumnos[i].matricula);
            hayMatriculas = 1;
        }
    }

    if (!hayMatriculas) {
        puts("Ninguna.");
    }

    printf("\nPromedio de la cuarta materia: %.2f\n",
           (double)sumaCuarta / cantidad);
    return 0;
}
