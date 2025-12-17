#include <bits/stdc++.h>
#define MAXN 200000
#define MAXM 200000
#define MAXD 200000
#define MAXQ 200000
using namespace std;

set<pair<int, int>> S;
vector<int> C(MAXN); // Capacity of the ith school.
vector<pair<int, int>> E(MAXM); // All graph edges.
vector<array<int, 3>> DC(MAXD); // Daily changes.
vector<array<int, 3>> T(MAXD); // Queries.
vector<pair<int, int>> R(MAXQ); // Query Range.
vector<> TS(MAXD + 1); // Timestamps.
int N;
int M;
int D;
int Q;

class DSU {
private:
    vector<int> P;
    vector<int> S;
    vector<int> C; // Total students that can be visited.
public:
    DSU() {
        P.resize(N);
        S.resize(N, 1);
        C.resize(N);
        for (int a = 0; a < N; ++a) {
            P[a] = a;
            C[a] = ::C[a];
        }
    }
}

int main() {
    scanf("%d %d %d %d", &N, &M, &D, &S);
    for (int i = 0; i < N; ++i)
        scanf("%d", &C[i]);
    for (int i = 0; i < M; ++i) {
        int v, u;
        scanf("%d %d", &v, &u);
        E[i] = make_pair(--v, --u);
        S.insert(E[i]);
    }
    for (int i = 0; i < D; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if (a == 1)
            S.erase(make_pair(--b, --c));
        else
            C[--b] -= c;
        DC[i] = {a, b, c};
    }
    for (int i = 0; i < Q; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        T[i] = {--a, --b, c};
    }
    for (int i = 0; i < Q; ++i)
        R[i] = make_pair();
    for (int i = 0; i < ceil(log2(D + 1)); ++i) {

    }
}
