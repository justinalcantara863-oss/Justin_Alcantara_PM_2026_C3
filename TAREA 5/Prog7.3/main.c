#include <stdio.h>
#include <string.h>

int main(void) {
    const char *saludo = "Buenos dias";
    char saludoCorto[20] = "Hola";
    char pais[] = "Mexico";
    char bienvenida[] = {'B', 'i', 'e', 'n', 'v', 'e', 'n', 'i', 'd', 'o', '\0'};

    puts(saludo);
    puts(saludoCorto);
    puts(pais);
    puts(bienvenida);

    char palabra[50];
    char frase[100];
    char texto[100];

    printf("Escribe una palabra: ");
    if (scanf("%49s", palabra) != 1) {
        return 1;
    }

    int caracter;
    while ((caracter = getchar()) != '\n' && caracter != EOF) {
    }

    printf("Escribe una frase: ");
    if (fgets(frase, sizeof frase, stdin) == NULL) {
        return 1;
    }
    frase[strcspn(frase, "\r\n")] = '\0';

    printf("Escribe otra frase: ");
    size_t longitud = 0;
    while ((caracter = getchar()) != '\n' && caracter != EOF) {
        if (longitud < sizeof texto - 1) {
            texto[longitud++] = (char)caracter;
        }
    }
    texto[longitud] = '\0';

    printf("\nPalabra: %s\n", palabra);
    printf("Primera frase: %s\n", frase);
    printf("Segunda frase: %s\n", texto);

    return 0;
}
