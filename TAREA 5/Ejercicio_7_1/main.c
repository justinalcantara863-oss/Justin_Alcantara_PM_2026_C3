#include <stdio.h>
#include <string.h>

void subcadena(const char texto[], size_t inicio, size_t cantidad,
               char resultado[]) {
    for (size_t i = 0; i < cantidad; i++) {
        resultado[i] = texto[inicio + i];
    }
    resultado[cantidad] = '\0';
}

void primeros(const char texto[], size_t n, char resultado[]) {
    size_t longitud = strlen(texto);
    if (n > longitud) {
        n = longitud;
    }
    subcadena(texto, 0, n, resultado);
}

void ultimos(const char texto[], size_t n, char resultado[]) {
    size_t longitud = strlen(texto);
    if (n > longitud) {
        n = longitud;
    }
    subcadena(texto, longitud - n, n, resultado);
}
void quitarEspaciosFinal(const char texto[], char resultado[]) {
    size_t longitud = strlen(texto);

    while (longitud > 0 && texto[longitud - 1] == ' ') {
        longitud--;
    }

    subcadena(texto, 0, longitud, resultado);
}
int main(void) {
    const char texto[] = "Mecatronica";
    char resultado[sizeof texto];

    primeros(texto, 4, resultado);
    printf("Primeros: %s\n", resultado);

    ultimos(texto, 4, resultado);
    printf("Ultimos: %s\n", resultado);
    quitarEspaciosFinal("Meca   ", resultado);
    printf("Sin espacios al final: [%s]\n", resultado);
    return 0;
}
