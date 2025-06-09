#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
#define MAXM 1000000
using namespace std;

vector<int> O(MAXM);
vector<int> T(MAXN);
vector<int> Z(MAXN);
int N;
int D;
int M;

bool isPossibleToProcessAllOrdersWith(int C) {
    for (int i = 0; i < N; ++i)
        Z[i] = T[i];
    int i = 0;
    for (int j = 0; j < N; ++j) {
        if (j - i > D)
            return false;
        int availableChefs = C;
        while (i <= j && availableChefs > 0) {
            int completed = min(Z[i], availableChefs);
            Z[i] -= completed;
            availableChefs -= completed;
            i += !Z[i];
        }
    }
    return true;
}

int main() {
    scanf("%d %d %d", &N, &D, &M);
    for (int i = 0; i < M; ++i) {
        scanf("%d", &O[i]);
        ++T[--O[i]];
    }
    int lo = 1;
    int hi = M;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (isPossibleToProcessAllOrdersWith(mid))
            hi = mid;
        else  
            lo = mid + 1;
    }
    printf("%d\n", lo);
}