#include <bits/stdc++.h>
#define MAXN 200000
using namespace std;

vector<vector<int>> Adj(MAXN);
vector<int> Q(MAXN);
vector<string> A(MAXN);
int N;
int M;

class DisjointSets {
private:
    vector<int> P;
    vector<int> S;
public:
    DisjointSets() {
        P.resize(N);
        S.resize(N);
        for (int a = 0; a < N; ++a) {
            P[a] = a;
            S[a] = 1;
        }
    }

    int GetSize(const int a) {
        return S[a];
    }

    int Find(const int a) {
        return P[a] == a ? a : P[a] = Find(P[a]);
    }

    void Unite(int a, int b) {
        a = Find(a);
        b = Find(b);
        if (a == b) return;
        if (S[a] < S[b]) swap(a, b);
        P[b] = a;
        S[a] += S[b];
    }
};

int main() {
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int v, u;
        cin >> v >> u;
        Adj[--v].push_back(--u);
        Adj[u].push_back(v);
    }
    for (int i = 0; i < N; ++i)
        cin >> Q[i];
    DisjointSets DSU;
    vector<bool> isActive(N, false);
    for (int i = N - 1; i >= 0; --i) {
        int v = --Q[i];
        isActive[v] = true;
        for (int u : Adj[v])
            if (isActive[u])
                DSU.Unite(v, u);
        A[i] = DSU.GetSize(DSU.Find(v)) == N - i ? "YES" : "NO";
    }
    for (int i = 0; i < N; ++i)
        cout << A[i] << endl;
}
