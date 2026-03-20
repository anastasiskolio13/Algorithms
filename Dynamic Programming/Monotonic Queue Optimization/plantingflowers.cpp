#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <deque>
#define MAXN 50000
using namespace std;

vector<int> A(MAXN + 1);
vector<int> dp(MAXN + 2);
int N;
int B;

int calculateDP(int L) {
    deque<int> Q;
    dp[N + 1] = 0;
    Q.push_back(N + 1);
    for (int i = N; i >= 0; --i) {
        if (Q.front() == min(i + L, N) + 2)
            Q.pop_front();
        dp[i] = dp[Q.front()] + A[i];
        while (!Q.empty() && dp[i] <= dp[Q.back()])
            Q.pop_back();
        Q.push_back(i);
    }
    return dp[0];
}

int main() {
    scanf("%d %d", &N, &B);
    for (int i = 1; i <= N; ++i)
        scanf("%d", &A[i]);
    int lo = 0;
    int hi = N;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (calculateDP(mid) <= B)
            hi = mid;
        else
            lo = mid + 1;
    }
    printf("%d\n", lo);
}