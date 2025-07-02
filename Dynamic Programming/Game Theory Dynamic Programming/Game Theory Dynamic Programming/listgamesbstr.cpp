#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 10000
#define A 0 
#define B 1
using namespace std;

vector<vector<vector<int>>> dp(2, vector<vector<int>>(MAXN + 1, vector<int>(2)));
vector<int> V(MAXN + 1);
int N;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i)
        scanf("%d", &V[i]);
    for (int i = 1; i <= N; ++i) {
        dp[i % 2][i][A] = V[i];
        dp[i % 2][i][B] = 0;
    }
    for (int l = 2; l <= N; ++l) {
        for (int i = 1; i <= N - l + 1; ++i) {
            dp[i % 2][i + l - 1][A] = max(V[i] + dp[(i + 1) % 2][i + l - 1][B], V[i + l - 1] + dp[i % 2][i + l - 2][B]);
            dp[i % 2][i + l - 1][B] = min(dp[(i + 1) % 2][i + l - 1][A], dp[i % 2][i + l - 2][A]);
        }
    }
    printf("%d\n", dp[1][N][A]);
}