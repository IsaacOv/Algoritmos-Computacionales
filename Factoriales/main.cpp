#include <cstdio>

int factorial(int n) {
    if (n < 0) {
        return -1;
    }
    else if (n == 0 || n == 1) {
        return 1;
    }
    else {
        return n* factorial(n-1);
    }
}

int main() {
    int numero;
    printf("- - - Factoriales - - -");
    while (1) {
        printf("\nIngresa el valor del factorial que quieres calcular: ");
        scanf("%d", &numero);
        int result = factorial(numero);

        if (result == -1) {
            printf("\nIngresa un numero positivo");
        }
        else {
            printf("El resultado es: %d", result);
            break;
        }
    }
    return 0;
    }
