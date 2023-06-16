#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


using namespace std;

struct arista {int v, p;};

struct posible {int v, w, p;};

bool comp(const arista& a, const arista& b){
    return (a.p < b.p);
}

vector<int> dijkstra(vector<vector<arista>>& grafo, int v, int n) {
    priority_queue<arista> heap;
    heap.push({v, 0});

    vector<int> dist(n, INT32_MAX);
    vector<bool> esta(n, false);

    while(!heap.empty()) {
        arista w = heap.top(); // Get the node with the smallest distance
        heap.pop();

        if(esta[w.v]) continue;

        esta[w.v] = true;
        for(arista k : grafo[w.v]) {
            if(esta[k.v]) continue;
            k.p += dist[w.v];
            if(dist[k.v] > k.p) {
                heap.push(k);
                dist[k.v] = k.p;
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
        if(ds[t] == INT32_MAX) {
            cout << -1 << endl;
            continue;
        }

        vector<int> dt = dijkstra(grafoT, t, n);

        int mn = ds[t];
        for(posible b : posibles) {
            mn = min(mn, ds[b.v] + b.p + dt[b.w]); 
            mn = min(mn, ds[b.w] + b.p + dt[b.v]); 
        }

        cout << mn << endl;
    }
}
 