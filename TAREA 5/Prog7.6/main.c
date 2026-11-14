#include <stdio.h>
#include <string.h>

int main(void) {
    const char saludo[] = "Hola Mexico";
    const char mensaje[] = ", buenos dias";
    char completa[40];
    char parcial[40];

    strcpy(completa, saludo);
    printf("Copia completa: %s\n", completa);

    strncpy(parcial, saludo, 4);
    parcial[4] = '\0';
    printf("Copia parcial: %s\n", parcial);

    strcat(completa, mensaje);
    printf("Union completa: %s\n", completa);

    strncat(parcial, " mundo entero", 6);
    printf("Union parcial: %s\n", parcial);

    return 0;
}
