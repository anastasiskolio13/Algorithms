#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
using namespace std;

vector<int> A(MAXN);
vector<int> B(MAXN);
int N;
long K;

long long countOfPairsWithSumAtMost(long long X) {
    long long totalPairs = 0;
    int j = N - 1;
    for (int i = 0; i < N; ++i) {
        while (j >= 0 && A[i] + B[j] > X)
            --j;
        totalPairs += j + 1;
    }
    return totalPairs;
}

int main() {
    scanf("%d %ld", &N, &K);
    for (int i = 0; i < N; ++i)
        scanf("%d", &A[i]);
    for (int i = 0; i < N; ++i)
        scanf("%d", &B[i]);
    sort(A.begin(), A.begin() + N);
    sort(B.begin(), B.begin() + N);
    long long lo = A[0] + B[0];
    long long hi = A[N - 1] + B[N - 1];
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (countOfPairsWithSumAtMost(mid) >= K)
            hi = mid;
        else 
            lo = mid + 1;
    }
    printf("%lld\n", lo);
}