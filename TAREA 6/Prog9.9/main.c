#include <stdio.h>

typedef struct {
    int matricula;
    char nombre[60];
    int carrera;
    float promedio;
} Alumno;

int mostrarAlumnos(FILE *archivo) {
    Alumno alumno;
    size_t leidos;

    puts("Matricula | Nombre | Carrera | Promedio");

    while ((leidos = fread(&alumno, 1, sizeof alumno, archivo)) ==
           sizeof alumno) {
        printf("%d | %.60s | %d | %.2f\n",
               alumno.matricula, alumno.nombre,
               alumno.carrera, alumno.promedio);
    }

    if (ferror(archivo)) {
        perror("Error al leer ad1.dat");
        return 0;
    }

    if (leidos != 0) {
        fputs("El ultimo registro de ad1.dat esta incompleto.\n", stderr);
        return 0;
    }

    return 1;
}

int main(void) {
    FILE *archivo = fopen("ad1.dat", "rb");
    if (archivo == NULL) {
        perror("No se pudo abrir ad1.dat");
        return 1;
    }

    int correcto = mostrarAlumnos(archivo);
    fclose(archivo);
    return correcto ? 0 : 1;
}
