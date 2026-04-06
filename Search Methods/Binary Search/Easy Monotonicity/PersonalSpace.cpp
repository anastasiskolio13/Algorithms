#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 1000000
using namespace std;

struct Penguin {
    int X;
    int R;
    bool operator<(const Penguin& other) const noexcept { return X < other.X; }
};

vector<Penguin> P(MAXN);
vector<int> R(MAXN);
vector<long long> dp(MAXN + 1);
int N;
long long D;

long long sumOfRentsWithMinimumDistance(int K) {
    for (int i = 0, j = 0; i < N; ++i) {
        while (j < N && P[j].X - P[i].X < K)
            ++j;
        R[i] = j;
    }
    for (int i = N - 1; i >= 0; --i)
        dp[i] = max(dp[i + 1], dp[R[i]] + P[i].R);
    return dp[0];
}

int main() {
    scanf("%d %lld", &N, &D);
    for (int i = 0; i < N; ++i)
        scanf("%d", &P[i].X);
    int maximumRent = 0;
    long long sumOfRents = 0;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &P[i].R);
        maximumRent = max(maximumRent, P[i].R);
        sumOfRents += P[i].R;
    }
    if (maximumRent >= D) {
        printf("-1\n");
        return 0;
    }
    if (sumOfRents < D) {
        printf("-2\n");
        return 0;
    }
    sort(P.begin(), P.begin() + N);
    int lo = 1;
    int hi = P[N - 1].X - P[0].X;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (sumOfRentsWithMinimumDistance(mid) >= D)
            lo = mid;
        else 
            hi = mid - 1;
    }
    printf("%d\n", lo);
}