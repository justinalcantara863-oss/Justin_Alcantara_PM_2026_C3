#include <stdio.h>
#include <string.h>

enum { MAX_TEXTO = 50 };

void imprimirInvertido(const char texto[]) {
    if (texto[0] == '\0') {
        return;
    }

    imprimirInvertido(texto + 1);
    putchar((unsigned char)texto[0]);
}

int main(void) {
    char texto[MAX_TEXTO + 3];

    printf("Escribe una linea de hasta 50 caracteres: ");
    if (fgets(texto, sizeof texto, stdin) == NULL) {
        return 1;
    }

    size_t longitud = strcspn(texto, "\r\n");
    if (longitud > MAX_TEXTO) {
        puts("La linea es demasiado larga.");
        return 1;
    }

    texto[longitud] = '\0';

    printf("Texto invertido: ");
    imprimirInvertido(texto);
    putchar('\n');

    return 0;
}
