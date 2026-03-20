#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#define MAXN 100000
using namespace std;

set<pair<long long, int>> S;
vector<long long> H(MAXN);
vector<int> I(MAXN);
vector<pair<int, int>> T(4 * MAXN);
vector<int> dp(MAXN);
vector<int> P(MAXN);
vector<int> solution;
int N;
int D;

void Update(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = { dp[i], i };
		return;
	}
	int mid = (lo + hi) / 2;
	if (I[i] <= mid)
		Update(lo, mid, 2 * v + 1, i);
	else
		Update(mid + 1, hi, 2 * v + 2, i);
	T[2 * v + 1].first >= T[2 * v + 2].first ? T[v] = T[2 * v + 1] : T[v] = T[2 * v + 2];
}

pair<int, int> Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return { 0, 0 };
	int mid = (lo + hi) / 2;
	pair<int, int> maxLeft = Query(lo, mid, 2 * v + 1, qlo, qhi);
	pair<int, int> maxRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi);
	return maxLeft.first >= maxRight.first ? maxLeft : maxRight;
}

int main() {
	scanf("%d %d", &N, &D);
	for (int i = 0; i < N; ++i) {
		scanf("%lld", &H[i]);
		S.insert({ H[i], i });
	}
	int i = 0;
	for (auto [value, index] : S)
		I[index] = i++;
	for (int i = N - 1; i >= 0; --i) {
		P[i] = i;
		dp[i] = 1;
		auto iteratorOne = S.lower_bound({H[i] + D, -1});
		auto iteratorTwo = S.upper_bound({H[i] - D, N});
		if (iteratorOne != S.end() && dp[i] < Query(0, N - 1, 0, I[iteratorOne->second], N - 1).first + 1) {
			P[i] = Query(0, N - 1, 0, I[iteratorOne->second], N).second;
			dp[i] = dp[P[i]] + 1;
		}
		if (iteratorTwo != S.begin() && dp[i] < Query(0, N - 1, 0, 0, I[(--iteratorTwo)->second]).first + 1) {
			P[i] = Query(0, N - 1, 0, 0, I[(iteratorTwo)->second]).second;
			dp[i] = dp[P[i]] + 1;
		}
		Update(0, N - 1, 0, i);
	}
	int argmax = 0;
	for (int i = 1; i < N; ++i)
		if (dp[i] > dp[argmax])
			argmax = i;
	i = argmax;
	while (i != P[i]) {
		solution.push_back(i);
		i = P[i];
	}
	solution.push_back(i);
	printf("%d\n", solution.size());
	for (int i : solution)
		printf("%d ", i + 1);
}