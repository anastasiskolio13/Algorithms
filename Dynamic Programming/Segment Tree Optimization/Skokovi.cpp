#include <bits/stdc++.h>
#define MAXN 200000
using namespace std;

set<pair<int, int>> S;
vector<int> I(MAXN);
vector<int> A(MAXN);
vector<bool> dp(MAXN);
int N;
int K;

class SegmentTree {
private:
    vector<bool> T;
public:
    SegmentTree() {
        T.resize(4 * N, false);
    }

    void Update(const int i, int lo = 0, int hi = N - 1, int v = 0) {
        if (lo == hi) {
            T[v] = dp[i];
            return;
        }
        int mid = (lo + hi) / 2;
        if (I[i] <= mid)
            Update(i, lo, mid, 2 * v + 1);
        else
            Update(i, mid + 1, hi, 2 * v + 2);
        T[v] = T[2 * v + 1] || T[2 * v + 2];
    }

    bool Query(const int qlo, const int qhi, int lo = 0, int hi = N - 1, int v = 0) {
        if (qlo > hi || qhi < lo)
            return false;
        if (qlo <= lo && hi <= qhi)
            return T[v];
        int mid = (lo + hi) / 2;
        bool isTrueLeft = Query(qlo, qhi, lo, mid, 2 * v + 1);
        bool isTrueRight = Query(qlo, qhi, mid + 1, hi, 2 * v + 2);
        return isTrueLeft || isTrueRight;
    }
};

int main() {
    cin >> N >> K;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        S.insert({A[i], i});
    }
    int i = 0;
    for (auto [_, index] : S)
        I[index] = i++;
    SegmentTree T;
    dp[0] = true;
    T.Update(0);
    for (int i = 1; i < N; ++i) {
        auto iteratorOne = S.upper_bound({A[i] + K, N});
        auto iteratorTwo = S.lower_bound({A[i] - K, 0});
        if (iteratorOne != S.begin() && iteratorTwo != S.end())
            dp[i] = T.Query(I[iteratorTwo->second], I[(--iteratorOne)->second]);
        else
            dp[i] = false;
        T.Update(i);
    }
    for (int i = 0; i < N; ++i)
        cout << dp[i] << " ";
}
