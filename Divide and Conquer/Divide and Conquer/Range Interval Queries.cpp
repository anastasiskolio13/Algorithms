#include <bits/stdc++.h>
#define MAXN 200000
using namespace std;

struct query {
    int A;
    int B;
    int C;
    int D;
    int I;
};

vector<int> A(MAXN);
vector<int> B(MAXN);
vector<vector<int>> TS(MAXN);
vector<int> I(MAXN);
int N;
int T;

class SegmentTree {
private:
    vector<int> T;
public:
    SegmentTree(const int N) {
        T.resize(4 * N, 0);
    }

    void Update(const int i, int lo, int hi, int v) {
        if (lo == hi) {
            T[v] = 1;
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid)
            Update(i, lo, mid, 2 * v + 1);
        else
            Update(i, mid + 1, hi, 2 * v + 2);
        T[v] = T[2 * v + 1] + T[2 * v + 2];
    }

    int Query(int qlo, int qhi, int lo, int hi, int v) {
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

void SRQ(int lo, int hi, vector<query>& Q, vector<int>& B) {
    if (lo == hi) {
        for (auto [a, b, c, d, i] : Q)
            B[i] = (A[lo] >= c && A[lo] <= d);
        return;
    }
    int mid = (lo + hi) / 2;
    vector<query> QL;
    vector<query> QR;
    // Clear the timestamps.
    for (int i = lo; i <= hi; ++i)
        TS[i].clear();
    // Seperate Queries.
    for (int i = 0; i < Q.size(); ++i) {
        if (Q[i].A <= mid && mid < Q[i].B) {
            TS[Q[i].A].push_back(i);
            TS[Q[i].B].push_back(i);
        }
        else if (Q[i].B <= mid) {
            QL.push_back(Q[i]);
        }
        else {
            QR.push_back(Q[i]);
        }
    }
    // [lo...mid].
    set<pair<int, int>> S1;
    SegmentTree T1(mid - lo + 1);
    for (int i = mid; i >= lo; --i)
        S1.insert({A[i], i});
    int i = 0;
    for (auto [_, index] : S1)
        I[index] = i++;
    for (int i = mid; i >= lo; --i) {
        T1.Update(I[i], 0, S1.size() - 1, 0);
        for (int j : TS[i]) {
            auto iteratorOne = S1.lower_bound({Q[j].C, 0});
            auto iteratorTwo = S1.upper_bound({Q[j].D, N});
            if (iteratorOne != S1.end() && iteratorTwo != S1.begin())
                B[Q[j].I] += T1.Query(I[iteratorOne->second], I[(--iteratorTwo)->second], 0, S1.size() - 1, 0);
        }
    }
    // [mid + 1...hi].
    set<pair<int, int>> S2;
    SegmentTree T2(hi - mid);
    for (int i = mid + 1; i <= hi; ++i)
        S2.insert({A[i], i});
    i = 0;
    for (auto [_, index] : S2)
        I[index] = i++;
    for (int i = mid + 1; i <= hi; ++i) {
        T2.Update(I[i], 0, S2.size() - 1, 0);
        for (int j : TS[i]) {
            auto iteratorOne = S2.lower_bound({Q[j].C, 0});
            auto iteratorTwo = S2.upper_bound({Q[j].D, N});
            if (iteratorOne != S2.end() && iteratorTwo != S2.begin())
                B[Q[j].I] += T2.Query(I[iteratorOne->second], I[(--iteratorTwo)->second], 0, S2.size() - 1, 0);
        }
    }
    // Recursive step.
    SRQ(lo, mid, QL, B);
    SRQ(mid + 1, hi, QR, B);
}

int main() {
    scanf("%d %d", &N, &T);
    for (int i = 0; i < N; ++i)
        scanf("%d", &A[i]);
    vector<query> Q(T);
    for (int i = 0; i < T; ++i) {
        scanf("%d %d %d %d", &Q[i].A, &Q[i].B, &Q[i].C, &Q[i].D);
        --Q[i].A;
        --Q[i].B;
        Q[i].I = i;
    }
    SRQ(0, N - 1, Q, B);
    for (int i = 0; i < T; ++i)
        printf("%d\n", B[i]);
}
