#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <climits>
#define MAXN 1000000
using namespace std;

vector<int> B(MAXN);
vector<int> dp(MAXN + 1);
int N;

int calculateDP(int S) {
    deque<int> Q;
    dp[N] = 0;
    Q.push_back(N);
    for (int i = N - 1; i >= 0; --i) {
        if (Q.front() > min(i + S, N))
            Q.pop_front();
        dp[i] = i + B[i] <= min(i + S, N) ? dp[Q.front()] + 1 : INT_MIN;
        while (!Q.empty() && dp[i] > dp[Q.back()])
            Q.pop_back();
        Q.push_back(i);
    }
    return dp[0];
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%d", &B[i]);
    sort(B.begin(), B.begin() + N, greater<int>());
    int maximumTeams = calculateDP(N);
    int lo = 1;
    int hi = N;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (calculateDP(mid) == maximumTeams)
            hi = mid;
        else 
            lo = mid + 1;
    }
    printf("%d %d", maximumTeams, lo);
}