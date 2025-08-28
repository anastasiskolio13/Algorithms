#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#define MAXN 100000
using namespace std;

struct interval {
	int L;
	int R;
};

bool compareIntervals(interval A, interval B) {
	return A.L < B.L || A.L == B.L && A.R > B.R;
}

auto cmp = [](auto& A, auto& B) {
	return A.first == B.first ? A.second > B.second : A.first < B.first;
};

set<pair<int, int>, decltype(cmp)> S(cmp);
vector<interval> I(MAXN);
vector<int> P(MAXN);
vector<int> dp(MAXN);
vector<int> parent(MAXN, -1);
vector<int> path;
vector<pair<int, int>> T(4 * MAXN);
int N;

void Update(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = { dp[i], i };
		return;
	}
	int mid = (lo + hi) / 2;
	if (P[i] <= mid)
		Update(lo, mid, 2 * v + 1, i);
	else
		Update(mid + 1, hi, 2 * v + 2, i);
	T[v] = T[2 * v + 1].first >= T[2 * v + 2].first ? T[2 * v + 1] : T[2 * v + 2];
}

pair<int, int> Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return { 0, -1 };
	int mid = (lo + hi) / 2;
	pair<int, int> QLeft = Query(lo, mid, 2 * v + 1, qlo, qhi);
	pair<int, int> QRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi);
	return QLeft.first >= QRight.first ? QLeft : QRight;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &I[i].L, &I[i].R);
	sort(I.begin(), I.begin() + N, compareIntervals);
	for (int i = 0; i < N; ++i)
		S.insert({ I[i].R, i });
	int i = 0;
	for (pair<int, int> el : S)
		P[el.second] = i++;
	for (int i = N - 1; i >= 0; --i) {
		pair<int, int> QueryAnswer = Query(0, N - 1, 0, 0, P[i] - 1);
		dp[i] = QueryAnswer.first + 1;
		parent[i] = QueryAnswer.second == -1 ? i : QueryAnswer.second;
		Update(0, N - 1, 0, i);
	}
	int argmax = 0;
	for (int i = 1; i < N; ++i)
		if (dp[i] > dp[argmax])
			argmax = i;
	printf("%d\n", dp[argmax]);
	i = argmax;
	while (i != parent[i]) {
		path.push_back(i);
		i = parent[i];
	}
	path.push_back(i);
	for (int i : path)
		printf("%d %d\n", I[i].L, I[i].R);
}