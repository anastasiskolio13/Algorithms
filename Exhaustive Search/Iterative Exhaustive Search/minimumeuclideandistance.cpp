#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#define MAXN 1000
using namespace std;

vector<int> X(MAXN);
vector<int> Y(MAXN);
int N;

double distance(int i, int j) {
	return sqrt((double)(X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]));
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &X[i], &Y[i]);
	double minDistance = DBL_MAX;
	for (int i = 0; i < N - 1; ++i)
		for (int j = i + 1; j < N; ++j)
			minDistance = min(minDistance, distance(i, j));
	printf("%lf\n", minDistance);
}