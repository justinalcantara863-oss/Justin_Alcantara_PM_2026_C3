#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int anio;
    int mes;
    double maxima;
    double minima;
} ResumenMensual;

int compararMeses(const void *izquierda, const void *derecha) {
    const ResumenMensual *a = izquierda;
    const ResumenMensual *b = derecha;

    if (a->anio != b->anio) {
        return (a->anio > b->anio) - (a->anio < b->anio);
    }

    return a->mes - b->mes;
}

int main(void) {
    FILE *archivo = fopen("TEMPERATURAS.txt", "r");
    if (archivo == NULL) {
        perror("No se pudo abrir TEMPERATURAS.txt");
        return EXIT_FAILURE;
    }

    ResumenMensual *meses = NULL;
    size_t total = 0;
    size_t numeroLinea = 0;
    int correcto = 1;
    char linea[256];

    while (fgets(linea, sizeof linea, archivo) != NULL) {
        char observatorio[32];
        char extra;
        int dia, mes, anio;
        double maxima, minima;
        numeroLinea++;

        if (sscanf(linea, "%31s %d %d %d %lf %lf %c",
                   observatorio, &dia, &mes, &anio,
                   &maxima, &minima, &extra) != 6 ||
            dia < 1 || dia > 31 || mes < 1 || mes > 12 || anio < 1 ||
            !isfinite(maxima) || !isfinite(minima) || maxima < minima) {
            fprintf(stderr, "Registro invalido en la linea %zu.\n", numeroLinea);
            correcto = 0;
            break;
        }

        size_t i = 0;
        while (i < total && (meses[i].anio != anio || meses[i].mes != mes)) {
            i++;
        }

        if (i == total) {
            ResumenMensual *ampliado = realloc(meses, (total + 1) * sizeof *meses);
            if (ampliado == NULL) {
                fputs("No hay memoria para guardar otro mes.\n", stderr);
                correcto = 0;
                break;
            }

            meses = ampliado;
            meses[total] = (ResumenMensual){anio, mes, maxima, minima};
            total++;
        } else {
            if (maxima > meses[i].maxima) {
                meses[i].maxima = maxima;
            }
            if (minima < meses[i].minima) {
                meses[i].minima = minima;
            }
        }
    }

    if (ferror(archivo)) {
        perror("Error al leer TEMPERATURAS.txt");
        correcto = 0;
    }
    fclose(archivo);

    if (!correcto) {
        free(meses);
        return EXIT_FAILURE;
    }

    if (total == 0) {
        puts("No hay registros de temperaturas.");
    } else {
        qsort(meses, total, sizeof *meses, compararMeses);
        puts("Mes\tMaxima\tMinima\tMedia");

        for (size_t i = 0; i < total; i++) {
            double media = meses[i].maxima / 2.0 + meses[i].minima / 2.0;
            printf("%02d/%04d\t%.2f\t%.2f\t%.2f\n",
                   meses[i].mes, meses[i].anio,
                   meses[i].maxima, meses[i].minima, media);
        }
    }

    free(meses);
    return EXIT_SUCCESS;
}
