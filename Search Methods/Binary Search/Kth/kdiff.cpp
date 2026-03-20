#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 300000
using namespace std;

vector<int> A(MAXN);
int N; 
long K;

long numberOfPairsWithDifferenceAtMost(int D) {
    int i = 0; long totalPairs = 0;
    for (int j = 0; j < N; j++) {
        while (A[j] - A[i] > D)
            ++i;
        totalPairs += j - i;
    }
    return totalPairs;
}

int main() {
    scanf("%d %ld", &N, &K);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    sort(A.begin(), A.begin() + N);
    int lo = 1;
    int hi = A[N - 1] - A[0];
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (numberOfPairsWithDifferenceAtMost(mid) >= K)
            hi = mid;
        else
            lo = mid + 1;
    }
    printf("%d\n", lo);
}