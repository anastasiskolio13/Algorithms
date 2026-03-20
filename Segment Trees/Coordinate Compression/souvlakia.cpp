#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#define MAXN 100000
#define INF 2e9
using namespace std;

struct point {
	int X;
	int Y;
	int Z;
	int idx;
};

bool comparePoints(point A, point B) {
	return A.X < B.X;
}

set<pair<int, int>> Q;
set<pair<int, int>> S;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<vector<int>> TS(MAXN);
vector<point> P(MAXN);
vector<int> D(MAXN);
vector<int> DA(MAXN);
vector<int> DB(MAXN);
vector<int> DC(MAXN);
vector<int> I(MAXN);
vector<int> T(4 * MAXN);
vector<bool> isDominant(MAXN);
int N;
int M;
int A;
int B;
int C;
int L;

vector<int> Dijsktra(int s) {
	fill(D.begin(), D.begin() + N, INF);
	D[s] = 0;
	Q.insert({ 0, s });
	while (!Q.empty()) {
		auto [d, v] = *Q.begin();
		Q.erase(Q.begin());
		if (d > D[v])
			continue;
		for (auto [u, w] : Adj[v]) {
			if (D[v] + w < D[u]) {
				D[u] = D[v] + w;
				Q.insert({ D[u], u });
			}
		}
	}
	return D;
}

void Update(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = P[i].Z;
		return;
	}
	int mid = (lo + hi) / 2;
	if (I[i] <= mid)
		Update(lo, mid, 2 * v + 1, i);
	else
		Update(mid + 1, hi, 2 * v + 2, i);
	T[v] = min(T[2 * v + 1], T[2 * v + 2]);
}

int Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return INF;
	int mid = (lo + hi) / 2;
	int minLeft = Query(lo, mid, 2 * v + 1, qlo, qhi);
	int minRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi);
	return min(minLeft, minRight);
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[--v].push_back({ --u, w });
		Adj[u].push_back({ v, w });
	}
	scanf("%d %d %d %d", &A, &B, &C, &L);
	DA = Dijsktra(--A);
	DB = Dijsktra(--B);
	DC = Dijsktra(--C);
	for (int i = 0; i < N; ++i)
		P[i] = { DA[i], DB[i], DC[i], i };
	sort(P.begin(), P.begin() + N, comparePoints);
	int j = 0;
	for (int i = 0; i < N; ++i) {
		while (j < N && P[i].X == P[j].X)
			++j;
		if (j < N)
			TS[j].push_back(i);
	}
	for (int i = 0; i < N; ++i)
		S.insert({ P[i].Y, i });
	int i = 0;
	for (auto [_, index] : S)
		I[index] = i++;
	fill(T.begin(), T.begin() + 4 * N, INF);
	for (int i = 0; i < N; ++i) {
		for (int j : TS[i])
			Update(0, N - 1, 0, j);
		auto it = S.lower_bound({ P[i].Y, -1 });
		if (it == S.begin())
			isDominant[P[i].idx] = true;
		else
			isDominant[P[i].idx] = P[i].Z <= Query(0, N - 1, 0, 0, I[(--it)->second]);
	}
	while (L--) {
		int i;
		scanf("%d", &i);
		printf(isDominant[--i] ? "YES\n" : "NO\n");
	}
}