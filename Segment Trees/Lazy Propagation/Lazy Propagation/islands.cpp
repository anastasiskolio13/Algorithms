#include <bits/stdc++.h>
using namespace std;

class LazySegmentTree {
private:
    vector<int> T;
    vector<int> L;
    vector<bool> F;
public:
    LazySegmentTree(const int N) {
        T.resize(4 * N, 0);
        L.resize(4 * N, 0);
        F.resize(4 * N, true);
    }

    void Relax(const int lo, const int hi, const int v) {
        if (!F[v]) {
            T[v] = (hi - lo + 1) * L[v];
            if (lo != hi) {
                F[2 * v + 1] = false;
                F[2 * v + 2] = false;
                L[2 * v + 1] = L[v];
                L[2 * v + 2] = L[v];
            }
            F[v] = true;
            L[v] = 0;
        }
    }

    void Update(int lo, int hi, int v, const int qlo, const int qhi, const int x) {
        Relax(lo, hi, v);
        if (qlo <= lo && hi <= qhi) {
            T[v] = (long long)(hi - lo + 1) * x;
            if (lo != hi) {
                F[2 * v + 1] = false;
                F[2 * v + 2] = false;
                L[2 * v + 1] = x;
                L[2 * v + 2] = x;
            }
            return;
        }
        if (qlo > hi || qhi < lo)
            return;
        int mid = (lo + hi) / 2;
        Update(lo, mid, 2 * v + 1, qlo, qhi, x);
        Update(mid + 1, hi, 2 * v + 2, qlo, qhi, x);
        T[v] = T[2 * v + 1] + T[2 * v + 2];
    }

    int Query(int lo, int hi, int v, int tickets) {
        Relax(lo, hi, v);
        if (lo == hi)
            return lo;
    }
};

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);
    while (Q--) {
        char a; int b, c;
        scanf(" %c %d %d", &a, &b, &c);
        switch (c) {
            case 'D' : Update(0, N - 1, 0, b - 1, c - 2, 1); break;
            case 'B' : Update(0, N - 1, 0, b - 1, c - 2, 0); break;
            default: printf("%d\n", Query(0, N - 1, 0, c) + 1);
        }
    }
}
