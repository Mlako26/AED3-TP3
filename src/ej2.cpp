#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int INF = 1e8;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t, int n) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}



int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    while(true) {
        int n, m; scanf("%d %d", &n, &m);
        if(n == 0 && m == 0) break;

        vector<vector<int>> grafo(n+2);
        vector<vector<int>> capacidades(n+2, vector<int>(n+2, 0));

        for(int i = 1; i <= n; ++i) {
            int k; scanf("%d", &k); k *= n + 1;
            grafo[k].push_back(i);
            grafo[i].push_back(k);
            capacidades[i][k] = 1;
            capacidades[k][i] = 1;
        }


        for(int i = 0; i < m; ++i) {
            int v, w; scanf("%d %d", &v, &w);
            grafo[v].push_back(w);
            grafo[w].push_back(v);
            capacidades[v][w] = 1;
            capacidades[w][v] = 1;
        } 
        adj = grafo;
        capacity = capacidades;


        printf("%d\n", maxflow(0, n+1, n+2));

    }

}

 