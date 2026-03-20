#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
#define eps 1e-6
using namespace std;

vector<int> A(MAXN + 1);
vector<int> PS(MAXN + 1);
int N;

bool canAchieve(double x) {
	double prefixMaximum = 2 * x - PS[1];
	for (int j = 2; j <= N - 1; ++j) {
		if (prefixMaximum >= x * (j - N + 1) + PS[N] - PS[j])
			return true;
		prefixMaximum = max(prefixMaximum, j * x - PS[j - 1]);
	}
	return false;
}

int main() {
	freopen("sabotage.in", "r", stdin);
	freopen("sabotage.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &A[i]);
		PS[i] = PS[i - 1] + A[i];
	}
	double lo = *min_element(A.begin() + 1, A.begin() + N + 1);
	double hi = *max_element(A.begin() + 1, A.begin() + N + 1);
	while (hi - lo > eps) {
		double mid = (lo + hi) / 2;
		if (canAchieve(mid))
			hi = mid;
		else
			lo = mid;
	}
	printf("%.3lf\n", lo);
}