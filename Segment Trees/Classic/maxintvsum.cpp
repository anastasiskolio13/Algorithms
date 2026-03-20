#include <bits/stdc++.h>
#define INF 1e16
using namespace std;

vector<int> A;
vector<long long> PS;
int N;
int Q;

class SegmenTree {
private:
    vector<long long> T;
public:
    SegmenTree() {
        T.resize(4 * N, -INF);
    }

    void Update(const int i, int lo = 1, int hi = N, int v = 0) {
        if (lo == hi) {
            T[v] = -PS[lo - 1];
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid)
            Update(i, lo, mid, 2 * v + 1);
        else
            Update(i, mid + 1, hi, 2 * v + 2);
        T[v] = max(T[2 * v + 1], T[2 * v + 2]);
    }

    long long Query(const int qlo, const int qhi, int lo = 1, int hi = N, int v = 0) {
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
    scanf("%d %d", &N, &Q);
    A.resize(N + 1);
    PS.resize(N + 1);
    SegmenTree T;
    PS[0] = 0;
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &A[i]);
        PS[i] = PS[i - 1] + A[i];
        T.Update(i);
    }
    while (Q--) {
        int j, a, b;
        scanf("%d %d %d", &j, &a, &b);
        printf("%lld\n", T.Query(max(1, j - b + 1), j - a + 1) + PS[j]);
    }
}
