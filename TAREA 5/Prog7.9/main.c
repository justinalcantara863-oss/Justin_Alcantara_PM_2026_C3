#include <stdio.h>
#include <string.h>

enum { MAX_TEXTO = 50 };

int contarCaracter(const char texto[], char buscado) {
    int total = 0;

    for (size_t i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == buscado) {
            total++;
        }
    }

    return total;
}

int main(void) {
    char texto[MAX_TEXTO + 3];
    char entrada[8];

    printf("Escribe un texto de hasta 50 caracteres: ");
    if (fgets(texto, sizeof texto, stdin) == NULL) {
        return 1;
    }

    size_t longitud = strcspn(texto, "\r\n");
    if (longitud > MAX_TEXTO) {
        puts("El texto es demasiado largo.");
        return 1;
    }
    texto[longitud] = '\0';

    printf("Escribe el caracter que quieres buscar: ");
    if (fgets(entrada, sizeof entrada, stdin) == NULL ||
        strcspn(entrada, "\r\n") != 1) {
        puts("Ingresa un solo caracter.");
        return 1;
    }

    printf("El caracter '%c' aparece %d veces.\n",
           entrada[0], contarCaracter(texto, entrada[0]));

    return 0;
}
