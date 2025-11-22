#include <bits/stdc++.h>
#define MAXN 1000
#define MAXK 2000
using namespace std;

vector<int> A(MAXN);
vector<int> B(MAXK);
int N;
int K;
int P;

bool isPossible(int T) {
    int i = 0;
    for (int j = 0; j < K && i < N; ++j)
        i += (abs(A[i] - B[j]) + abs(B[j] - P) <= T);
    return i == N;
}

int main() {
    scanf("%d %d %d", &N, &K, &P);
    for (int i = 0; i < N; ++i)
        scanf("%d", &A[i]);
    for (int i = 0; i < K; ++i)
        scanf("%d", &B[i]);
    sort(A.begin(), A.begin() + N);
    sort(B.begin(), B.begin() + K);
    int lo = 0;
    int hi = 2e9;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (isPossible(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    printf("%d\n", lo);
}
