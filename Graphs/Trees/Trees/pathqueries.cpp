#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 200000
#define MAXM 200000
using namespace std;

struct edge {
	int v;
	int u;
	int w;
};

bool compareEdges(edge A, edge B) {
	return A.w < B.w;
}

struct query {
	int idx;
	int q;
};

bool compareQueries(query A, query B) {
	return A.q < B.q;
}

vector<edge> E(MAXN - 1);
vector<query> Q(MAXM);
vector<int> P(MAXN);
vector<int> S(MAXN);
vector<long long> A(MAXM);
int N;
int M;

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
	if (S[b] > S[a])
		swap(a, b);
	P[b] = a;
	S[a] += S[b];
}

long long Sum(long long N) {
	return N * (N - 1) / 2;
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N - 1; ++i) {
		scanf("%d %d %d", &E[i].v, &E[i].u, &E[i].w);
		--E[i].v;
		--E[i].u;
	}
	for (int i = 0; i < M; ++i) {
		scanf("%d", &Q[i].q);
		Q[i].idx = i;
	}
	sort(E.begin(), E.begin() + N - 1, compareEdges);
	sort(Q.begin(), Q.begin() + M, compareQueries);
	DSU();
	long long totalPairs = 0;
	int j = 0;
	for (int i = 0; i < M; ++i) {
		while (j < N - 1 && E[j].w <= Q[i].q) {
			int v = Find(E[j].v);
			int u = Find(E[j].u);
			totalPairs += Sum(S[v] + S[u]) - Sum(S[v]) - Sum(S[u]);
			Unite(v, u);
			++j;
		}
		A[Q[i].idx] = totalPairs;
	}
	for (int i = 0; i < M; ++i)
		printf("%lld ", A[i]);
}