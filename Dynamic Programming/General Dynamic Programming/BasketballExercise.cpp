#include <bits/stdc++.h>
#define MAXN 100000
#define INF LLONG_MAX
using namespace std;

vector<int> A(MAXN);
vector<int> B(MAXN);
vector<vector<long long>> dp(MAXN, vector<long long>(2));
int N;

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    for (int i = 0; i < N; ++i)
        cin >> B[i];
    long long maxZero = -INF;
    long long maxOne = -INF;
    for (int i = N - 1; i >= 0; --i) {
        dp[i][0] = max(0LL, maxOne) + A[i];
        dp[i][1] = max(0LL, maxZero) + B[i];
        maxZero = max(maxZero, dp[i][0]);
        maxOne = max(maxOne, dp[i][1]);
    }
    long long maximumTotalHeight = -INF;
    for (int i = 0; i < N; ++i)
        maximumTotalHeight = max({maximumTotalHeight, dp[i][0], dp[i][1]});
    cout << maximumTotalHeight << endl;
}
