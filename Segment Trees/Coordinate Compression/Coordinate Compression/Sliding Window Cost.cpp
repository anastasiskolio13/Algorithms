#include <bits/stdc++.h>
using namespace std;

set<pair<int, int>> S;
vector<int> A;
vector<int> I;
int N;
int K;

class SegmentTree {
private:
    vector<pair<long long, int>> T;
public:
    SegmentTree() {
        T.resize(4 * N, make_pair(0, 0));
    }

    void Update(const int i, const pair<int, int> x, int lo = 0, int hi = N - 1, int v = 0) {
        if (lo == hi) {
            T[v] = x;
            return;
        }
        int mid = (lo + hi) / 2;
        if (I[i] <= mid)
            Update(i, x, lo, mid, 2 * v + 1);
        else
            Update(i, x, mid + 1, hi, 2 * v + 2);
        T[v].first = T[2 * v + 1].first + T[2 * v + 2].first;
        T[v].second  = T[2 * v + 1].second + T[2 * v + 2].second;
    }

    int Kth(int k, int lo = 0, int hi = N - 1, int v = 0) {
        if (lo == hi)
            return T[v].first;
        int mid = (lo + hi) / 2;
        if (T[2 * v + 1].second >= k)
            return Kth(k, lo, mid, 2 * v + 1);
        else
            return Kth(k - T[2 * v + 1].second, mid + 1, hi, 2 * v + 2);
    }

    pair<long long, int> Query(const int qlo, const int qhi, int lo = 0, int hi = N - 1, int v = 0) {
        if (qlo <= lo && hi <= qhi)
            return T[v];
        if (qlo > hi || qhi < lo)
            return make_pair(0, 0);
        int mid = (lo + hi) / 2;
        pair<long long, int> sumLeft = Query(qlo, qhi, lo, mid, 2 * v + 1);
        pair<long long, int> sumRight = Query(qlo, qhi, mid + 1, hi, 2 * v + 2);
        return make_pair(sumLeft.first + sumRight.first, sumLeft.second + sumRight.second);
    }
};

int main() {
    scanf("%d %d", &N, &K);
    A.resize(N);
    I.resize(N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &A[i]);
        S.insert({A[i], i});
    }
    int i = 0;
    for (auto [_, index] : S)
        I[index] = i++;
    SegmentTree T;
    for (int i = 0; i < N; ++i) {
        T.Update(i, make_pair(A[i], 1));
        if (i >= K - 1) {
            int median = T.Kth(ceil((double)K / 2));
            auto it = S.upper_bound({median, N});
            long long costOfBiggerValues = it != S.end() ? T.Query(I[it->second], N - 1).first - (long long)median * T.Query(I[it->second], N - 1).second : 0;
            long long costOfSmallerValues = (long long)median * T.Query(0, I[(--it)->second]).second - T.Query(0, I[it->second]).first;
            printf("%lld ", costOfBiggerValues + costOfSmallerValues);
            T.Update(i - K + 1, make_pair(0, 0));
        }
    }
}
