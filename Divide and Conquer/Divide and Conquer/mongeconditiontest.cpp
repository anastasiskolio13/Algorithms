#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1000
using namespace std;

vector<int> A(MAXN);
int N;

int C(int i, int j) {
	int min_el = INT_MAX;
	int max_el = INT_MIN;
	for (int k = i; k <= j; ++k) {
		min_el = min(min_el, A[k]);
		max_el = max(max_el, A[k]);
	}
	return (max_el - min_el) * i;
}

bool isMongeConditionSatisfied(int a, int b, int c, int d) {
	return C(a, c) + C(b, d) >= C(a, d) + C(b, c);
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	int k = 0;
	for (int a = 0; a < N; ++a)
		for (int b = a; b < N; ++b)
			for (int c = b; c < N; ++c)
				for (int d = c; d < N; ++d)
					if (!isMongeConditionSatisfied(a, b, c, d))
						++k;
					//printf(isMongeConditionSatisfied(a, b, c, d) ? "YES\n" : "NO\n");
	printf("%d\n", k);
}