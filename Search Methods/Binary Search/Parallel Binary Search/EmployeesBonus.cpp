#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#define MAXN 100000
#define MAXK 100000
using namespace std;

vector<int> A(MAXN);
vector<vector<int>> Adj(MAXN);
vector<bool> hasParent(MAXN, false);
vector<pair<int, int>> Q(MAXK);
vector<pair<int, int>> R(MAXN);
vector<int> B(MAXN);
vector<int> S(MAXN);
vector<int> E(MAXN);
vector<long long> T(4 * MAXN);
vector<long long> L(4 * MAXN);

int N;
int K;
int timer = -1;

class LazySegmentTree {
private:
    void Relax(const int v, const int lo, const int hi) {
        if (L[v] != 0) {
            T[v] += L[v] * (hi - lo + 1);
            if (lo != hi) {
                L[2 * v + 1] += L[v];
                L[2 * v + 2] += L[v];
            }
            L[v] = 0;
        }
    }

public:
    void GiveBonus(const int qlo, const int qhi, const int x, int v = 0, int lo = 0, int hi = N - 1) {
        Relax(v, lo, hi);
        if (qlo > hi || qhi < lo)
            return;
        if (qlo <= lo && hi <= qhi) {
            T[v] += (long long)x * (hi - lo + 1);
            if (lo != hi) {
                L[2 * v + 1] += x;
                L[2 * v + 2] += x;                
            }
            return;
        }
        int mid = (lo + hi) / 2;
        GiveBonus(qlo, qhi, x, 2 * v + 1, lo, mid);
        GiveBonus(qlo, qhi, x, 2 * v + 2, mid + 1, hi);
        T[v] = T[2 * v + 1] + T[2 * v + 2];
    }

    long long GetMoney(const int i, int v = 0, int lo = 0, int hi = N - 1) {
        Relax(v, lo, hi);
        if (lo == hi)
            return T[v];
        int mid = (lo + hi) / 2;
        if (i <= mid)
            return GetMoney(i, 2 * v + 1, lo, mid);
        else
            return GetMoney(i, 2 * v + 2, mid + 1, hi); 
    }
};

void DFS(int v, int p) {
    S[v] = ++timer;
    for (int u : Adj[v])
        if (u != p)
            DFS(u, v);
    E[v] = timer;
}

int main() {
    cin >> N >> K; 
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    for (int i = 0; i < N - 1; ++i) {
        int v, u;
        cin >> v >> u;
        Adj[--v].push_back(--u);
        hasParent[u] = true;
    }
    for (int i = 0; i < K; ++i) {
        cin >> Q[i].first >> Q[i].second;
        --Q[i].first;
    } 
    for (int v = 0; v < N; ++v)
        if (!hasParent[v])
            DFS(v, -1);
    fill(R.begin(), R.begin() + N, make_pair(0, K - 1));
    for (int i = 0; i < ceil(log2(K)); ++i) {
        vector<vector<int>> TS(K);
        for (int j = 0; j < N; ++j) {
            int lo = R[j].first;
            int hi = R[j].second;
            if (lo < hi) 
                TS[(lo + hi) / 2].push_back(j);
        }
        LazySegmentTree Tree;
        for (int j = 0; j < K; ++j) {
            int v = Q[j].first;
            int bonus = Q[j].second;
            Tree.GiveBonus(S[v], E[v], bonus / (E[v] - S[v] + 1));
            Tree.GiveBonus(S[v], S[v], bonus % (E[v] - S[v] + 1));
            for (int k : TS[j]) 
                if (Tree.GetMoney(S[k]) >= A[k])
                    R[k].second = j;
                else   
                    R[k].first = j + 1;
        }
        fill(T.begin(), T.begin() + 4 * N, 0);
        fill(L.begin(), L.begin() + 4 * N, 0);
    }
    vector<vector<int>> TS(K);
    for (int i = 0; i < N; ++i)
        TS[R[i].first].push_back(i);
    LazySegmentTree Tree;
    for (int i = 0; i < K; ++i) {
        int v = Q[i].first;
        int bonus = Q[i].second;
        Tree.GiveBonus(S[v], E[v], bonus / (E[v] - S[v] + 1));
        Tree.GiveBonus(S[v], S[v], bonus % (E[v] - S[v] + 1));
        for (int j : TS[i])
            if (Tree.GetMoney(S[j]) >= A[j])
                B[j] = i + 1;
            else 
                B[j] = -1;
    }
    for (int i = 0; i < N; ++i)
        cout << B[i] << endl;
}