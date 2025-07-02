#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#define MAXN 1000000
using namespace std;

vector<int> X(2 * MAXN + 1);
int N;

int main() {
	scanf("%d", &N);
	int totalSumOfElements = 0;
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &X[i]);
		X[i + N] = X[i];
		totalSumOfElements += X[i];
	}
	int minimumDifference = INT_MAX;
	for (int i = 1; i <= N; ++i) {
		int sumOfElements = 0;
		for (int j = i; j <= i + N; ++j) {
			sumOfElements += X[j];
			minimumDifference = min(minimumDifference, abs(totalSumOfElements - 2 * sumOfElements));
		}
	}
	printf("%d\n", minimumDifference);
}