#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
using namespace std;

vector<int> S(MAXN); 
vector<int> F(MAXN);
int N; 
long long K;

long long totalProduction(int T) {
    long long production = 0;
    for (int i = 0; i < N; ++i)
        production += max(0, min(T, F[i]) - S[i] + 1);
    return production;
}

int main() {
    scanf("%d %lld", &N, &K);
    for (int i = 0; i < N; ++i)
        scanf("%d %d", &S[i], &F[i]);
    int lo = *min_element(S.begin(), S.begin() + N);
    int hi = *max_element(F.begin(), F.begin() + N);
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (totalProduction(mid) >= K)
            hi = mid;
        else 
            lo = mid + 1;
    }
    printf("%d\n", lo);
}