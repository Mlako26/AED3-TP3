#include <iostream>
#include <vector>
#include <numeric>
#include <stack>

using namespace std;

struct solucion {
    vector<bool> nodos;
    int size;
};

int cfc = 1;

void dfs(int root, vector<vector<int>>& aristas, vector<int>& visited, vector<int>& s, bool kosaraju) {
    vector<int> pila = {root};
    vector<int> next(aristas.size(), 0); 
    visited[root] = cfc;

    while (pila.size()) { 
        int v = pila.back();
        visited[v] = cfc;

        if (next[v] == aristas[v].size()) {
            if (kosaraju) s.push_back(v);
            pila.pop_back();
        }

        while (next[v] < aristas[v].size()) {
            if (visited[aristas[v][next[v]]]){
                next[v]++;
            } else {
                pila.push_back(aristas[v][next[v]++]); 
                break;
            }
        }

    }
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, m; cin >> n >> m;
    vector<vector<int>> aristas(n);
    vector<vector<int>> aristasT(n);
    for (int i = 0; i < m; i++) {
        int v, u; cin >> v >> u;
        aristas[v-1].push_back(u-1);
        aristasT[u-1].push_back(v-1);
    }

    // Inicializamos el vector solucion con algunos nodos
    solucion res = {vector<bool>(n, false), 0};
    vector<int> visited(n, 0);
    vector<int> stack; stack.reserve(n);
    for (int i = 0; i < n; i++) {
        if (aristasT[i].size() == 0) { // Sabemos que no lo vamos a haber visitado; grado de entrada = 0
            res.nodos[i] = true; res.size++;
            dfs(i, aristas, visited, stack, false);
        }
    } 

    // Aplicamos Kosaraju
    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs(i, aristas, visited, stack, true);
    }

    vector<int> grupos(n, 0);
    while (stack.size()) {
        if (grupos[stack.back()] == 0){
            dfs(stack.back(), aristasT, grupos, stack, false);
            cfc++;
        }
        stack.pop_back();
    }

    vector<bool> valido(cfc, true);
    for (int v = 0; v < n; v++) {
        if (grupos[v] == 0 || !valido[grupos[v]]) continue;
        for (int u : aristasT[v]) {
            if (grupos[u] != grupos[v]) {
                valido[grupos[v]] = false;
                break;
            }
            if (u == aristasT[v].back()) {
                res.nodos[v] = true; res.size++;
                valido[grupos[v]] = false;
            }
        }
    }

    // Imprimimos solucion
    cout << res.size << endl;
    for (int i = 0; i < n; i++) {
        if (res.nodos[i]) cout << i+1 << " ";
    }
    cout << endl;

    return 0;
}