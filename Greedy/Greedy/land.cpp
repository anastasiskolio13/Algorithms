#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#define MAXN 50000
using namespace std;

priority_queue<double, vector<double>, greater<double>> Q;
vector<double> X(MAXN);
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%lf", &X[i]);
        Q.push(X[i]);
    }
    double totalCost = 0;
    while (Q.size() > 1) {
        double p1 = Q.top();
        Q.pop();
        double p2 = Q.top();
        Q.pop();
        double p1_U_p2 = p1 + p2;
        totalCost += p1_U_p2;
        Q.push(p1_U_p2);
    }
    totalCost = round(totalCost * 100.0) / 100.0;
    printf("%.2lf\n", totalCost);
}