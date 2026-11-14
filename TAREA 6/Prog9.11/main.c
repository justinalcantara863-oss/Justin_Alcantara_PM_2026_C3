#include <stdio.h>
#include <string.h>

enum { MESES = 12 };

typedef struct {
    int clave;
    int departamento;
    float salario;
    float ventas[MESES];
} Empleado;

int crearArchivoDePrueba(const char ruta[]) {
    Empleado empleados[] = {
        {101, 1, 20000.0f, {600000.0f, 500000.0f}},
        {102, 2, 18000.0f, {500000.0f, 500000.0f}}
    };
    const size_t cantidad = sizeof empleados / sizeof empleados[0];

    FILE *archivo = fopen(ruta, "wb");
    if (archivo == NULL) {
        perror(ruta);
        return 0;
    }

    size_t escritos = fwrite(empleados, sizeof empleados[0], cantidad, archivo);
    return fclose(archivo) == 0 && escritos == cantidad;
}

int actualizarSalarios(FILE *archivo) {
    Empleado empleado;

    for (;;) {
        long posicion = ftell(archivo);
        if (posicion == -1L) {
            return 0;
        }

        size_t leidos = fread(&empleado, 1, sizeof empleado, archivo);
        if (leidos != sizeof empleado) {
            return leidos == 0 && feof(archivo) && !ferror(archivo);
        }

        double ventasAnuales = 0.0;
        for (int mes = 0; mes < MESES; mes++) {
            ventasAnuales += empleado.ventas[mes];
        }

        if (ventasAnuales > 1000000.0) {
            long siguiente = ftell(archivo);
            empleado.salario = (float)(empleado.salario * 1.10);

            if (siguiente == -1L ||
                fseek(archivo, posicion, SEEK_SET) != 0 ||
                fwrite(&empleado, sizeof empleado, 1, archivo) != 1 ||
                fseek(archivo, siguiente, SEEK_SET) != 0) {
                return 0;
            }
        }

        printf("%d | Ventas: %.2f | Salario: %.2f\n",
               empleado.clave, ventasAnuales, empleado.salario);
    }
}

int main(int argc, char *argv[]) {
    const char *ruta = "ad5.dat";

    if (argc == 2 && strcmp(argv[1], "--prueba") == 0) {
        ruta = "ad5_prueba.dat";
        if (!crearArchivoDePrueba(ruta)) {
            fputs("No se pudo guardar el archivo de prueba.\n", stderr);
            return 1;
        }
    }

    FILE *archivo = fopen(ruta, "r+b");
    if (archivo == NULL) {
        perror(ruta);
        return 1;
    }

    int correcto = actualizarSalarios(archivo);
    if (fclose(archivo) != 0 || !correcto) {
        fputs("Error al procesar el archivo de empleados.\n", stderr);
        return 1;
    }

    return 0;
}
