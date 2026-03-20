#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 24
using namespace std;

vector<int> X(MAXN);
vector<int> Y(MAXN);
vector<vector<long long>> dp(1 << MAXN, vector<long long>(MAXN));
int Xs;
int Ys;
int N;

int main() {
	scanf("%d %d %d", &Xs, &Ys, &N);
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &X[i], &Y[i]);
}