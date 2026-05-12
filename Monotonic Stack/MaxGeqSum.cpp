#include <iostream>
#include <vector>
#include <stack>
#define MAXN 200000
using namespace std;

vector<int> A(MAXN);
vector<int> L(MAXN);
vector<int> R(MAXN);
int T;
int N;

class SegmentTree {
private:
    vector<long long> T;
public:
    SegmentTree() {
        T.resize(4 * N);
    }

    void Update(int i, int lo = 0, int hi = N - 1, int v = 0) {
        T[v] += A[i];
        if (lo == hi)
            return;
        int mid = (lo + hi) / 2;
        if (i <= mid)
            Update(i, lo, mid, 2 * v + 1);
        else 
            Update(i, mid + 1, hi, 2 * v + 2);
    }

    long long Query(int qlo, int qhi, int lo = 0, int hi = N - 1, int v = 0) {
        if (qlo > hi || qhi < lo)
            return 0;
        if (qlo <= lo && hi <= qhi)
            return T[v];
        int mid = (lo + hi) / 2;
        long long sumLeft = Query(qlo, qhi, lo, mid, 2 * v + 1);
        long long sumRight = Query(qlo, qhi, mid + 1, hi, 2 * v + 2);
        return sumLeft + sumRight;
    }
};

int main() {
    cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; ++i)
            cin >> A[i];
        stack<int> S;
        fill(R.begin(), R.begin() + N, N - 1);
        for (int j = 0; j < N; ++j) {
            while (!S.empty() && A[j] > A[S.top()]) {
                int i = S.top();
                S.pop();
                R[i] = j - 1;
            }
        }
        stack<int> Q;
        fill(L.begin(), L.begin() + N, 0);
        for (int j = N - 1; j >= 0; --j) {
            while (!S.empty() && A[j] > A[Q.top()]) {
                int i = Q.top();
                Q.pop();
                L[i] = j + 1;
            }
        }
        SegmentTree T;
        for (int i = 0; i < N; ++i)
            T.Update(i);
        for (int i = 0; i < N; ++i)
            if (A[i] < T.Q)
    }
}