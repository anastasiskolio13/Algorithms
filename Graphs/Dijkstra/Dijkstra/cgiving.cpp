#include <bits/stdc++.h>
#define INF 2e9
using namespace std;

vector<int> Dijkstra(const vector<vector<pair<int, int>>>& Adj) {
    vector<int> D(Adj.size(), INF);
    set<pair<int, int>> Q;
    for (int v = 1; v < Adj.size(); ++v)
        Q.insert({INF, v});
    D[0] = 0;
    Q.insert({0, 0});
    for (int i = 0; i < Adj.size() - 1; ++i) {
        auto [_, v] = *Q.begin();
        Q.erase(Q.begin());
        for (auto [u, w] : Adj[v]) {
            if (D[v] + w < D[u]) {
                Q.erase({D[u], u});
                D[u] = D[v] + w;
                Q.insert({D[u], u});
            }
        }
    }
    return D;
}

int main() {
    int N;
    int M;
    int B;
    scanf("%d %d %d", &N, &M, &B);
    vector<vector<pair<int, int>>> Adj(N);
    for (int i = 0; i < M; ++i) {
        int v;
        int u;
        int w;
        scanf("%d %d %d", &v, &u, &w);
        Adj[--v].push_back({--u, w});
        Adj[u].push_back({v, w});
    }
    vector<int> D = Dijkstra(Adj);
    for (int i = 0; i < B; ++i) {
        int v;
        int u;
        scanf("%d %d", &v, &u);
        printf("%d\n", D[--v] + D[--u]);
    }
}
