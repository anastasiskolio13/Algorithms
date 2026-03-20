#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
//#include <bits/stdc++.h>
#include <climits>
#include <cstdio>
#include <vector>
#include <cfloat>
#define MAXN 1000000
using namespace std;

int N;
vector<int> X(MAXN + 1);
vector<int> SM(MAXN + 2);

int main() {
    //freopen("profit.in", "r", stdin);
    //freopen("profit.out", "w", stdout);
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i)
        scanf("%d", &X[i]);

    SM[N + 1] = INT_MIN;
    for (int i = N; i >= 1; --i)
        SM[i] = max(SM[i + 1], X[i]);

    double maxprofit = DBL_MIN;
    for (int i = 1; i <= N; ++i) {
        maxprofit = max(maxprofit, (double)SM[i] / X[i]);
    }
    printf("%.3lf", maxprofit);
}