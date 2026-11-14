#include <stdio.h>
#include <string.h>
#include <windows.h>

#define ARCHIVO "ALMACEN.dat"
#define TEMPORAL "ALMACEN.tmp"

typedef struct {
    char codigo[32];
    char descripcion[100];
    char proveedor[100];
    double precio;
    int stockActual;
    int stockMaximo;
    int stockMinimo;
} Producto;

int leerTexto(const char *mensaje, char *texto, size_t capacidad) {
    printf("%s", mensaje);
    if (fgets(texto, capacidad, stdin) == NULL) {
        return 0;
    }

    size_t fin = strcspn(texto, "\r\n");
    if (texto[fin] == '\0' && !feof(stdin)) {
        int caracter;
        while ((caracter = getchar()) != '\n' && caracter != EOF) {
        }
        return 0;
    }

    texto[fin] = '\0';
    return fin > 0;
}

int leerDatos(Producto *producto) {
    char entrada[100];
    char extra;

    return leerTexto("Descripcion: ", producto->descripcion,
                     sizeof producto->descripcion) &&
           leerTexto("Proveedor: ", producto->proveedor,
                     sizeof producto->proveedor) &&
           leerTexto("Precio (ejemplo: 150.50): ", entrada, sizeof entrada) &&
           sscanf(entrada, "%lf %c", &producto->precio, &extra) == 1 &&
           producto->precio >= 0 &&
           leerTexto("Stock actual, maximo y minimo (ejemplo: 10 20 2): ",
                     entrada, sizeof entrada) &&
           sscanf(entrada, "%d %d %d %c", &producto->stockActual,
                  &producto->stockMaximo, &producto->stockMinimo, &extra) == 3 &&
           producto->stockActual >= 0 &&
           producto->stockMinimo >= 0 &&
           producto->stockMaximo >= producto->stockMinimo;
}

void crearArchivo(void) {
    FILE *archivo = fopen(ARCHIVO, "ab");

    if (archivo == NULL) {
        perror("No se pudo crear el archivo");
        return;
    }

    if (fclose(archivo) == 0) {
        puts("Archivo de almacen listo.");
    } else {
        perror("No se pudo cerrar el archivo");
    }
}

void consultar(int porCodigo) {
    char buscado[100];
    if (!leerTexto(porCodigo ? "Codigo: " : "Descripcion: ",
                   buscado, sizeof buscado)) {
        puts("Busqueda invalida.");
        return;
    }

    FILE *archivo = fopen(ARCHIVO, "rb");
    if (archivo == NULL) {
        puts("Primero crea el archivo con la opcion 1.");
        return;
    }

    Producto producto;
    int encontrado = 0;

    while (fread(&producto, 1, sizeof producto, archivo) == sizeof producto) {
        const char *campo = porCodigo ? producto.codigo : producto.descripcion;
        if (strcmp(campo, buscado) == 0) {
            printf("%s | %s | %s | Precio: %.2f | Stock actual/max/min: %d/%d/%d\n",
                   producto.codigo, producto.descripcion, producto.proveedor,
                   producto.precio, producto.stockActual,
                   producto.stockMaximo, producto.stockMinimo);
            encontrado = 1;
        }
    }

    if (ferror(archivo)) {
        puts("Error al leer el archivo.");
    } else if (!encontrado) {
        puts("Producto no encontrado.");
    }
    fclose(archivo);
}

void actualizar(char opcion) {
    Producto nuevo = {0};
    if (!leerTexto("Codigo del producto: ", nuevo.codigo, sizeof nuevo.codigo)) {
        puts("Codigo invalido.");
        return;
    }

    if (opcion != '5' && !leerDatos(&nuevo)) {
        puts("Datos invalidos.");
        return;
    }

    FILE *original = fopen(ARCHIVO, "rb");
    if (original == NULL) {
        puts("Primero crea el archivo con la opcion 1.");
        return;
    }

    FILE *temporal = fopen(TEMPORAL, "wb");
    if (temporal == NULL) {
        perror("No se pudo crear el archivo temporal");
        fclose(original);
        return;
    }

    Producto actual;
    size_t leidos = 0;
    int encontrado = 0;
    int correcto = 1;

    while ((leidos = fread(&actual, 1, sizeof actual, original)) == sizeof actual) {
        if (strcmp(actual.codigo, nuevo.codigo) == 0) {
            encontrado = 1;
            if (opcion == '4') {
                break;
            }
            if (opcion == '5') {
                continue;
            }
            actual = nuevo;
        }

        if (fwrite(&actual, sizeof actual, 1, temporal) != 1) {
            correcto = 0;
            break;
        }
    }

    if (ferror(original) || (leidos > 0 && leidos < sizeof actual)) {
        correcto = 0;
    }
    fclose(original);

    if (correcto && opcion == '4' && !encontrado) {
        correcto = fwrite(&nuevo, sizeof nuevo, 1, temporal) == 1;
    }
    if (fclose(temporal) != 0) {
        correcto = 0;
    }

    const char *mensaje = NULL;
    if (!correcto) {
        mensaje = "Error al guardar los cambios.";
    } else if (opcion == '4' && encontrado) {
        mensaje = "Ese codigo ya existe.";
    } else if (opcion != '4' && !encontrado) {
        mensaje = "Producto no encontrado.";
    } else if (!MoveFileExA(TEMPORAL, ARCHIVO, MOVEFILE_REPLACE_EXISTING)) {
        mensaje = "No se pudo actualizar el archivo.";
    }

    if (mensaje != NULL) {
        remove(TEMPORAL);
        puts(mensaje);
        return;
    }

    puts("Cambio guardado.");
}

int main(void) {
    char opcion[16];

    for (;;) {
        puts("\n1. Crear archivo\n2. Consultar por codigo"
             "\n3. Consultar por descripcion\n4. Agregar producto"
             "\n5. Eliminar producto\n6. Modificar producto\n0. Salir");

        if (!leerTexto("Opcion: ", opcion, sizeof opcion)) {
            if (feof(stdin) || ferror(stdin)) {
                return 0;
            }
            puts("Opcion invalida.");
            continue;
        }

        if (opcion[1] != '\0') {
            puts("Opcion invalida.");
            continue;
        }

        switch (opcion[0]) {
            case '0': return 0;
            case '1': crearArchivo(); break;
            case '2': consultar(1); break;
            case '3': consultar(0); break;
            case '4':
            case '5':
            case '6': actualizar(opcion[0]); break;
            default: puts("Opcion invalida.");
        }
    }
}
