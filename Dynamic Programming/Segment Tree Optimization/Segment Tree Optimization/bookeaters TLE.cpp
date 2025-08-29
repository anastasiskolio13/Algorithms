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
vector<int> T(4 * MAXN + 1);
int N;

void Update(int lo, int hi, int v, int i) {
    if (lo == hi) {
        T[v] = dp[i];
        return;
    }
    int mid = (lo + hi) / 2;
    if (i <= mid)
        Update(lo, mid, 2 * v + 1, i);
    else 
        Update(mid + 1, hi, 2 * v + 2, i);
    T[v] = max(T[2 * v + 1], T[2 * v + 2]);
}

int Query(int lo, int hi, int v, int qlo, int qhi) {
    if (qlo <= lo && hi <= qhi)
        return T[v];
    if (qlo > hi || qhi < lo)
        return -N;
    int mid = (lo + hi) / 2;
    int maxL = Query(lo, mid, 2 * v + 1, qlo, qhi);
    int maxR = Query(mid + 1, hi, 2 * v + 2, qlo, qhi);
    return max(maxL, maxR);
}

int calculateDPArrayWithMaximumTeamSize(int S) {
    for (int i = N - 1; i >= 0; --i) {
        dp[i] = i + B[i] <= min(i + S, N) ? Query(0, N, 0, i + B[i], min(i + S, N)) + 1 : INT_MIN;
        Update(0, N, 0, i);
    }
    return dp[0];
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%d", &B[i]);
    sort(B.begin(), B.begin() + N, greater<int>());
    int maximumTeams = calculateDPArrayWithMaximumTeamSize(N);
    int lo = 1;
    int hi = N;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (calculateDPArrayWithMaximumTeamSize(mid) == maximumTeams)
            hi = mid;
        else 
            lo = mid + 1;
    }
    printf("%d %d", maximumTeams, lo);
}