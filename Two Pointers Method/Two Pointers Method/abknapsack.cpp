#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
#define MAXM 100000
using namespace std;

vector<int> X(MAXN);
vector<int> Y(MAXM);
int N;
int M;
int S;
int A;
int B;

int main() {
	scanf("%d %d %d %d %d", &N, &M, &S, &A, &B);
	for (int i = 0; i < N; ++i)
		scanf("%d", &X[i]);
	for (int i = 0; i < M; ++i)
		scanf("%d", &Y[i]);
	sort(X.begin(), X.begin() + N, greater<int>());
	sort(Y.begin(), Y.begin() + M, greater<int>());
	int i = 0;
	int j = 0;
	long long sumX = 0;
	long long sumY = 0;
	long long sumA = 0;
	long long sumB = 0;
	while (i < N && sumA + A <= S) {
		sumA += A;
		sumX += X[i++];
	}
	i -= i != 0;
	long long maximumTotalCost = sumX;
	while (j < M && sumB + B <= S) {
		sumB += B;
		sumY += Y[j++];
		while (i >= 0 && sumA + sumB > S) {
			sumA -= A;
			sumX -= X[i--];
		}
		maximumTotalCost = max(maximumTotalCost, sumX + sumY);
	}
	printf("%lld\n", maximumTotalCost);
}