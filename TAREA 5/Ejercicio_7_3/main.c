#include <ctype.h>
#include <stdio.h>

void convertirMayusculas(const char texto[], char resultado[]) {
    size_t i = 0;

    while (texto[i] != '\0') {
        resultado[i] = (char)toupper((unsigned char)texto[i]);
        i++;
    }

    resultado[i] = '\0';
}

void convertirMinusculas(const char texto[], char resultado[]) {
    size_t i = 0;

    while (texto[i] != '\0') {
        resultado[i] = (char)tolower((unsigned char)texto[i]);
        i++;
    }

    resultado[i] = '\0';
}

int main(void) {
    const char texto[] = "Hola Mundo";
    char resultado[sizeof texto];

    convertirMayusculas(texto, resultado);
    printf("Mayusculas: %s\n", resultado);

    convertirMinusculas(texto, resultado);
    printf("Minusculas: %s\n", resultado);

    return 0;
}
