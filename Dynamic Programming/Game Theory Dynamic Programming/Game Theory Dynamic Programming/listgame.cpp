#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 10000
#define A 0 
#define B 1
using namespace std;

vector<vector<vector<int>>> dp(2, vector<vector<int>>(MAXN, vector<int>(2)));
vector<int> V(MAXN);
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%d", &V[i]);
    for (int i = N - 1; i >= 0; --i) {
        dp[i % 2][i][A] = V[i];
        dp[i % 2][i][B] = 0;
        for (int j = i + 1; j < N; ++j) {
            dp[i % 2][j][A] = max(V[i] + dp[(i + 1) % 2][j][B], V[j] + dp[i % 2][j - 1][B]);
            dp[i % 2][j][B] = min(dp[(i + 1) % 2][j][A], dp[i % 2][j - 1][A]);
        }
    }
    printf("%d\n", dp[0][N - 1][A]);
}