#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <numeric>

using namespace std;

//* Definiciones *//

struct coordenada {
    int x, y;
};

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        // Cargo entrada
        int N, R, W, U, V;
        cin >> N >> R >> W >> U >> V;

        vector<coordenada> pos(N);
        for(int i = 0; i < N; ++i) cin >> pos[i].x >> pos[i].y;

        // Dense Kruskal
        vector<vector<double>> adj(N, vector<double>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                double d = sqrt(pow(pos[i].x - pos[j].x, 2) + pow(pos[i].y - pos[j].y, 2));
                adj[i][j] = d;
                adj[j][i] = d;
            }
        }
        vector<bool> representante(N, true);
        vector<double> next(N, std::numeric_limits<double>::infinity());
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                next[i] = min(next[i], adj[i][j]);
            }
        }

        int faltan = N - W;
        double pU = 0, pV = 0;
        while (faltan--) {
            // Busco y sumo mejor arista
            int v = 0; 
            while (!representante[v]) v++;
            for (int i = v+1; i < N; ++i) {
                if (!representante[i]) continue;
                if (next[i] < next[v]) v = i;
            }
            if (next[v] <= R) pU += next[v];
            else pV += next[v];  

            // La quito y actualizo las aristas
            int u = 0;
            for (int i = 0; i < N; ++i) {
                if (!representante[i]) continue;
                if (adj[v][i] == next[v]) {u = i; break;}
            }
            representante[u] = false;
            next[v] = std::numeric_limits<double>::infinity();
            for (int i = 0; i < N; ++i) {
                if (!representante[i] || i == v) continue;
                adj[v][i] = min(adj[u][i], adj[v][i]);
                adj[i][v] = adj[v][i]; 
                next[v] = min(next[v], adj[v][i]);
            }
        }

        // Imprimo salida
        cout << setprecision(3) << fixed;
        cout << "Caso #"<< t << ": " << pU * U << " " << pV * V << endl;
    }

    
    return 0;
}