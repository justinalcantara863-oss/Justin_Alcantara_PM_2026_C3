#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef struct {
    char codigo[32];
    char titulo[100];
    char autor[100];
    int precio;
} Libro;

int leerTexto(const char mensaje[], char texto[], int capacidad) {
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
    return texto[0] != '\0' && strchr(texto, '\t') == NULL;
}

int leerLibro(FILE *archivo, Libro *libro) {
    char linea[256];
    char extra;

    if (fgets(linea, sizeof linea, archivo) == NULL) {
        return ferror(archivo) ? -1 : 0;
    }

    return sscanf(linea, "%31[^\t]\t%99[^\t]\t%99[^\t]\t%d %c",
                  libro->codigo, libro->titulo, libro->autor,
                  &libro->precio, &extra) == 4 ? 1 : -1;
}

int escribirLibro(FILE *archivo, const Libro *libro) {
    return fprintf(archivo, "%s\t%s\t%s\t%d\n", libro->codigo,
                   libro->titulo, libro->autor, libro->precio) >= 0;
}

void consultar(const char codigo[]) {
    FILE *archivo = fopen("LIBROS.txt", "r");
    if (archivo == NULL) {
        if (errno == ENOENT) {
            puts("Todavia no hay libros.");
        } else {
            perror("No se pudo abrir LIBROS.txt");
        }
        return;
    }

    Libro libro;
    int estado;
    while ((estado = leerLibro(archivo, &libro)) == 1) {
        int comparacion = strcmp(libro.codigo, codigo);
        if (comparacion == 0) {
            printf("Codigo: %s\nTitulo: %s\nAutor: %s\nPrecio: %d\n",
                   libro.codigo, libro.titulo, libro.autor, libro.precio);
            fclose(archivo);
            return;
        }
        if (comparacion > 0) {
            break;
        }
    }

    fclose(archivo);
    puts(estado < 0 ? "Error al leer LIBROS.txt." : "Libro no encontrado.");
}

void insertar(const Libro *nuevo) {
    FILE *original = fopen("LIBROS.txt", "r");
    if (original == NULL && errno != ENOENT) {
        perror("No se pudo abrir LIBROS.txt");
        return;
    }

    FILE *temporal = fopen("LIBROS.tmp", "w");
    if (temporal == NULL) {
        perror("No se pudo crear LIBROS.tmp");
        if (original != NULL) {
            fclose(original);
        }
        return;
    }

    Libro actual;
    int estado = 0;
    int insertado = 0;
    int duplicado = 0;
    int correcto = 1;

    while (original != NULL && correcto &&
           (estado = leerLibro(original, &actual)) == 1) {
        int comparacion = strcmp(nuevo->codigo, actual.codigo);
        if (comparacion == 0) {
            duplicado = 1;
            break;
        }
        if (!insertado && comparacion < 0) {
            correcto = escribirLibro(temporal, nuevo);
            insertado = 1;
        }
        if (correcto) {
            correcto = escribirLibro(temporal, &actual);
        }
    }

    if (original != NULL) {
        fclose(original);
    }
    if (estado < 0) {
        correcto = 0;
    }
    if (correcto && !duplicado && !insertado) {
        correcto = escribirLibro(temporal, nuevo);
    }
    if (fclose(temporal) != 0) {
        correcto = 0;
    }

    if (duplicado || !correcto) {
        remove("LIBROS.tmp");
        puts(duplicado ? "Ese codigo ya existe." : "Error al guardar.");
        return;
    }

    if (!MoveFileExA("LIBROS.tmp", "LIBROS.txt", MOVEFILE_REPLACE_EXISTING)) {
        remove("LIBROS.tmp");
        puts("No se pudo actualizar LIBROS.txt.");
        return;
    }

    puts("Libro guardado.");
}

int main(void) {
    char opcion[16];

    for (;;) {
        puts("\n1. Insertar libro\n2. Consultar por codigo\n0. Salir");
        if (!leerTexto("Opcion: ", opcion, sizeof opcion) ||
            strcmp(opcion, "0") == 0) {
            return 0;
        }
        if (strcmp(opcion, "1") != 0 && strcmp(opcion, "2") != 0) {
            puts("Opcion invalida.");
            continue;
        }

        Libro libro;
        if (!leerTexto("Codigo: ", libro.codigo, sizeof libro.codigo)) {
            puts("Codigo invalido.");
            continue;
        }

        if (strcmp(opcion, "2") == 0) {
            consultar(libro.codigo);
            continue;
        }

        char precio[32];
        char extra;
        if (!leerTexto("Titulo: ", libro.titulo, sizeof libro.titulo) ||
            !leerTexto("Autor: ", libro.autor, sizeof libro.autor) ||
            !leerTexto("Precio entero: ", precio, sizeof precio) ||
            sscanf(precio, "%d %c", &libro.precio, &extra) != 1 ||
            libro.precio < 0) {
            puts("Datos invalidos.");
            continue;
        }

        insertar(&libro);
    }
}
