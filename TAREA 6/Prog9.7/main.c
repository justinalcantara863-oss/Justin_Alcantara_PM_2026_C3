#include <stdio.h>

enum { MAX_ALUMNOS = 35, NUM_NOTAS = 5 };

int mostrarPromedios(FILE *archivo) {
    int cantidad;
    if (fscanf(archivo, "%2d", &cantidad) != 1 ||
        cantidad < 1 || cantidad > MAX_ALUMNOS) {
        puts("Cantidad de alumnos invalida.");
        return 0;
    }

    puts("Matricula | Promedio");
    for (int i = 0; i < cantidad; i++) {
        int matricula;
        double suma = 0.0;

        if (fscanf(archivo, "%9d", &matricula) != 1 || matricula <= 0) {
            printf("Matricula invalida en el registro %d.\n", i + 1);
            return 0;
        }

        for (int j = 0; j < NUM_NOTAS; j++) {
            double nota;
            if (fscanf(archivo, "%lf", &nota) != 1 ||
                !(nota >= 0.0 && nota <= 10.0)) {
                printf("Nota invalida en el registro %d.\n", i + 1);
                return 0;
            }
            suma += nota;
        }

        printf("%d | %.2f\n", matricula, suma / NUM_NOTAS);
    }

    return 1;
}

int main(void) {
    FILE *archivo = fopen("arc8.txt", "r");
    if (archivo == NULL) {
        perror("No se pudo abrir arc8.txt");
        return 1;
    }

    int correcto = mostrarPromedios(archivo);
    fclose(archivo);
    return correcto ? 0 : 1;
}
