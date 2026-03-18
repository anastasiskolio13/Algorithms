#include <iostream>
#include <vector>
#include <climits>
#define MAXN 150000
#define MAXM 300
#define INF LLONG_MAX
using namespace std;

vector<vector<long long>> dp(2, vector<long long>(MAXN));
vector<int> A(MAXM);
vector<int> B(MAXM);
vector<int> T(MAXM);
int N;
int M;
int D;

int main() {
    cin >> N >> M >> D;
    for (int i = 0; i < M; ++i) {
        cin >> A[i] >> B[i] >> T[i];
        --A[i];
    }
    for (int i = 0; i < N; ++i)
        dp[(M - 1) % 2][i] = B[M - 1] - abs(A[M - 1] - i);
    for (int j = M - 2; j >= 0; --j) {
        for (int i = 0; i < N; ++i) {
            dp[j % 2][i] = -INF;
            for (int k = max(0LL, i - (T[j + 1] - T[j]) * (long long)D); k <= min(i + (T[j + 1] - T[j]) * (long long)D, (long long)N - 1); ++k)
                dp[j % 2][i] = max(dp[j % 2][i], dp[(j + 1) % 2][k]);
            dp[j % 2][i] += B[j] - abs(A[j] - i);
        }
    }
    long long ans = -INF;
    for (int i = 0; i < N; ++i)
        ans = max(ans, dp[0][i]);
    cout << ans << endl;
}