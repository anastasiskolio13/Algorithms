#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define MAXN 200
using namespace std;

struct point {
    int X;
    int Y;
};

bool comparePoints(point A, point B) {
    return A.X < B.X;
}

double dp[MAXN + 2][MAXN + 2];
vector<point> P(MAXN + 2);
int N;
int A;
int B;

double D(int i, int j) {
    return sqrt((double)(P[i].X - P[j].X) * (P[i].X - P[j].X) + (P[i].Y - P[j].Y) * (P[i].Y - P[j].Y));
}

int main() {
    scanf("%d %d %d", &N, &A, &B);
    for (int i = 1; i <= N; ++i)
        scanf("%d %d", &P[i].X, &P[i].Y);
    sort(P.begin() + 1, P.begin() + N + 1, comparePoints);
    P[0].X = 0;
    P[0].Y = 0;
    P[N + 1].X = A;
    P[N + 1].Y = B;
    for (int i2 = N; i2 >= 0; --i2)
        dp[N + 1][i2] = D(i2, N + 1);
    for (int i1 = N; i1 >= 0; --i1)
        dp[i1][N + 1] = D(i1, N + 1);
    for (int i1 = N; i1 >= 0; --i1)
        for (int i2 = N; i2 >= 0; --i2)
            dp[i1][i2] = min(D(i1, max(i1, i2) + 1) + dp[max(i1, i2) + 1][i2], D(i2, max(i1, i2) + 1) + dp[i1][max(i1, i2) + 1]);
    printf("%lld\n", (long long)round(dp[0][0]));
}