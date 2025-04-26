#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
using namespace std;

vector<int> A(MAXN);
vector<int> B(MAXN);
vector<int> C(MAXN);
vector<pair<long long, int>> D;
int N;

int main() {
	//freopen("hydrocabons.in", "r", stdin);
	//freopen("hydrocabons.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d %d %d", &A[i], &B[i], &C[i]);
	for (int i = 0; i < N; ++i) {
		long long efficiency = 3000 * (long long) A[i] - (long long) A[i] * B[i] - 75 * (long long) A[i] * C[i];
		if (efficiency > 0) {
			D.push_back({ efficiency , i });
		}
	}
	sort(D.begin(), D.end(), greater<pair<long long, int>>());
	printf("%d\n", D.size());
	for (int i = 0; i < D.size(); ++i)
		printf("%d ", D[i].second + 1);
}