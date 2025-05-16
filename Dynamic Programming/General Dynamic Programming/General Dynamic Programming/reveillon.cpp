#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 50000
using namespace std;

vector<int> dp(MAXN + 1);
vector<int> H(MAXN);
int N;
int K;

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; ++i)
        scanf("%d", &H[i]);
    dp[N] = 0;
    for (int i = N - 1; i >= 0; --i) {
        int max_el = 0;
        dp[i] = 0;
        for (int j = i; j < min(i + K, N); ++j) {
            max_el = max(max_el, H[j]);
            dp[i] = max(dp[i], dp[j + 1] + (j - i + 1) * max_el);
        }
    }
    printf("%d\n", dp[0]);
}