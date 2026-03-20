#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#define MAXN 100000
#define eps 1e-6
using namespace std;

vector<int> A(MAXN + 1);
vector<int> PS(MAXN + 1);
int N;
int D;

pair<int, int> SegmentWithAvgSumAtLeast(double x) {
    double PM = DBL_MAX;
    int PM_idx;
    for (int j = D; j <= N; ++j) {
        if (PS[j - D] - (j - D) * x < PM) {
            PM = PS[j - D] - (j - D) * x;
            PM_idx = j - D;
        }
        if (PS[j] - j * x >= PM)
            return { PM_idx + 1, j };
    }
    return { -1, -1 };
}

int main() {
    scanf("%d %d", &N, &D);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &A[i]);
        PS[i] = PS[i - 1] + A[i];
    }
    double lo = 0;
    double hi = 100;
    while (hi - lo > eps) {
        double mid = (lo + hi) / 2;
        if (SegmentWithAvgSumAtLeast(mid) != make_pair(-1, -1))
            lo = mid;
        else
            hi = mid;
    }
    pair<int, int> Segment = SegmentWithAvgSumAtLeast(lo);
    printf("%d %d", Segment.first, Segment.second);
}