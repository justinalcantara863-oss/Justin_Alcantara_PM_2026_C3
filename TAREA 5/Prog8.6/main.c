#include <limits.h>
#include <stdio.h>

enum { MAX_PRODUCTOS = 100 };

typedef struct {
    int clave;
    char nombre[60];
    double precio;
    int existencia;
} Producto;

int buscarPosicion(const Producto inventario[], int total, int clave) {
    int posicion = 0;

    while (posicion < total && inventario[posicion].clave < clave) {
        posicion++;
    }

    return posicion;
}

int agregarProductos(Producto inventario[], int *total) {
    for (;;) {
        Producto nuevo;

        printf("Clave nueva (0 para volver): ");
        if (scanf("%9d", &nuevo.clave) != 1) {
            return 0;
        }
        if (nuevo.clave == 0) {
            return 1;
        }

        int posicion = buscarPosicion(inventario, *total, nuevo.clave);
        if (nuevo.clave < 0) {
            puts("La clave debe ser positiva.");
            continue;
        }
        if (posicion < *total && inventario[posicion].clave == nuevo.clave) {
            puts("Esa clave ya existe.");
            continue;
        }
        if (*total == MAX_PRODUCTOS) {
            puts("El inventario esta lleno.");
            return 1;
        }

        printf("Nombre: ");
        if (scanf(" %59[^\n]", nuevo.nombre) != 1) {
            return 0;
        }
        printf("Precio: ");
        if (scanf("%lf", &nuevo.precio) != 1) {
            return 0;
        }
        printf("Existencia inicial: ");
        if (scanf("%9d", &nuevo.existencia) != 1) {
            return 0;
        }

        if (!(nuevo.precio > 0 && nuevo.precio <= 1000000000.0) ||
            nuevo.existencia < 0) {
            puts("Precio o existencia fuera de rango.");
            continue;
        }

        for (int i = *total; i > posicion; i--) {
            inventario[i] = inventario[i - 1];
        }
        inventario[posicion] = nuevo;
        (*total)++;
        puts("Producto agregado.");
    }
}

int cambiarExistencias(Producto inventario[], int total, int esVenta) {
    double importe = 0.0;

    for (;;) {
        int clave;
        printf("Clave del producto (0 para terminar): ");
        if (scanf("%9d", &clave) != 1) {
            return 0;
        }
        if (clave == 0) {
            if (esVenta) {
                printf("Total de la venta: %.2f\n", importe);
            }
            return 1;
        }

        int posicion = buscarPosicion(inventario, total, clave);
        if (posicion == total || inventario[posicion].clave != clave) {
            puts("Producto no encontrado.");
            continue;
        }

        int cantidad;
        printf("Cantidad: ");
        if (scanf("%9d", &cantidad) != 1) {
            return 0;
        }
        if (cantidad <= 0) {
            puts("La cantidad debe ser positiva.");
            continue;
        }

        Producto *producto = &inventario[posicion];
        if (esVenta) {
            if (cantidad > producto->existencia) {
                puts("Existencia insuficiente.");
                continue;
            }
            producto->existencia -= cantidad;
            importe += cantidad * producto->precio;
        } else {
            if (cantidad > INT_MAX - producto->existencia) {
                puts("La cantidad excede el limite de existencias.");
                continue;
            }
            producto->existencia += cantidad;
        }

        printf("Existencia actual de %s: %d\n",
               producto->nombre, producto->existencia);
    }
}

void mostrarInventario(const Producto inventario[], int total) {
    if (total == 0) {
        puts("El inventario esta vacio.");
        return;
    }

    puts("Clave | Nombre | Precio | Existencia");
    for (int i = 0; i < total; i++) {
        printf("%d | %s | %.2f | %d\n", inventario[i].clave,
               inventario[i].nombre, inventario[i].precio,
               inventario[i].existencia);
    }
}

int main(void) {
    Producto inventario[MAX_PRODUCTOS];
    int total = 0;
    int correcto = 1;

    while (correcto) {
        int opcion;
        puts("\n1. Ventas\n2. Reabastecimiento\n3. Nuevos productos"
             "\n4. Inventario\n0. Salir");
        printf("Opcion: ");
        if (scanf("%2d", &opcion) != 1) {
            break;
        }

        switch (opcion) {
            case 0: return 0;
            case 1: correcto = cambiarExistencias(inventario, total, 1); break;
            case 2: correcto = cambiarExistencias(inventario, total, 0); break;
            case 3: correcto = agregarProductos(inventario, &total); break;
            case 4: mostrarInventario(inventario, total); break;
            default: puts("Opcion invalida.");
        }
    }

    puts("Entrada invalida.");
    return 1;
}
