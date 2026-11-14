#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *archivo = fopen("PEDIDOS.txt", "r");
    if (archivo == NULL) {
        perror("No se pudo abrir PEDIDOS.txt");
        return 1;
    }

    char linea[160];
    char proveedorAnterior[100] = "";
    size_t pedidosDelProveedor = 0;

    while (fgets(linea, sizeof linea, archivo) != NULL) {
        char proveedor[100];
        char codigo[32];
        char extra;
        int cantidad;

        if (sscanf(linea, "%99[^\t]\t%31[^\t]\t%d %c",
                   proveedor, codigo, &cantidad, &extra) != 3) {
            fprintf(stderr, "Registro invalido en PEDIDOS.txt.\n");
            fclose(archivo);
            return 1;
        }

        int orden = strcmp(proveedor, proveedorAnterior);
        if (pedidosDelProveedor > 0 && orden < 0) {
            fprintf(stderr, "PEDIDOS.txt debe estar ordenado por proveedor.\n");
            fclose(archivo);
            return 1;
        }

        if (pedidosDelProveedor == 0 || orden != 0) {
            if (pedidosDelProveedor > 0) {
                printf("Numero de pedidos: %zu\n\n", pedidosDelProveedor);
            }

            strcpy(proveedorAnterior, proveedor);
            printf("Proveedor: %s\n", proveedor);
            puts("Codigo producto\tCantidad a pedir");
            pedidosDelProveedor = 0;
        }

        printf("%s\t\t%d\n", codigo, cantidad);
        pedidosDelProveedor++;
    }

    if (ferror(archivo)) {
        perror("Error al leer PEDIDOS.txt");
        fclose(archivo);
        return 1;
    }
    fclose(archivo);

    if (pedidosDelProveedor > 0) {
        printf("Numero de pedidos: %zu\n", pedidosDelProveedor);
    } else {
        puts("No hay pedidos.");
    }

    return 0;
}
