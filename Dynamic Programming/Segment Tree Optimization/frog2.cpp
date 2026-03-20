#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#define MAXN 100000
#define INF 1000000000
using namespace std;

set<pair<int, int>> S;
vector<int> H(MAXN);
vector<int> P(MAXN);
vector<int> dp(MAXN);
vector<pair<int, int>> T(4 * MAXN);
int N;
int K;

void Update(int lo, int hi, int v, int i, int x, int y) {
	if (lo == hi) {
		T[v].first = x;
		T[v].second = y;
		return;
	}
	int mid = (lo + hi) / 2;
	if (i <= mid)
		Update(lo, mid, 2 * v + 1, i, x, y);
	else
		Update(mid + 1, hi, 2 * v + 2, i, x, y);
	T[v].first = min(T[2 * v + 1].first, T[2 * v + 2].first);
	T[v].second = min(T[2 * v + 1].second, T[2 * v + 2].second);
}

int Query(int lo, int hi, int v, int qlo, int qhi, int id) {
	if (qlo <= lo && hi <= qhi)
		return T[v].first * !id + T[v].second * id;
	if (qlo > hi || qhi < lo)
		return INF;
	int mid = (lo + hi) / 2;
	int minLeft = Query(lo, mid, 2 * v + 1, qlo, qhi, id);
	int minRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi, id);
	return min(minLeft, minRight);
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &H[i]);
		S.insert({ H[i], i });
	}
	// Συμπίεση τιμών.
	int i = 0;
	for (auto stone : S)
		P[stone.second] = i++;
	// Αρχικοποίηση του T.
	for (int i = 0; i < N - 1; ++i)
		Update(0, N - 1, 0, P[i], INF, INF);
	// Οριακή συνθήκη.
	dp[N - 1] = 0;
	Update(0, N - 1, 0, P[N - 1], dp[N - 1] - H[N - 1], dp[N - 1] + H[N - 1]);
	for (int i = N - 2; i >= 0; --i) {
		if (i + K + 1 < N)
			Update(0, N - 1, 0, P[i + K + 1], INF, INF);
		auto it = S.upper_bound({ H[i], N });
		int RightSide = it != S.end() ? Query(0, N - 1, 0, P[it->second], N - 1, 1) - H[i] : INF;
		int LeftSide = it != S.begin() ? Query(0, N - 1, 0, 0, P[(--it)->second], 0) + H[i] : INF;
		dp[i] = min(RightSide, LeftSide);
		Update(0, N - 1, 0, P[i], dp[i] - H[i], dp[i] + H[i]);
	}
	printf("%d\n", dp[0]);
}