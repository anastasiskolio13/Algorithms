#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1000
#define INF 1e9
using namespace std;

vector<int> A(MAXN);
int N;

int C(int i, int j) {
	int sum = 0;
	for (int k = i; k <= j; ++k) {
		sum += A[k] * (k - i + 1);
	}
	return sum;
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