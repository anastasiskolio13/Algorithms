#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#define MAXN 200000
#define MAXM 200000
#define MAXQ 200000
using namespace std;

vector<pair<int, int>> E(MAXM + 1);
vector<pair<int, int>> T(MAXQ);
vector<pair<int, int>> R(MAXQ);
vector<vector<int>> TS(MAXM + 1);
vector<int> P(MAXN);
vector<int> S(MAXN);
vector<int> A(MAXQ);
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
	a = Find(a);
	b = Find(b);
	if (S[b] > S[a])
		swap(a, b);
	P[b] = a;
	S[a] += S[b];
}

int main() {
	scanf("%d %d %d", &N, &M, &Q);
	for (int i = 1; i <= M; ++i) {
		scanf("%d %d", &E[i].first, &E[i].second);
		--E[i].first;
		--E[i].second;
	}
	for (int i = 0; i < Q; ++i) {
		scanf("%d %d", &T[i].first, &T[i].second);
		--T[i].first;
		--T[i].second;
	}
	for (int i = 0; i < Q; ++i)
		R[i] = { 1, M };
	for (int i = 0; i < ceil((double)log2(M)); ++i) {
		for (int j = 1; j <= M; ++j)
			TS[j].clear();
		for (int j = 0; j < Q; ++j) {
			auto [lo, hi] = R[j];
			if (lo < hi)
				TS[(lo + hi) / 2].push_back(j);
		}
		DSU();
		for (int j = 1; j <= M; ++j) {
			Unite(E[j].first, E[j].second);
			for (int k : TS[j]) {
				if (Find(T[k].first) == Find(T[k].second))
					R[k].second = j;
				else
					R[k].first = j + 1;
			}
		}
	}
	for (int i = 1; i <= M; ++i)
		TS[i].clear();
	for (int i = 0; i < Q; ++i)
		TS[R[i].first].push_back(i);
	DSU();
	for (int i = 1; i <= M; ++i) {
		Unite(E[i].first, E[i].second);
		for (int k : TS[i]) {
			if (Find(T[k].first) == Find(T[k].second))
				A[k] = i;
			else
				A[k] = -1;
		}
	}
	for (int i = 0; i < Q; ++i)
		printf("%d\n", T[i].first != T[i].second ? A[i] : 0);
}