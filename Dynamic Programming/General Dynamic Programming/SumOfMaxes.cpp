#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#define MAXK 500
#define MAXN 200000
#define INF 2000000000
using namespace std;

stack<int> S;
vector<int> A(MAXN + 1);
vector<int> L(MAXN + 1);
vector<vector<int>> dp(MAXK + 1, vector<int>(MAXN + 1));
int N;
int K;

int main() {
    // Read Input.
    scanf("%d %d", &N, &K);
    for (int i = 1; i <= N; ++i)
        scanf("%d", &A[i]);
    
    // Compute L_i.
    fill(L.begin() + 1, L.begin() + N + 1, 1);
    for (int j = N; j >= 1; --j) {
        while (!S.empty() && A[j] > A[S.top()]) {
            int i = S.top();
            S.pop();
            L[i] = j + 1;
        }
        S.push(j);
    } 

    // Compute DP.
    dp[0][0] = 0;
    for (int i = 1; i <= N; ++i)
        dp[0][i] = INF;
    for (int j = 1; j <= K; ++j) {
        dp[j][0] = INF;
        for (int i = 1; i <= N; ++i) {
            dp[j][i] = min(min(dp[j - 1][L[i] - 1], dp[j - 1][i - 1]) + A[i], L[i] == 1 ? INF : dp[j][L[i] - 1]);
        }
    }
    printf("%d\n", dp[K][N]);
}