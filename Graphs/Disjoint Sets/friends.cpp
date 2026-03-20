#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 200000
using namespace std;

vector<int> P(MAXN);
vector<int> S(MAXN);
int N;
int M;

void DisjointSets() {
	for (int a = 0; a < N; ++a) {
		P[a] = a;
		S[a] = 1;
	}
}

int Find(int a) {
	return P[a] == a ? a : P[a] = Find(P[a]);
}

int Unite(int a, int b) {
	if (S[b] > S[a])
		swap(a, b);
	P[b] = a;
	S[a] += S[b];
	return S[a];
}

int main() {
	scanf("%d %d", &N, &M);
	DisjointSets();
	int minimumNumberOfTeams = 1;
	for (int i = 0; i < M; ++i) {
		int v, u;
		scanf("%d %d", &v, &u);
		if (Find(--v) != Find(--u))
			minimumNumberOfTeams = max(minimumNumberOfTeams, Unite(Find(v), Find(u)));
	}
	printf("%d\n", minimumNumberOfTeams);
}