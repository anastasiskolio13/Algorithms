#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 21
#define MOD 1000000007
using namespace std;

vector<vector<int>> A(MAXN, vector<int>(MAXN));
vector<int> dp(1 << MAXN);
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            scanf("%d", &A[i][j]);
    dp[0] = 1;
    for (int s = 1; s < (1 << N); ++s) {
        int i = __builtin_popcount(s) - 1;
        for (int j = 0; j < N; ++j) {
            if (s & (1 << j) && A[i][j]) {
                dp[s] += dp[s & ~(1 << j)];
                dp[s] %= MOD;
            }
        }
    }
    printf("%d\n", dp[(1 << N) - 1]);
}