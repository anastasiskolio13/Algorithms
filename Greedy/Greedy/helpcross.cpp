#include <bits/stdc++.h>
#define MAXC 20000
#define MAXN 20000
using namespace std;

struct cow {
    int A;
    int B;
};

bool compareCows(cow X, cow Y) {
    return X.A < Y.A;
}

multiset<int> S;
vector<int> T(MAXC);
vector<cow> U(MAXN);
int C;
int N;

int main() {
    freopen("helpcross.in", "r", stdin);
    freopen("helpcross.out", "w", stdout);
    scanf("%d %d", &C, &N);
    for (int i = 0; i < C; ++i)
        scanf("%d", &T[i]);
    for (int i = 0; i < N; ++i)
        scanf("%d %d", &U[i].A, &U[i].B);
    sort(T.begin(), T.begin() + C);
    sort(U.begin(), U.begin() + N, compareCows);
    int ans = 0;
    int j = 0;
    for (int i = 0; i < C; ++i) {
        while (j < N && T[i] >= U[j].A)
            S.insert(U[j++].B);
        auto it = S.lower_bound(T[i]);
        if (it != S.end()) {
            ++ans;
            S.erase(it);
        }
    }
    printf("%d\n", ans);
}