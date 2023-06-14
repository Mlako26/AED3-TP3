#include <iomanip>
#include <iostream>
#include <vector>

#define ll long long

using namespace std;

vector<vector<int>> aristas;
vector<int> componentes = {};
int obtenerPuentes(int v, int p, int lvl, vector<int>& nivel, vector<int>& familia) {
    int minlvl = lvl;  // Por defecto llego a mi propio nivel
    nivel[v] = lvl;

    for (int u : aristas[v]) {
        if (u == p) continue;
        if (nivel[u] == -1) {
            minlvl = min(minlvl, obtenerPuentes(u, v, lvl + 1, nivel, familia));
            familia[v] += familia[u];
        } else minlvl = min(minlvl, nivel[u]);
    }
    if (minlvl >= lvl) {
        componentes.push_back(familia[v]);
        if (p > -1) familia[p] -= familia[v];
    }
    return minlvl;
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // Cargo Entrada
    int N, M;
    cin >> N >> M;

    aristas.resize(N);
    for (int i = 0; i < M; ++i) {
        int v, w;
        cin >> v >> w;
        aristas[v - 1].push_back(w - 1);
        aristas[w - 1].push_back(v - 1);
    }

    vector<int> nivel(N, -1), familia(N, 1);
    obtenerPuentes(0, -1, 0, nivel, familia);

    float p = 0;
    for (int X : componentes) p += (float)X / (float)N * (float)(X - 1) / (float)(N - 1);

    // Imprimo salida
    cout << setprecision(5) << fixed;
    cout << 1 - p << endl;

    return 0;
}