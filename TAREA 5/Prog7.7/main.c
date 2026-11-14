#include <stdio.h>
#include <string.h>

void comparar(const char izquierda[], const char derecha[]) {
    int orden = strcmp(izquierda, derecha);

    if (orden == 0) {
        printf("\"%s\" y \"%s\" son iguales.\n", izquierda, derecha);
    } else {
        printf("\"%s\" va %s de \"%s\".\n",
               izquierda, orden < 0 ? "antes" : "despues", derecha);
    }
}

int main(void) {
    const char texto[] = "Hola Mexico";

    comparar(texto, "Hola Guatemala");
    comparar(texto, "Hola Venezuela");
    comparar(texto, "Hola Mexico");

    printf("Longitud de \"%s\": %zu\n", texto, strlen(texto));

    const char *encontrado = strchr(texto, 'M');
    if (encontrado != NULL) {
        printf("La M esta en la posicion %zu.\n",
               (size_t)(encontrado - texto) + 1);
        printf("Texto desde la M: %s\n", encontrado);
    }

    if (strchr(texto, 'z') == NULL) {
        puts("La z no aparece en el texto.");
    }

    return 0;
}
