#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 100000000;
 
struct posible {int v, w, p;};


vector<int> dijkstra(int s, int n, vector<vector<pair<int, int>>>& grafo) {
    vector<int> D(n);
    for(int i = 0; i < n; i++) D[i] = INF;
    D[s] = 0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
    q.push({0,s});
 
    while(!q.empty()) {
        pair<int,int> p = q.top();
        q.pop();
 
        int u = p.second, dist = p.first;
        if(dist > D[u]) continue;
 
        for(pair<int,int> pr : grafo[u]) {
            int v = pr.first;
            int next_dist = dist + pr.second;
 
            if(next_dist < D[v]) {
                D[v] = next_dist;
                q.push({next_dist,v});
            }
        }
    }
    return D;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        int n, m, k, s, t; cin >> n >> m >> k >> s >> t;
        --s; --t;

        vector<vector<pair<int, int>>> grafo(n), grafoT(n);
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

        vector<int> ds = dijkstra(s, n, grafo); 
        vector<int> dt = dijkstra(t, n, grafoT);
        
        int mn = ds[t];
        for(posible b : posibles) {
            mn = min(mn, ds[b.v] + b.p + dt[b.w]); 
            mn = min(mn, ds[b.w] + b.p + dt[b.v]); 
        }

        cout << (mn < INF ? mn : -1) << endl;
    }
}
 