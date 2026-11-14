#include <limits.h>
#include <stdio.h>

void convertirBase(unsigned long long numero, unsigned int base,
                   char resultado[]) {
    const char digitos[] = "0123456789ABCDEFGHIJ";
    size_t cantidad = 0;

    do {
        resultado[cantidad] = digitos[numero % base];
        cantidad++;
        numero /= base;
    } while (numero > 0);

    for (size_t i = 0; i < cantidad / 2; i++) {
        size_t opuesto = cantidad - 1 - i;
        char temporal = resultado[i];
        resultado[i] = resultado[opuesto];
        resultado[opuesto] = temporal;
    }

    resultado[cantidad] = '\0';
}

int main(void) {
    long long numero;
    int base;
    char resultado[sizeof(unsigned long long) * CHAR_BIT + 1];

    printf("Escribe un entero decimal mayor o igual a 0: ");
    if (scanf("%lld", &numero) != 1 || numero < 0) {
        printf("Numero invalido.\n");
        return 1;
    }

    printf("Escribe una base entre 2 y 20: ");
    if (scanf("%d", &base) != 1 || base < 2 || base > 20) {
        printf("Base invalida.\n");
        return 1;
    }

    convertirBase((unsigned long long)numero, (unsigned int)base, resultado);
    printf("Resultado en base %d: %s\n", base, resultado);

    return 0;
}
