/*
 * Ordenamiento con TORRES DE HANOI.
 * Los numeros son discos. Torre A = origen, B = torre ordenada, C = auxiliar.
 * Regla de Hanoi: nunca un disco mayor sobre uno menor, asi que B siempre
 * tiene el menor arriba. Para colocar un disco se mueven a C los discos
 * menores que estorban, se coloca, y se regresan a B.
 */
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

constexpr int MAX_NUMEROS = 100000;

struct Torre {
    vector<int> discos;                              // base -> tope
    bool vacia() const { return discos.empty(); }
    int tope() const { return discos.back(); }
};

static unsigned long long comparaciones = 0, movimientos = 0;

static void mover(Torre& origen, Torre& destino) {   // un movimiento de disco
    destino.discos.push_back(origen.discos.back());
    origen.discos.pop_back();
    movimientos++;
}

int main() {
    int n;
    cout << "Cuantos numeros desea ordenar (1 - " << MAX_NUMEROS << ")? ";
    if (!(cin >> n) || n < 1 || n > MAX_NUMEROS) {
        cout << "Cantidad invalida. Debe estar entre 1 y " << MAX_NUMEROS << ".\n";
        return 1;
    }

    Torre A, B, C;
    A.discos.reserve(n); B.discos.reserve(n); C.discos.reserve(n);

    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(1, 100000);
    for (int i = 0; i < n; i++) A.discos.push_back(dist(gen));

    if (n <= 20) {
        cout << "\nTorre A (original, base->tope): ";
        for (int x : A.discos) cout << x << ' ';
        cout << '\n';
    }

    auto t0 = chrono::steady_clock::now();           // inicia SOLO el ordenamiento
    while (!A.vacia()) {
        int v = A.tope();
        while (!B.vacia()) {                         // despejar menores a C
            comparaciones++;
            if (B.tope() < v) mover(B, C);
            else break;
        }
        mover(A, B);                                 // colocar v
        while (!C.vacia()) mover(C, B);              // regresar los menores
    }
    auto t1 = chrono::steady_clock::now();           // termina el ordenamiento

    vector<int> salida(B.discos.rbegin(), B.discos.rend());  // tope (menor) -> base

    if (n <= 20) {
        cout << "Ordenado (menor a mayor)      : ";
        for (int x : salida) cout << x << ' ';
        cout << '\n';
    }
    for (int i = 0; i + 1 < n; i++)
        if (salida[i] > salida[i + 1]) { cout << "ERROR: no esta ordenado\n"; return 1; }

    cout << "\n--- Resultados (Ordenamiento con Torres de Hanoi) ---\n"
         << "Numeros ordenados   : " << n << '\n'
         << "Comparaciones       : " << comparaciones << '\n'
         << "Movimientos (disco) : " << movimientos << '\n'
         << "Tiempo ordenando    : " << chrono::duration<double>(t1 - t0).count()
         << " segundos\n";
    return 0;
}