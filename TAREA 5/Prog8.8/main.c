#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum { MAX_PACIENTES = 100, MAX_CONDICION = 5 };

typedef struct {
    char calle[64];
    int numero;
    char colonia[64];
    char codigoPostal[16];
    char ciudad[64];
} Domicilio;

typedef struct {
    char nombre[64];
    int edad;
    char sexo;
    int condicion;
    Domicilio domicilio;
    char telefono[24];
} Paciente;

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

int leerPaciente(Paciente *paciente) {
    char linea[16];
    char extra;
    Domicilio *direccion = &paciente->domicilio;

    if (!leerTexto("Nombre y apellido: ", paciente->nombre,
                   sizeof paciente->nombre) ||
        !leerEntero("Edad: ", 0, 130, &paciente->edad) ||
        !leerTexto("Sexo (H o M): ", linea, sizeof linea) ||
        sscanf(linea, " %c %c", &paciente->sexo, &extra) != 1) {
        return 0;
    }

    paciente->sexo = (char)toupper((unsigned char)paciente->sexo);
    if (paciente->sexo != 'H' && paciente->sexo != 'M') {
        return 0;
    }

    return leerEntero("Condicion (1 a 5): ", 1, MAX_CONDICION,
                      &paciente->condicion) &&
           leerTexto("Calle: ", direccion->calle, sizeof direccion->calle) &&
           leerEntero("Numero: ", 0, 999999999, &direccion->numero) &&
           leerTexto("Colonia o sector: ", direccion->colonia,
                     sizeof direccion->colonia) &&
           leerTexto("Codigo postal: ", direccion->codigoPostal,
                     sizeof direccion->codigoPostal) &&
           leerTexto("Ciudad: ", direccion->ciudad, sizeof direccion->ciudad) &&
           leerTexto("Telefono: ", paciente->telefono, sizeof paciente->telefono);
}

int main(void) {
    Paciente pacientes[MAX_PACIENTES];
    int cantidad;
    int hombres = 0;
    int porCondicion[MAX_CONDICION + 1] = {0};

    if (!leerEntero("Cuantos pacientes (1 a 100): ", 1, MAX_PACIENTES,
                    &cantidad)) {
        puts("Cantidad invalida.");
        return 1;
    }

    for (int i = 0; i < cantidad; i++) {
        printf("\nPaciente %d\n", i + 1);
        if (!leerPaciente(&pacientes[i])) {
            puts("Datos invalidos.");
            return 1;
        }

        if (pacientes[i].sexo == 'H') {
            hombres++;
        }
        porCondicion[pacientes[i].condicion]++;
    }

    printf("\nHombres: %.2f%%\n", 100.0 * hombres / cantidad);
    printf("Mujeres: %.2f%%\n", 100.0 * (cantidad - hombres) / cantidad);

    puts("\nPacientes por condicion");
    for (int condicion = 1; condicion <= MAX_CONDICION; condicion++) {
        printf("Condicion %d: %d\n", condicion, porCondicion[condicion]);
    }

    puts("\nPacientes con condicion 5");
    if (porCondicion[5] == 0) {
        puts("Ninguno.");
    }
    for (int i = 0; i < cantidad; i++) {
        if (pacientes[i].condicion == 5) {
            printf("%s | %s\n", pacientes[i].nombre, pacientes[i].telefono);
        }
    }

    return 0;
}
