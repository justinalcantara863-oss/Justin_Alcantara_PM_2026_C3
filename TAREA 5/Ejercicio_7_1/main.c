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
void quitarEspaciosInicio(const char texto[], char resultado[]) {
    size_t longitud = strlen(texto);
    size_t inicio = 0;

    while (inicio < longitud && texto[inicio] == ' ') {
        inicio++;
    }

    subcadena(texto, inicio, longitud - inicio, resultado);
}
void borrarDesde(const char texto[], size_t posicion, size_t cantidad,
                 char resultado[]) {
    size_t longitud = strlen(texto);

    if (posicion == 0 || posicion > longitud) {
        subcadena(texto, 0, longitud, resultado);
        return;
    }

    size_t inicio = posicion - 1;
    if (cantidad > longitud - inicio) {
        cantidad = longitud - inicio;
    }

    subcadena(texto, 0, inicio, resultado);
    subcadena(texto, inicio + cantidad, longitud - inicio - cantidad,
              resultado + inicio);
}
void borrarPrimeraAparicion(const char texto[], const char buscado[],
                           char resultado[]) {
    const char *encontrado = strstr(texto, buscado);

    if (encontrado == NULL || buscado[0] == '\0') {
        subcadena(texto, 0, strlen(texto), resultado);
        return;
    }

    size_t posicion = (size_t)(encontrado - texto) + 1;
    borrarDesde(texto, posicion, strlen(buscado), resultado);
}
void insertarCadena(const char texto[], const char inserto[],
                    size_t posicion, char resultado[]) {
    size_t longitud = strlen(texto);
    size_t longitudInserto = strlen(inserto);

    if (posicion == 0 || posicion > longitud + 1) {
        subcadena(texto, 0, longitud, resultado);
        return;
    }

    size_t inicio = posicion - 1;

    subcadena(texto, 0, inicio, resultado);
    subcadena(inserto, 0, longitudInserto, resultado + inicio);
    subcadena(texto, inicio, longitud - inicio,
              resultado + inicio + longitudInserto);
}
void reemplazarPrimeraAparicion(const char texto[], const char buscado[],
                                const char reemplazo[], char resultado[]) {
    size_t longitudTexto = strlen(texto);
    const char *encontrado = strstr(texto, buscado);

    if (encontrado == NULL || buscado[0] == '\0') {
        subcadena(texto, 0, longitudTexto, resultado);
        return;
    }

    size_t inicio = (size_t)(encontrado - texto);
    size_t fin = inicio + strlen(buscado);
    size_t longitudReemplazo = strlen(reemplazo);

    subcadena(texto, 0, inicio, resultado);
    subcadena(reemplazo, 0, longitudReemplazo, resultado + inicio);
    subcadena(texto, fin, longitudTexto - fin,
              resultado + inicio + longitudReemplazo);
}
size_t contarApariciones(const char texto[], const char buscado[]) {
    if (buscado[0] == '\0') {
        return 0;
    }

    size_t cantidad = 0;
    const char *inicio = texto;
    const char *encontrado;

    while ((encontrado = strstr(inicio, buscado)) != NULL) {
        cantidad++;
        inicio = encontrado + 1;
    }

    return cantidad;
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
        quitarEspaciosInicio("   Meca", resultado);
    printf("Sin espacios al principio: [%s]\n", resultado);
        borrarDesde("ABCDEF", 3, 2, resultado);
    printf("Despues de borrar: [%s]\n", resultado);
        borrarPrimeraAparicion("sol y sol", "sol", resultado);
    printf("Sin la primera aparicion: [%s]\n", resultado);
        insertarCadena("ABEF", "CD", 3, resultado);
    printf("Despues de insertar: [%s]\n", resultado);
        reemplazarPrimeraAparicion("sol y sol", "sol", "luna", resultado);
    printf("Despues de reemplazar: [%s]\n", resultado);
    size_t apariciones = contarApariciones("banana", "ana");
    printf("Apariciones de ana: %zu\n", apariciones);
    return 0;
}
