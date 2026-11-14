#include <stdio.h>
#include <string.h>

typedef struct {
    char calle[80];
    int numero;
    char codigoPostal[16];
    char localidad[60];
} Domicilio;

typedef struct {
    char nombre[60];
    char departamento[60];
    double sueldo;
    Domicilio direccion;
} Empleado;

int leerLinea(const char mensaje[], char texto[], int capacidad) {
    printf("%s", mensaje);
    if (fgets(texto, capacidad, stdin) == NULL) {
        return 0;
    }

    size_t longitud = strcspn(texto, "\r\n");
    if (longitud == (size_t)(capacidad - 1) && texto[longitud] == '\0') {
        return 0;
    }

    texto[longitud] = '\0';
    return longitud > 0;
}

int leerEmpleado(Empleado *empleado) {
    char entrada[40];
    char extra;

    return leerLinea("Nombre: ", empleado->nombre, sizeof empleado->nombre) &&
           leerLinea("Departamento: ", empleado->departamento,
                     sizeof empleado->departamento) &&
           leerLinea("Sueldo: ", entrada, sizeof entrada) &&
           sscanf(entrada, "%lf %c", &empleado->sueldo, &extra) == 1 &&
           leerLinea("Calle: ", empleado->direccion.calle,
                     sizeof empleado->direccion.calle) &&
           leerLinea("Numero: ", entrada, sizeof entrada) &&
           sscanf(entrada, "%9d %c", &empleado->direccion.numero, &extra) == 1 &&
           leerLinea("Codigo postal: ", empleado->direccion.codigoPostal,
                     sizeof empleado->direccion.codigoPostal) &&
           leerLinea("Localidad: ", empleado->direccion.localidad,
                     sizeof empleado->direccion.localidad);
}

void mostrarEmpleado(const Empleado *empleado) {
    printf("\nNombre: %s\n", empleado->nombre);
    printf("Departamento: %s\n", empleado->departamento);
    printf("Sueldo: %.2f\n", empleado->sueldo);
    printf("Domicilio: %s %d, %s, CP %s\n",
           empleado->direccion.calle, empleado->direccion.numero,
           empleado->direccion.localidad, empleado->direccion.codigoPostal);
}

int main(void) {
    const Empleado primero = {
        "Arturo", "Compras", 15500.75,
        {"San Jeronimo", 120, "03490", "Toluca"}
    };
    Empleado segundo;

    puts("Ingresa los datos del segundo empleado.");
    if (!leerEmpleado(&segundo)) {
        puts("Datos invalidos.");
        return 1;
    }

    mostrarEmpleado(&primero);
    mostrarEmpleado(&segundo);
    return 0;
}
