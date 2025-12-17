#include <bits/stdc++.h>
#define MAXN 100000
using namespace std;

struct event {
    int X;
    int T;
};

bool CompareEvents(event A, event B) {
    return A.T < B.T;
}

set<pair<int, int>> S1;
set<pair<int, int>> S2;
vector<event> E(MAXN);
vector<int> I1(MAXN);
vector<int> I2(MAXN);
vector<int> dp(MAXN);
int N;
int V;

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
        T[v] = max(T[2 * v + 1], T[2 * v + 2]);
    }

    int Query(const int qlo, const int qhi, int lo = 0, int hi = N - 1, int v = 0) {
        if (qlo <= lo && hi <= qhi)
            return T[v];
        if (qlo > hi || qhi < lo)
            return 0;
        int mid = (lo + hi) / 2;
        int maxLeft = Query(qlo, qhi, lo, mid, 2 * v + 1);
        int maxRight = Query(qlo, qhi, mid + 1, hi, 2 * v + 2);
        return max(maxLeft, maxRight);
    }
};

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%d %d", &E[i].X, &E[i].T);
    scanf("%d", &V);
    sort(E.begin(), E.begin() + N, CompareEvents);
    for (int i = 0; i < N; ++i) {
        S1.insert({V * E[i].T - E[i].X, i});
        S2.insert({V * E[i].T + E[i].X, i});
    }
    int i = 0;
    for (auto [_, index] : S1)
        I1[index] = i++;
    i = 0;
    for (auto [_, index] : S2)
        I2[index] = i++;
    fill(dp.begin(), dp.begin() + N , 1);
    SegmentTree T1;
    SegmentTree T2;
    for (int i = N - 1; i >= 0; --i) {
        auto iteratorOne = S1.lower_bound({V * E[i].T - E[i].X, 0});
        auto iteratorTwo = S2.lower_bound({V * E[i].T + E[i].X, 0});
        if (iteratorOne != S1.end() && iteratorTwo != S2.end())
            dp[i] =
        //if (iteratorOne != S1.end())
            //dp[i] = max(dp[i], T1.Query(I1[iteratorOne->second], N - 1) + 1);
        //if (iteratorTwo != S2.end())
            //dp[i] = max(dp[i], T2.Query(I2[iteratorTwo->second], N - 1) + 1);
        //T1.Update(I1[i], dp[i]);
        //T2.Update(I2[i], dp[i]);
    }
    printf("%d\n", *max_element(dp.begin(), dp.begin() + N));
}
