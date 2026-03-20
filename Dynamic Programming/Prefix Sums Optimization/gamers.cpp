#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 1000000
using namespace std;

vector<int> V(MAXN);
vector<int> R(MAXN);
vector<int> S(MAXN + 2);
vector<bool> dp(MAXN + 1);
int N;
int X;
int Y;

bool canAchieveMaximumDifference(int D) {
    // Calculate for each i the max j : V[j] - V[i] <= D, using two pointers technique.
    int j = 0;
    for (int i = 0; i < N; ++i) {
        while (j < N && V[j] - V[i] <= D)
            ++j;
        R[i] = min(i + Y, j) - 1;
    }
    dp[N] = 1;
    S[N] = 1;
    for (int i = N - 1; i >= 0; --i) {
        dp[i] = i + X <= R[i] + 1 && (S[i + X] - S[R[i] + 2]);
        S[i] = dp[i] + S[i + 1];
    }
    return dp[0];
}

int main() {
    scanf("%d %d %d", &N, &X, &Y);
    for (int i = 0; i < N; ++i)
        scanf("%d", &V[i]);
    sort(V.begin(), V.begin() + N);
    int lo = 0;
    int hi = V[N - 1] - V[0];
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (canAchieveMaximumDifference(mid))
            hi = mid;
        else 
            lo = mid + 1;
    }
    printf("%d\n", lo);
}