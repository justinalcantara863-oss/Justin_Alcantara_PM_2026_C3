#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ALMACEN "ALMACEN.dat"
#define PEDIDOS "PEDIDOS.txt"
#define TEMPORAL "PEDIDOS.tmp"

typedef struct {
    char codigo[32];
    char descripcion[100];
    char proveedor[100];
    double precio;
    int stockActual;
    int stockMaximo;
    int stockMinimo;
} Producto;

int main(void) {
    FILE *almacen = fopen(ALMACEN, "rb");
    if (almacen == NULL) {
        perror("No se pudo abrir ALMACEN.dat");
        return EXIT_FAILURE;
    }

    FILE *pedidos = fopen(TEMPORAL, "w");
    if (pedidos == NULL) {
        perror("No se pudo crear PEDIDOS.tmp");
        fclose(almacen);
        return EXIT_FAILURE;
    }

    Producto producto;
    size_t leidos;
    size_t total = 0;
    int correcto = 1;

    while ((leidos = fread(&producto, 1, sizeof producto, almacen)) ==
           sizeof producto) {
        if (producto.stockActual < producto.stockMinimo) {
            int cantidad = producto.stockMaximo - producto.stockActual;

            if (fprintf(pedidos, "%s\t%s\t%d\n",
                        producto.proveedor, producto.codigo, cantidad) < 0) {
                correcto = 0;
                break;
            }
            total++;
        }
    }

    if (ferror(almacen) || (leidos > 0 && leidos < sizeof producto)) {
        correcto = 0;
    }
    fclose(almacen);

    if (fclose(pedidos) != 0) {
        correcto = 0;
    }

    if (!correcto ||
        !MoveFileExA(TEMPORAL, PEDIDOS, MOVEFILE_REPLACE_EXISTING)) {
        remove(TEMPORAL);
        puts("No se pudo generar PEDIDOS.txt.");
        return EXIT_FAILURE;
    }

    printf("Pedidos generados: %zu\n", total);
    return EXIT_SUCCESS;
}
