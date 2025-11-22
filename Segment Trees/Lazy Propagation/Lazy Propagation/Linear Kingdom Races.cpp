#include <bits/stdc++.h>
#define INF 10000
using namespace std;

struct race {
    int L;
    int R;
    int P;
};

int N;
int M;

class LazySegmentTree {
private:
    vector<long long> T;
    vector<long long> L;
    vector<bool> F;
public:
    LazySegmentTree() {
        T.resize(4 * (N + 2), -INF);
        L.resize(4 * (N + 2), 0);
        F.resize(4 * (N + 2), true);
    }

    void Relax(const int lo, const int hi, const int v) {
        if (!F[v]) {
            T[v] += L[v];
            if (lo != hi) {
                F[2 * v + 1] = false;
                F[2 * v + 2] = false;
                L[2 * v + 1] += L[v];
                L[2 * v + 2] += L[v];
            }
            F[v] = true;
            L[v] = 0;
        }
    }

    void Update(const int qlo, const int qhi, const int x, int lo = 0, int hi = N + 1, int v = 0) {
        Relax(lo, hi, v);
        if (qlo <= lo && hi <= qhi) {
            T[v] += x;
            if (lo != hi) {
                F[2 * v + 1] = false;
                F[2 * v + 2] = false;
                L[2 * v + 1] += x;
                L[2 * v + 2] += x;
            }
            return;
        }
        if (qlo > hi || qhi < lo)
            return;
        int mid = (lo + hi) / 2;
        Update(qlo, qhi, x, lo, mid, 2 * v + 1);
        Update(qlo, qhi, x, mid + 1, hi, 2 * v + 2);
        T[v] = max(T[2 * v + 1], T[2 * v + 2]);
    }

    void Update(const int i, const long long x, int lo = 0, int hi = N + 1, int v = 0) {
        if (lo == hi) {
            T[v] = x;
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid)
            Update(i, x, lo, mid, 2 * v + 1);
        else
            Update(i, x, mid + 1, hi, 2 * v + 2);
        T[v] = max(T[2 * v + 1], T[2 * v + 2]);
    }

    long long Query(const int qlo, const int qhi, int lo = 0, int hi = N + 1, int v = 0) {
        Relax(lo, hi, v);
        if (qlo <= lo && hi <= qhi)
            return T[v];
        if (qlo > hi || qhi < lo)
            return -INF;
        int mid = (lo + hi) / 2;
        long long maxLeft = Query(qlo, qhi, lo, mid, 2 * v + 1);
        long long maxRight = Query(qlo, qhi, mid + 1, hi, 2 * v + 2);
        return max(maxLeft, maxRight);
    }
};

int main() {
    scanf("%d %d", &N, &M);
    vector<int> C(N + 1);
    vector<long long> PS(N + 1);
    PS[0] = 0;
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &C[i]);
        PS[i] = PS[i - 1] + C[i];
    }
    vector<race> R(M);
    vector<vector<pair<int, int>>> AP(N + 2);
    for (int i = 0; i < M; ++i) {
        scanf("%d %d %d", &R[i].L, &R[i].R, &R[i].P);
        AP[R[i].L - 1].push_back({R[i].R, R[i].P});
    }
    vector<long long> dp(N + 2);
    LazySegmentTree T;
    dp[N + 1] = 0;
    T.Update(N + 1, PS[N]);
    for (int i = N; i >= 0; --i) {
        for (auto [upperBound, profit] : AP[i])
            T.Update(upperBound + 1, N + 1, profit);
        dp[i] = T.Query(i + 1, N + 1) - PS[i];
        if (i > 0)
            T.Update(i, dp[i] + PS[i - 1]);
    }
    printf("%lld\n", dp[0]);
}
