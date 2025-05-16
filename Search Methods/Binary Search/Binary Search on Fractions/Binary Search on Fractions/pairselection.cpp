#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
#define eps 1e-6
using namespace std;

vector<int> A(MAXN);
vector<int> B(MAXN);
vector<double> C(MAXN);
int N;
int K;
long S;

bool canAchieveAverageAtLeast(double X) {
    for (int i = 0; i < N; ++i)
        C[i] = X * B[i] - A[i];
    nth_element(C.begin(), C.begin() + K, C.begin() + N);
    double Sc = 0;
    for (int i = 0; i < K; ++i)
        Sc += C[i];
    return Sc <= 0;
}

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &A[i], &B[i]);
        S += A[i];
    }
    double lo = 0;
    double hi = S;
    while (hi - lo > eps) {
        double mid = (lo + hi) / 2;
        if (canAchieveAverageAtLeast(mid))
            lo = mid;
        else
            hi = mid;
    }
    printf("%lf\n", lo);
}