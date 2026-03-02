#include <iostream>
#include <vector>

int main() {
    // Ανάγνωση δεδομένων.
    freopen("DG.in", "r", stdin);
    freopen("DG.out", "w", stdout);
    int N;
    scanf("%d", &N);
    std::vector<int> A(N + 1);
    for (int i = 1; i <= N; ++i)
        scanf("%d", &A[i]);
    // Επίλυση.
    std::vector<int> dp(3);
    dp[0] = 0;
    dp[1] = std::max(A[1], 0);
    for (int i = 2; i <= N; ++i)
        dp[i % 2] = std::max(dp[(i - 1) % 2] + std::max(A[i], 0), dp[(i - 2) % 2] + A[i] * A[i - 1]);
    printf("%d\n", dp[N % 2]);
}
