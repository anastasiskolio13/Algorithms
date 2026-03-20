#include <bits/stdc++.h>
#define MAXN 200000
using namespace std;

vector<int> A(MAXN);
vector<int> B(MAXN);
int T;
int N;
int K;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &N, &K);
        for (int i = 0; i < N; ++i)
            scanf("%d", &A[i]);
        for (int i = 0; i < K; ++i)
            scanf("%d", &B[i]);
        sort(A.begin(), A.begin() + N, greater<int>());
        sort(B.begin(), B.begin() + K);
        int i = 0;
        int j = 0;
        long long minimumTotalCost = 0;
        while (i < N) {
            if (j == K || i + B[j] - 1 >= N) {
                minimumTotalCost += A[i++];
                continue;
            }
            int k = 0;
            while (k < B[j] - 1) {
                minimumTotalCost += A[i++];
                ++k;
            }
            ++i;
            ++j;
        }
        printf("%lld\n", minimumTotalCost);
    }
}
