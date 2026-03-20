#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1000
#define INF 1e9
using namespace std;

vector<int> A(MAXN);
int N;

int C(int i, int j) {
	int maxOne, maxTwo, maxThree;
	maxOne = maxTwo = maxThree = -0;
	for (int k = i; k <= j; ++k) {
		if (A[k] >= maxOne) {
			maxThree = maxTwo;
			maxTwo = maxOne;
			maxOne = A[k];
		}
		else if (A[k] >= maxTwo) {
			maxThree = maxTwo;
			maxTwo = A[k];
		}
		else if (A[k] >= maxThree) {
			maxThree = A[k];
		}
	}
	return maxOne + maxTwo + maxThree + i - j;
}

bool isMongeConditionSatisfied(int a, int b, int c, int d) {
	return C(a, c) + C(b, d) >= C(a, d) + C(b, c);
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	int k = 0;
	for (int a = 1; a <= N; ++a)
		for (int b = a; b <= N; ++b)
			for (int c = b; c <= N; ++c)
				for (int d = c; d <= N; ++d)
					if (!isMongeConditionSatisfied(a, b, c, d))
						++k;
					//printf(isMongeConditionSatisfied(a, b, c, d) ? "YES\n" : "NO\n");
	printf("%d\n", k);
}