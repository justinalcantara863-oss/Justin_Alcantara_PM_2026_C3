#include <stdio.h>
#include <string.h>

typedef struct {
    int matricula;
    char nombre[60];
    int carrera;
    float promedio;
} Alumno;

int leerLinea(const char mensaje[], char texto[], int capacidad) {
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

int guardarAlumnos(FILE *archivo) {
    char linea[64];
    char extra;

    for (;;) {
        int opcion;
        if (!leerLinea("Ingresar un alumno (1 = si, 0 = no): ",
                       linea, sizeof linea) ||
            sscanf(linea, "%1d %c", &opcion, &extra) != 1 ||
            (opcion != 0 && opcion != 1)) {
            puts("Opcion invalida.");
            return 0;
        }
        if (opcion == 0) {
            return 1;
        }

        Alumno alumno = {0};
        if (!leerLinea("Matricula: ", linea, sizeof linea) ||
            sscanf(linea, "%9d %c", &alumno.matricula, &extra) != 1 ||
            alumno.matricula <= 0 ||
            !leerLinea("Nombre: ", alumno.nombre, sizeof alumno.nombre) ||
            !leerLinea("Codigo de carrera (1 a 5): ", linea, sizeof linea) ||
            sscanf(linea, "%1d %c", &alumno.carrera, &extra) != 1 ||
            alumno.carrera < 1 || alumno.carrera > 5 ||
            !leerLinea("Promedio (0 a 10): ", linea, sizeof linea) ||
            sscanf(linea, "%f %c", &alumno.promedio, &extra) != 1 ||
            !(alumno.promedio >= 0.0f && alumno.promedio <= 10.0f)) {
            puts("Datos invalidos.");
            return 0;
        }

        if (fwrite(&alumno, sizeof alumno, 1, archivo) != 1) {
            perror("Error al escribir ad1.dat");
            return 0;
        }
    }
}

int main(void) {
    FILE *archivo = fopen("ad1.dat", "wb");
    if (archivo == NULL) {
        perror("No se pudo abrir ad1.dat");
        return 1;
    }

    puts("Carreras: 1 Economia, 2 Contabilidad, 3 Derecho,"
         " 4 Ingenieria en Computacion, 5 Ingenieria Industrial.");

    int correcto = guardarAlumnos(archivo);
    if (fclose(archivo) == EOF) {
        perror("No se pudo cerrar ad1.dat");
        return 1;
    }

    if (!correcto) {
        return 1;
    }

    puts("Alumnos guardados en ad1.dat.");
    return 0;
}
