#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

enum { MAX_PROPIEDADES = 100, TAM_TEXTO = 80 };

typedef struct {
    char zona[TAM_TEXTO];
    char calle[TAM_TEXTO];
    char colonia[TAM_TEXTO];
} Ubicacion;

typedef struct {
    char clave[20];
    double superficieCubierta;
    double superficieTerreno;
    char caracteristicas[160];
    Ubicacion ubicacion;
    double precio;
    char disponibilidad;
} Propiedad;

int leerTexto(const char *mensaje, char *texto, int capacidad) {
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

int leerReal(const char *mensaje, double *valor) {
    char linea[64];
    char extra;

    return leerTexto(mensaje, linea, sizeof linea) &&
           sscanf(linea, "%lf %c", valor, &extra) == 1 &&
           isfinite(*valor) && *valor >= 0.0;
}

int leerPropiedad(Propiedad *propiedad) {
    char linea[16];
    char extra;

    if (!leerTexto("Clave: ", propiedad->clave, sizeof propiedad->clave) ||
        !leerReal("Superficie cubierta: ", &propiedad->superficieCubierta) ||
        !leerReal("Superficie del terreno: ", &propiedad->superficieTerreno) ||
        !leerTexto("Caracteristicas: ", propiedad->caracteristicas,
                   sizeof propiedad->caracteristicas) ||
        !leerTexto("Zona: ", propiedad->ubicacion.zona,
                   sizeof propiedad->ubicacion.zona) ||
        !leerTexto("Calle: ", propiedad->ubicacion.calle,
                   sizeof propiedad->ubicacion.calle) ||
        !leerTexto("Colonia: ", propiedad->ubicacion.colonia,
                   sizeof propiedad->ubicacion.colonia) ||
        !leerReal("Precio en soles: ", &propiedad->precio) ||
        !leerTexto("Disponibilidad (V para venta, R para renta): ",
                   linea, sizeof linea) ||
        sscanf(linea, " %c %c", &propiedad->disponibilidad, &extra) != 1) {
        return 0;
    }

    propiedad->disponibilidad =
        (char)toupper((unsigned char)propiedad->disponibilidad);
    return propiedad->disponibilidad == 'V' || propiedad->disponibilidad == 'R';
}

int mismaZona(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0' &&
           tolower((unsigned char)*a) == tolower((unsigned char)*b)) {
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

void mostrarListado(const Propiedad propiedades[], int cantidad,
                    char disponibilidad, const char *zona,
                    double minimo, double maximo) {
    int encontrados = 0;

    for (int i = 0; i < cantidad; i++) {
        const Propiedad *p = &propiedades[i];

        if (p->disponibilidad == disponibilidad &&
            mismaZona(p->ubicacion.zona, zona) &&
            p->precio >= minimo && p->precio <= maximo) {
            printf("%s | Cubierta: %.2f | Terreno: %.2f | %s | %s | %s | S/ %.2f\n",
                   p->clave, p->superficieCubierta, p->superficieTerreno,
                   p->caracteristicas, p->ubicacion.calle,
                   p->ubicacion.colonia, p->precio);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        puts("No se encontraron propiedades.");
    }
}

int main(void) {
    Propiedad propiedades[MAX_PROPIEDADES];
    char linea[32];
    char extra;
    int cantidad;

    if (!leerTexto("Cuantas propiedades (1 a 100): ", linea, sizeof linea) ||
        sscanf(linea, "%3d %c", &cantidad, &extra) != 1 ||
        cantidad < 1 || cantidad > MAX_PROPIEDADES) {
        puts("Cantidad invalida.");
        return 1;
    }

    for (int i = 0; i < cantidad; i++) {
        printf("\nPropiedad %d\n", i + 1);
        if (!leerPropiedad(&propiedades[i])) {
            puts("Datos invalidos.");
            return 1;
        }
    }

    puts("\nVentas en Miraflores entre S/ 450000 y S/ 650000");
    mostrarListado(propiedades, cantidad, 'V', "Miraflores", 450000, 650000);

    char zona[TAM_TEXTO];
    double minimo, maximo;

    if (!leerTexto("\nZona para buscar alquiler: ", zona, sizeof zona) ||
        !leerReal("Precio minimo: ", &minimo) ||
        !leerReal("Precio maximo: ", &maximo) || minimo > maximo) {
        puts("Zona o rango invalido.");
        return 1;
    }

    printf("\nAlquileres en %s\n", zona);
    mostrarListado(propiedades, cantidad, 'R', zona, minimo, maximo);
    return 0;
}
