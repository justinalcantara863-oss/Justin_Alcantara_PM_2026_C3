#include <stdio.h>
#include <string.h>

int main(void) {
    const char *pais = "Argentina";
    puts(pais);

    pais = "Brasil";
    puts(pais);

    char destino[20] = "Mexico";
    printf("Valor inicial del arreglo: %s\n", destino);

    printf("Escribe otro pais (hasta 19 caracteres): ");
    if (fgets(destino, sizeof destino, stdin) == NULL) {
        return 1;
    }

    destino[strcspn(destino, "\r\n")] = '\0';
    printf("Nuevo valor del arreglo: %s\n", destino);

    return 0;
}
