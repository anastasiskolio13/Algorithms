#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#define MAXN 40
using namespace std;

set<pair<long long, int>> S;
vector<int> H(MAXN + 1);
vector<int> G(MAXN + 1);
vector<int> P(1 << (MAXN / 2));
vector<int> T(4 * (1 << (MAXN / 2)));
vector<pair<int, long long>> L;
vector<pair<int, long long>> R;
int N;
long long K;
long long differentWaysToPlayTheGame;

void FindLeftFeasibleSubsets(int i, int p, long long s) {
	if (i == ceil((double)N / 2) + 1) {
		if (p != 0)
			L.push_back({ p, s });
		differentWaysToPlayTheGame += (s >= K);
		return;
	}
	FindLeftFeasibleSubsets(i + 1, p, s);
	if (H[i] >= p)
		FindLeftFeasibleSubsets(i + 1, H[i], s + G[i]);
}

void FindRightFeasibleSubsets(int i, int p, long long s) {
	if (i == ceil((double)N / 2)) {
		if (p != 2e9)
			R.push_back({ p, s });
		differentWaysToPlayTheGame += (s >= K);
		return;
	}
	FindRightFeasibleSubsets(i - 1, p, s);
	if (H[i] <= p)
		FindRightFeasibleSubsets(i - 1, H[i], s + G[i]);
}

void Update(int lo, int hi, int v, int i, int x) {
	if (lo == hi) {
		T[v] = x;
		return;
	}
	int mid = (lo + hi) / 2;
	if (P[i] <= mid)
		Update(lo, mid, 2 * v + 1, i, x);
	else
		Update(mid + 1, hi, 2 * v + 2, i, x);
	T[v] = T[2 * v + 1] + T[2 * v + 2];
}

int Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	int sumLeft = Query(lo, mid, 2 * v + 1, qlo, qhi);
	int sumRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi);
	return sumLeft + sumRight;
}

int main() {
	scanf("%d %lld", &N, &K);
	for (int i = 1; i <= N; ++i)
		scanf("%d %d", &H[i], &G[i]);
	FindLeftFeasibleSubsets(1, 0, 0);
	FindRightFeasibleSubsets(N, 2e9, 0);
	sort(L.begin(), L.end());
	sort(R.begin(), R.end());
	for (int i = 0; i < R.size(); ++i)
		S.insert({ R[i].second, i });
	int i = 0;
	for (pair<long long, int> x : S)
		P[x.second] = i++;
	for (int i = 0; i < R.size(); ++i)
		Update(0, R.size() - 1, 0, i, 1);
	int j = 0;
	for (int i = 0; i < L.size(); ++i) {
		while (j < R.size() && L[i].first > R[j].first) {
			Update(0, R.size() - 1, 0, j, 0);
			++j;
		}
		auto it = S.lower_bound({ K - L[i].second, -1 });
		if (it != S.end())
			differentWaysToPlayTheGame += Query(0, R.size() - 1, 0, P[it->second], R.size() - 1);
	}
	printf("%lld\n", differentWaysToPlayTheGame);
}
