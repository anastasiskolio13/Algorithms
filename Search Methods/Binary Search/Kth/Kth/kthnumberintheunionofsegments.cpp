#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 50
using namespace std;

vector<long long> L(MAXN);
vector<long long> R(MAXN);
long long N;
long long K;

long long countOfElementsSmallerThanOrEqualTo(long long X) {
    long long count = 0;
    for (long long i = 0; i < N; ++i)
        count += max(min(X, R[i]) - L[i] + 1, 0LL);
    return count;
}

int main() {
    scanf("%lld %lld", &N, &K);
    ++K; // Θέλω το K-οστό σε μηδενική αρίθμηση, οπότε το K + 1 σε κανονική
    for (long long i = 0; i < N; ++i) 
        scanf("%lld %lld", &L[i], &R[i]);
    long long lo = *min_element(L.begin(), L.begin() + N);
    long long hi = *max_element(R.begin(), R.begin() + N);
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (countOfElementsSmallerThanOrEqualTo(mid) >= K)
            hi = mid;
        else 
            lo = mid + 1;
    }
    printf("%lld\n", lo);
}