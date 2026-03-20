#include <iostream>
#include <vector>
#include <climits>
#include <stack>
#define INF LLONG_MAX
#define MAXN 300000
using namespace std;

stack<int> S;
vector<int> H(MAXN);
vector<int> B(MAXN);
vector<int> R(MAXN);
vector<long long> dp(MAXN + 1);
int N;

class SegmentTree {
private:
    long long value;
    SegmentTree* left;
    SegmentTree* right;
public:
    SegmentTree(int lo = 0, int hi = N) {
        if (lo == hi) {
            value = -INF;
            left = nullptr;
            right = nullptr;
            return;
        }
        int mid = (lo + hi) / 2;
        left = new SegmentTree(lo, mid);
        right = new SegmentTree(mid + 1, hi);
        value = max(left->value, right->value);
    }    

    long long Query(const int qlo, const int qhi, int lo = 0, int hi = N) const {
        if (qlo > hi || qhi < lo)
            return -INF;
        if (qlo <= lo && hi <= qhi)
            return value;
        int mid = (lo + hi) / 2;
        long long maxLeft = left->Query(qlo, qhi, lo, mid);
        long long maxRight = right->Query(qlo, qhi, mid + 1, hi);
        return max(maxLeft, maxRight);
    }

    void Update(const int i, int lo = 0, int hi = N) {
        if (lo == hi) {
            value = dp[i];
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid)
            left->Update(i, lo, mid);
        else 
            right->Update(i, mid + 1, hi);
        value = max(left->value, right->value);
    }
};

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> H[i];
    for (int i = 0; i < N; ++i)
        cin >> B[i];
    fill(R.begin(), R.begin() + N, N - 1);
    for (int j = 0; j < N; ++j) {
        while (!S.empty() && H[j] < H[S.top()]) {
            int i = S.top();
            S.pop();
            R[i] = j - 1;
        }
        S.push(j);
    }
    SegmentTree T;
    dp[N] = 0;
    T.Update(N);
    for (int i = N - 1; i >= 0; --i) {
        dp[i] = max(T.Query(i + 1, R[i] + 1) + B[i], R[i] == N - 1 ? -INF : dp[R[i] + 1]);
        T.Update(i);
    }
    cout << dp[0] << endl;
} 
