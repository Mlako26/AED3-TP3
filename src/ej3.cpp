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

struct arista {
    int u, v;
    double d;
};

bool comp(const arista& a, const arista& b){
    return a.d < b.d;
};

class dsu {
   public:
    vector<int> p;
    int n;

    dsu(int _n) : n(_n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
    }

    inline int get(int x) {
        return (x == p[x] ? x : (p[x] = get(p[x])));
    }

    inline bool unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (x != y) {
            p[x] = y;
            return true;
        }
        return false;
    }
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

        // Genero y ordeno aristas pesadas
        vector<arista> aristas;
        aristas.reserve((N *(N-1)) / 2);
        for(int i = 0; i < N; ++i) {
            for(int j = i+1; j < N; ++j) {
                double d = sqrt(pow(pos[i].x - pos[j].x, 2) + pow(pos[i].y - pos[j].y, 2));
                aristas.push_back({i, j, d});
            }
        }
    
        sort(aristas.begin(), aristas.end(), comp);

        // N-W iteraciones de Kruskal
        dsu grupos(N);
        double pU = 0, pV = 0;
        int faltan = N - W;
        for(arista a : aristas) {
            if(grupos.get(a.u) != grupos.get(a.v)) {
                grupos.unite(a.u, a.v);
                if(a.d <= R) pU += a.d;
                else        pV += a.d;
                if(--faltan == 0) break;
            }
        }

        // Imprimo salida
        cout << setprecision(3) << fixed;
        cout << "Caso #"<< t << ": " << pU * U << " " << pV * V << endl;
    }

    
    return 0;
}