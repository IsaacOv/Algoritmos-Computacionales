/*
 * Ordenamiento por FACTORIALES (sistema numerico factoradico).
 * Se prueban las permutaciones k = 0, 1, 2, ..., n!-1. Cada k se convierte
 * a una permutacion usando los factoriales (codigo de Lehmer) y se revisa si
 * deja el arreglo ordenado de menor a mayor.
 * Complejidad O(n! * n^2): solo es practico para n pequeno.
 */
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

constexpr int MAX_NUMEROS = 10;   // 10! = 3,628,800; 100,000! es imposible

int main() {
    int n;
    cout << "Cuantos numeros desea ordenar (1 - " << MAX_NUMEROS << ")? ";
    if (!(cin >> n) || n < 1 || n > MAX_NUMEROS) {
        cout << "Cantidad invalida. Debe estar entre 1 y " << MAX_NUMEROS << ".\n";
        return 1;
    }

    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(1, 100);
    vector<int> arr(n), res(n);
    for (int& x : arr) x = dist(gen);

    cout << "\nArreglo original: ";
    for (int x : arr) cout << x << ' ';
    cout << '\n';

    vector<unsigned long long> fact(n + 1, 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;

    unsigned long long comparaciones = 0, intercambios = 0, intentos = 0, k;
    vector<int> disp(n);

    auto t0 = chrono::steady_clock::now();          // inicia SOLO el ordenamiento
    for (k = 0; k < fact[n]; k++) {
        intentos++;
        for (int i = 0; i < n; i++) disp[i] = i;
        unsigned long long resto = k;
        int quedan = n;
        for (int i = 0; i < n; i++) {
            unsigned long long q = resto / fact[n - 1 - i];
            resto %= fact[n - 1 - i];
            res[i] = arr[disp[q]];
            for (int j = (int)q; j < quedan - 1; j++) {
                disp[j] = disp[j + 1];              // corrimiento de un elemento
                intercambios++;
            }
            quedan--;
        }
        bool ok = true;
        for (int i = 0; i < n - 1; i++) {
            comparaciones++;
            if (res[i] > res[i + 1]) { ok = false; break; }
        }
        if (ok) break;
    }
    auto t1 = chrono::steady_clock::now();          // termina el ordenamiento

    cout << "Arreglo ordenado: ";
    for (int x : res) cout << x << ' ';
    cout << "\n\n--- Resultados (Ordenamiento por factoriales) ---\n"
         << "Numeros ordenados      : " << n << '\n'
         << "Total de permutaciones : " << n << "! = " << fact[n] << '\n'
         << "Permutaciones probadas : " << intentos << " (indice factoradico k = " << k << ")\n"
         << "Comparaciones          : " << comparaciones << '\n'
         << "Intercambios (corrim.) : " << intercambios << '\n'
         << "Tiempo ordenando       : " << chrono::duration<double>(t1 - t0).count()
         << " segundos\n";
    return 0;
}