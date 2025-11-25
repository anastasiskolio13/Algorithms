#include <bits/stdc++.h>
#define MAXN 200000
using namespace std;

map<int, int> C;
vector<int> A(MAXN);
int N;
int K;

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; ++i)
        scanf("%d", &A[i]);
    for (int i = 0; i < N; ++i) {
        ++C[A[i]];
        if (i >= K - 1) {
            printf("%d ", C.size());
            if (!--C[A[i - K + 1]])
                C.erase(A[i - K + 1]);
        }
    }
}
