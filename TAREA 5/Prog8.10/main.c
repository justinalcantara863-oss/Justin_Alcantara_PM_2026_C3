#include <math.h>
#include <stdio.h>
#include <string.h>

enum { MAX_VENDEDORES = 100, MESES = 12 };
enum { CHEQUES = 1, NOMINA = 2, VENTANILLA = 3 };

typedef struct {
    char banco[60];
    char numero[32];
} Cuenta;

typedef union {
    Cuenta cheques;
    Cuenta nomina;
    char ventanilla;
} FormaPago;

typedef struct {
    char calleYNumero[80];
    char colonia[60];
    char codigoPostal[16];
    char ciudad[60];
} Domicilio;

typedef struct {
    int numero;
    char nombre[64];
    double ventas[MESES];
    Domicilio domicilio;
    double salario;
    int clavePago;
    FormaPago pago;
} Vendedor;

int leerTexto(const char *mensaje, char *texto, int capacidad) {
    printf("%s", mensaje);
    if (fgets(texto, capacidad, stdin) == NULL) {
        return 0;
    }

    size_t longitud = strcspn(texto, "\r\n");
    if (texto[longitud] == '\0' && !feof(stdin)) {
        return 0;
    }

    texto[longitud] = '\0';
    return longitud > 0;
}

int leerEntero(const char *mensaje, int minimo, int maximo, int *valor) {
    char entrada[32];
    char extra;

    return leerTexto(mensaje, entrada, sizeof entrada) &&
           sscanf(entrada, "%9d %c", valor, &extra) == 1 &&
           *valor >= minimo && *valor <= maximo;
}

int leerMonto(const char *mensaje, double *monto) {
    char entrada[64];
    char extra;

    return leerTexto(mensaje, entrada, sizeof entrada) &&
           sscanf(entrada, "%lf %c", monto, &extra) == 1 &&
           isfinite(*monto) && *monto >= 0.0;
}

int leerVendedor(Vendedor *vendedor) {
    if (!leerEntero("Numero de vendedor: ", 1, 999999999,
                    &vendedor->numero) ||
        !leerTexto("Nombre y apellido: ", vendedor->nombre,
                   sizeof vendedor->nombre)) {
        return 0;
    }

    for (int mes = 0; mes < MESES; mes++) {
        printf("Mes %d. ", mes + 1);
        if (!leerMonto("Ventas: ", &vendedor->ventas[mes])) {
            return 0;
        }
    }

    Domicilio *domicilio = &vendedor->domicilio;
    if (!leerTexto("Calle y numero: ", domicilio->calleYNumero,
                   sizeof domicilio->calleYNumero) ||
        !leerTexto("Colonia o sector: ", domicilio->colonia,
                   sizeof domicilio->colonia) ||
        !leerTexto("Codigo postal: ", domicilio->codigoPostal,
                   sizeof domicilio->codigoPostal) ||
        !leerTexto("Ciudad: ", domicilio->ciudad, sizeof domicilio->ciudad) ||
        !leerMonto("Salario mensual: ", &vendedor->salario) ||
        !leerEntero("Pago (1 cheques, 2 nomina, 3 ventanilla): ",
                    CHEQUES, VENTANILLA, &vendedor->clavePago)) {
        return 0;
    }

    if (vendedor->clavePago == VENTANILLA) {
        vendedor->pago.ventanilla = 'V';
        return 1;
    }

    Cuenta *cuenta = vendedor->clavePago == CHEQUES
        ? &vendedor->pago.cheques : &vendedor->pago.nomina;

    return leerTexto("Banco: ", cuenta->banco, sizeof cuenta->banco) &&
           leerTexto("Numero de cuenta: ", cuenta->numero,
                     sizeof cuenta->numero);
}

double sumarVentas(const Vendedor *vendedor) {
    double total = 0.0;

    for (int mes = 0; mes < MESES; mes++) {
        total += vendedor->ventas[mes];
    }

    return total;
}

int main(void) {
    Vendedor vendedores[MAX_VENDEDORES];
    double totales[MAX_VENDEDORES];
    int cantidad;

    if (!leerEntero("Cuantos vendedores (1 a 100): ", 1, MAX_VENDEDORES,
                    &cantidad)) {
        puts("Cantidad invalida.");
        return 1;
    }

    for (int i = 0; i < cantidad; i++) {
        printf("\nVendedor %d\n", i + 1);
        if (!leerVendedor(&vendedores[i])) {
            puts("Datos invalidos.");
            return 1;
        }
        totales[i] = sumarVentas(&vendedores[i]);
    }

    puts("\nVentas anuales y salario mensual");
    for (int i = 0; i < cantidad; i++) {
        Vendedor *vendedor = &vendedores[i];
        if (totales[i] > 1500000.0) {
            vendedor->salario *= 1.05;
        }

        printf("%d | %s | Ventas: %.2f | Salario: %.2f\n",
               vendedor->numero, vendedor->nombre, totales[i],
               vendedor->salario);
    }

    puts("\nVendedores con ventas menores de 300000");
    for (int i = 0; i < cantidad; i++) {
        if (totales[i] < 300000.0) {
            printf("%d | %s | %.2f\n", vendedores[i].numero,
                   vendedores[i].nombre, totales[i]);
        }
    }

    puts("\nVendedores con cuenta de cheques");
    for (int i = 0; i < cantidad; i++) {
        if (vendedores[i].clavePago == CHEQUES) {
            printf("%d | %s | %s\n", vendedores[i].numero,
                   vendedores[i].pago.cheques.banco,
                   vendedores[i].pago.cheques.numero);
        }
    }

    return 0;
}
