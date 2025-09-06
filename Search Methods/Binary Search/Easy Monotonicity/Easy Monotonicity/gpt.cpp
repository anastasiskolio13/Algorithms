#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 100

vector<int> A(MAXN);
vector<int> B(MAXN);
vector<long long> C(MAXN);
int T;
int N;
int tM;
int tC;

long long floor_div(long long a, long long b) {
    // floor(a/b) works for positive/negative b
    if (b < 0) a = -a, b = -b;
    if (a >= 0) return a / b;
    return -((-a + b - 1) / b);
}

long long ceil_div(long long a, long long b) {
    // ceil(a/b) works for positive/negative b
    if (b < 0) a = -a, b = -b;
    if (a >= 0) return (a + b - 1) / b;
    return -((-a) / b);
}

bool canBessieSatisfyAllHerFriends(int L) {
    long long low = max(0, L - tC + 1);
    long long high = min(tM - 1, L);

    for (int i = 0; i < N; i++) {
        long long D = 1LL * A[i] - B[i];
        long long R = C[i] - 1LL * A[i] * (tC - L) - 1LL * B[i] * tM;

        if (D == 0) {
            if (R < 0) return false; // no solution possible for this friend
        }
        else if (D > 0) {
            high = min(high, floor_div(R, D));
        }
        else { // D < 0
            low = max(low, ceil_div(R, D));
        }

        if (low > high) return false; // interval collapsed
    }
    return true;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &N, &tC, &tM);
        for (int i = 0; i < N; ++i)
            scanf("%d %d %lld", &A[i], &B[i], &C[i]);

        int lo = 0;
        int hi = tC + tM - 2;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (canBessieSatisfyAllHerFriends(mid))
                hi = mid;
            else
                lo = mid + 1;
        }
        printf("%d\n", lo);
    }
}
