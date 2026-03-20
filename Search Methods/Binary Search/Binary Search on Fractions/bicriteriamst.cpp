#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#define MAXN 50000
#define MAXM 200000
#define eps 1e-6
using namespace std;

vector<array<int, 4>> E(MAXM);
vector<array<double, 4>> Ex(MAXM);
vector<int> P(MAXN);
vector<int> S(MAXN);
int N;
int M;

void disjointSets() {
    for (int a = 0; a < N; ++a) {
        P[a] = a;
        S[a] = 1;
    }
}

int find(int a) {
    return a == P[a] ? a : P[a] = find(P[a]);
}

void unite(int a, int b) {
    if (S[a] < S[b])
        swap(a, b);
    P[b] = a;
    S[a] += S[b];
}

pair<long, long> canAchieveAverageAtLeast(double x) {
    for (int i = 0; i < M; ++i) {
        Ex[i] = {x * E[i][3] - E[i][2], (double)E[i][0], (double)E[i][1]};
        Ex[i][3] = i;
    }
    // MST_Kruskal
    disjointSets();
    sort(Ex.begin(), Ex.begin() + M);
    long Sp = 0;
    long Sw = 0;
    for (int i = 0; i < M; ++i) {
        if (find(Ex[i][1]) != find(Ex[i][2])) {
            Sp += E[Ex[i][3]][2];
            Sw += E[Ex[i][3]][3];
            unite(find(Ex[i][1]), find(Ex[i][2]));
        }
    }
    if (x * Sw <= Sp) 
        return {Sp, Sw};
    else 
        return {-1, -1};
}


int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; ++i) {
        scanf("%d %d %d %d", &E[i][0], &E[i][1], &E[i][2], &E[i][3]);
        --E[i][0];
        --E[i][1];
    }
    double lo = 0;
    double hi = 1e10;
    while (hi - lo > eps) {
        double mid = (lo + hi) / 2;
        pair<long, long> res = canAchieveAverageAtLeast(mid);
        if (res != make_pair<long, long>(-1, -1))
            lo = mid;
        else 
            hi = mid;
    }
    pair<long, long> res = canAchieveAverageAtLeast(lo);
    printf("%ld %ld\n", res.first / __gcd(res.first, res.second), res.second / __gcd(res.first, res.second));
}