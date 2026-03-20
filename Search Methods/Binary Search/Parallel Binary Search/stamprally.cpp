#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#define MAXN 100000
#define MAXM 100000
#define MAXQ 100000
using namespace std;

vector<tuple<int, int, int>> T(MAXQ);
vector<pair<int, int>> E(MAXM);
vector<pair<int, int>> R(MAXQ);
vector<vector<int>> TS(MAXM);
vector<int> P(MAXN);
vector<int> S(MAXN);
int N;
int M;
int Q;

void DSU() {
	for (int a = 0; a < N; ++a) {
		P[a] = a;
		S[a] = 1;
	}
}

int Find(int a) {
	if (P[a] == a)
		return a;
	return P[a] = Find(P[a]);
}

void Unite(int a, int b) {
	if (a == b)
		return;
	if (S[b] > S[a])
		swap(a, b);
	P[b] = a;
	S[a] += S[b];
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; ++i) {
		scanf("%d %d", &E[i].first, &E[i].second);
		--E[i].first;
		--E[i].second;
	}
	scanf("%d", &Q);
	for (int i = 0; i < Q; ++i) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		T[i] = { --x, --y, z };
		R[i] = { 0, M - 1 };
	}
	for (int i = 0; i < ceil(log2(M)); ++i) {
		for (int i = 0; i < M; ++i)
			TS[i].clear();
		for (int i = 0; i < Q; ++i) {
			auto [lo, hi] = R[i];
			if (lo < hi)
				TS[(lo + hi) / 2].push_back(i);
		}
		DSU();
		for (int i = 0; i < M; ++i) {
			Unite(Find(E[i].first), Find(E[i].second));
			for (int j : TS[i]) {
				int a = Find(get<0>(T[j]));
				int b = Find(get<1>(T[j]));
				int numberOfNodesTheyCanVisit = S[a] + S[b] * (a != b);
				if (numberOfNodesTheyCanVisit >= get<2>(T[j]))
					R[j].second = i;
				else
					R[j].first = i + 1;
			}
		}
	}
	for (int i = 0; i < Q; ++i)
		printf("%d\n", R[i].first + 1);
}