#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 100000
#define eps 1e-6
using namespace std;

vector<int> A(MAXN + 1);
vector<int> B(MAXN + 1);
vector<long long> PSA(MAXN + 1);
vector<long long> PSB(MAXN + 1);
int N;

pair<int, int> isPossibleToAchieveAverage(double K) {
	int argmax = 1;
	int argmin = 1;
	for (int i = 2; i <= N; ++i) {
		if (PSA[i] - K * i > PSA[argmax] - K * argmax)
			argmax = i;
		if (K * i - PSB[i] < K * argmin - PSB[argmin])
			argmin = i;
	}
	return PSA[argmax] - K * argmax >= K * argmin - PSB[argmin] ? make_pair(argmax, argmin) : make_pair(-1, -1);
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &A[i]);
		PSA[i] = PSA[i - 1] + A[i];
	}
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &B[i]);
		PSB[i] = PSB[i - 1] + B[i];
	}
	double lo = 0;
	double hi = 1e14;
	while (hi - lo > eps) {
		double mid = (lo + hi) / 2;
		if (isPossibleToAchieveAverage(mid) != make_pair(-1, -1))
			lo = mid;
		else
			hi = mid;
	}
	pair<int, int> res = isPossibleToAchieveAverage(lo);
	printf("%d %d\n", res.first, res.second);
}