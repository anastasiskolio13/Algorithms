#include <bits/stdc++.h>
using namespace std;

set<int> S;
map<int, int> TP;
vector<int> AP;
int N;

class SegmentTree {
private:
    vector<pair<int, long long>> T;
public:
    SegmentTree() {
        T.resize(4 * N, make_pair(0, 0));
    }

    void Update(const int i, const int x, int lo = 0, int hi = N - 1, int v = 0) {
        if (lo == hi) {
            T[v].first += x;
            T[v].second += x * AP[lo];
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid)
            Update(i, x, lo, mid, 2 * v + 1);
        else
            Update(i, x, mid + 1, hi, 2 * v + 2);
        T[v] = make_pair(T[2 * v + 1].first + T[2 * v + 2].first, T[2 * v + 1].second + T[2 * v + 2].second);
    }

    pair<int, long long> Query(const int qlo, const int qhi, int lo = 0, int hi = N - 1, int v = 0) {
        if (qlo <= lo && hi <= qhi)
            return T[v];
        if (qlo > hi || qhi < lo)
            return make_pair(0, 0);
        int mid = (lo + hi) / 2;
        pair<int, long long> QueryLeft = Query(qlo, qhi, lo, mid, 2 * v + 1);
        pair<int, long long> QueryRight = Query(qlo, qhi, mid + 1, hi, 2 * v + 2);
        return make_pair(QueryLeft.first + QueryRight.first, QueryLeft.second + QueryRight.second);
    }

    long long C(const int x, const int a, const int b) {
        long long totalCost = 0;
        auto it = S.upper_bound(x);
        if (it != S.end())
            totalCost += b * (Query(TP[*it], N - 1).second - x * Query(TP[*it], N - 1).first);
        if (it != S.begin())
            totalCost += a * (x * Query(0, TP[*(--it)]).first - Query(0, TP[*it]).second);
        return totalCost;
    }

    /*long long MinimumCost(const int a, const int b) {
        int lo = 1;
        int hi = 1e9;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (C(mid, a, b) > C(mid + 1, a, b))
                lo = mid + 1;
            else
                hi = mid;
        }
        return C(lo, a, b);
    }*/

    /*long long MinimumCost(const int a, const int b, int lo = 0, int hi = N - 1, int v = 0) {
       if (lo == hi)
           return C(lo, a, b);
        int mid =
    }*/
};

int main() {
    freopen("bicycle.in", "r", stdin);
    freopen("bicycle.out", "w", stdout);
    int Q;
    scanf("%d", &Q);
    vector<array<int, 3>> A;
    for (int q = 0; q < Q; ++q) {
        int a, b, c;
        scanf("%d %d", &a, &b);
        if (a != 3) {
            A.push_back({a, b, -1});
            S.insert(b);
        }
        else {
            scanf("%d", &c);
            A.push_back({a, b, c});
        }
    }
    N = S.size();
    AP.resize(N);
    int i = 0;
    for (int x : S) {
        TP[x] = i;
        AP[i] = x;
        ++i;
    }
    SegmentTree T;
    for (int q = 0; q < Q; ++q) {
        auto [a, b, c] = A[q];
        if (a == 1)
            T.Update(TP[b], 1);
        else if (a == 2)
            T.Update(TP[b], -1);
        else
            printf("%lld\n", T.MinimumCost(b, c));
    }
}
