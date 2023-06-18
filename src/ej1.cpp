#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int mxn = 1e8;

struct posible {int v, w, p;};

struct arista {
    int v, p;
    bool operator<(const arista &b) const {
        return p < b.p;
    }
};

vector<int> dijkstra(vector<vector<arista>>& grafo, int v, int n) {
    priority_queue<arista> heap;
    heap.push({v, 0});
    vector<int> dist(n, mxn);
    vector<bool> esta(n, false);
    dist[v] = 0;

    while(!heap.empty()) {
        int w = heap.top().v; heap.pop();
        if(esta[w]) continue;
        esta[w] = true;
        for(arista k : grafo[w]) {
            int p = k.p, u = k.v;
            if(dist[u] > dist[w] + p) {
                dist[u] = dist[w] + p;
                heap.push({u, -dist[u]});
            }
        }
    }

    return dist;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        int n, m, k, s, t; cin >> n >> m >> k >> s >> t;
        --s; --t;

        vector<vector<arista>> grafo(n), grafoT(n);
        for(int i = 0; i < m; ++i) {
            int v, w, p; cin >> v >> w >> p;
            grafo[v-1].push_back({w-1, p});
            grafoT[w-1].push_back({v-1, p});
        } 

        vector<posible> posibles;
        for(int i = 0 ; i < k; ++i) {
            int v, w, p; cin >> v >> w >> p;
            posibles.push_back({v-1, w-1, p});
        }

        vector<int> ds = dijkstra(grafo, s, n); 
        vector<int> dt = dijkstra(grafoT, t, n);
        
        int mn = ds[t];
        for(posible b : posibles) {
            mn = min(mn, ds[b.v] + b.p + dt[b.w]); 
            mn = min(mn, ds[b.w] + b.p + dt[b.v]); 
        }

        cout << (mn < mxn ? mn : -1) << endl;
    }
}