#include <stdio.h>
#include <string.h>

typedef union {
    char celular[24];
    char correo[80];
} Contacto;

typedef struct {
    int matricula;
    char nombre[60];
    char carrera[60];
    float promedio;
    char tipoContacto;
    Contacto contacto;
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

int leerAlumno(Alumno *alumno) {
    char entrada[64];
    char extra;

    if (!leerTexto("Matricula: ", entrada, sizeof entrada) ||
        sscanf(entrada, "%9d %c", &alumno->matricula, &extra) != 1 ||
        alumno->matricula <= 0 ||
        !leerTexto("Nombre: ", alumno->nombre, sizeof alumno->nombre) ||
        !leerTexto("Carrera: ", alumno->carrera, sizeof alumno->carrera) ||
        !leerTexto("Promedio (0 a 10): ", entrada, sizeof entrada) ||
        sscanf(entrada, "%f %c", &alumno->promedio, &extra) != 1 ||
        !(alumno->promedio >= 0.0f && alumno->promedio <= 10.0f)) {
        return 0;
    }

    if (!leerTexto("Contacto (1 para celular, 2 para correo): ",
                   entrada, sizeof entrada) ||
        sscanf(entrada, " %c %c", &alumno->tipoContacto, &extra) != 1) {
        return 0;
    }

    switch (alumno->tipoContacto) {
        case '1':
            return leerTexto("Celular: ", alumno->contacto.celular,
                             sizeof alumno->contacto.celular);
        case '2':
            return leerTexto("Correo: ", alumno->contacto.correo,
                             sizeof alumno->contacto.correo);
        default:
            return 0;
    }
}

void mostrarAlumno(const Alumno *alumno) {
    printf("\nMatricula: %d\nNombre: %s\nCarrera: %s\nPromedio: %.2f\n",
           alumno->matricula, alumno->nombre, alumno->carrera, alumno->promedio);

    if (alumno->tipoContacto == '1') {
        printf("Celular: %s\n", alumno->contacto.celular);
    } else {
        printf("Correo: %s\n", alumno->contacto.correo);
    }
}

int main(void) {
    const Alumno primero = {
        120, "Maria", "Contabilidad", 8.9f, '1',
        {.celular = "809-555-0100"}
    };
    Alumno segundo;

    if (!leerAlumno(&segundo)) {
        puts("Datos invalidos.");
        return 1;
    }

    mostrarAlumno(&primero);
    mostrarAlumno(&segundo);
    return 0;
}
