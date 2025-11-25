#include <bits/stdc++.h>
#define MAXN 200000
using namespace std;

set<pair<int, int>> S;
vector<int> A(MAXN);
vector<int> I(MAXN);
int N;
int K;

class SegmentTree {
private:
    vector<int> T;
public:
    SegmentTree() {
        T.resize(4 * N, 0);
    }

    void Update(const int i, const int x, int lo = 0, int hi = N - 1, int v = 0) {
        if (lo == hi) {
            T[v] = x;
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid)
            Update(i, x, lo, mid, 2 * v + 1);
        else
            Update(i, x, mid + 1, hi, 2 * v + 2);
        T[v] = T[2 * v + 1] + T[2 * v + 2];
    }

    int Query(const int qlo, const int qhi, int lo = 0, int hi = N - 1, int v = 0) {
        if (qlo <= lo && hi <= qhi)
            return T[v];
        if (qlo > hi || qhi < lo)
            return 0;
        int mid = (lo + hi) / 2;
        int sumLeft = Query(qlo, qhi, lo, mid, 2 * v + 1);
        int sumRight = Query(qlo, qhi, mid + 1, hi, 2 * v + 2);
        return sumLeft + sumRight;
    }
};

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &A[i]);
        S.insert({A[i], i});
    }
    int i = 0;
    for (auto [_, index] : S)
        I[index] = i++;
    SegmentTree T;
    long long currentInversions = 0;
    for (int i = 0; i < N; ++i) {
        auto it = S.upper_bound({A[i], N});
        if (it != S.end())
            currentInversions += T.Query(I[it->second], N - 1);
        T.Update(I[i], 1);
        if (i >= K - 1) {
            printf("%lld ", currentInversions);
            it = S.lower_bound({A[i - K + 1], 0});
            if (it != S.begin())
                currentInversions -= T.Query(0, I[(--it)->second]);
            T.Update(I[i - K + 1], 0);
        }
    }
}
