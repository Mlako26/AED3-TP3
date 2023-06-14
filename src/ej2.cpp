#include <iostream>
#include <vector>
#include <numeric>
#include <stack>

using namespace std;

struct solucion {
    vector<bool> nodos;
    int size;
    void add(int v) {
        nodos[v] = true;
        ++size;
    }
};

int cfc = 1;
void dfs(int v, vector<vector<int>>& aristas, vector<int>& visited, vector<int>& stack, bool kosaraju) {
    visited[v] = cfc;
    for (int u : aristas[v])
        if (!visited[u]) dfs(u, aristas, visited, stack, kosaraju);

    if (kosaraju) stack.push_back(v);
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
            res.add(i);
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

    vector<int> representante(cfc, -1);
    representante[0] = -2;
    for (int v = 0; v < n; v++) {
        if (representante[grupos[v]] == -2) continue;
        if(representante[grupos[v]] == -1) representante[grupos[v]] = v;

        for (int u : aristasT[v]) {
            if (grupos[u] != grupos[v]) {
                representante[grupos[v]] = -2;
                break;
            }
        }
    }

    for(int v : representante) if(v >= 0) res.add(v);

    // Imprimimos solucion
    cout << res.size << endl;
    for (int i = 0; i < n; i++) {
        if (res.nodos[i]) cout << i+1 << " ";
    }
    cout << endl;

    return 0;
}