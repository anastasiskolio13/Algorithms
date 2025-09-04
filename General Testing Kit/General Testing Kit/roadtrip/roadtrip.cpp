#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct edge {
	int v;
	int u;
	int d;
};

bool compareEdges(edge A, edge B) {
	return A.d < B.d;
}

vector<edge> E;
vector<pair<int, int>> T;
vector<pair<int, int>> R;
vector<vector<int>> TS;
vector<int> P;
vector<int> S;
int N;
int M;
int Q;

void DSU() {
	for (int a = 1; a <= N; ++a) {
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

void SolveTestCase(int t) {
	E.clear();
	T.clear();
	R.clear();
	TS.clear();
	P.clear();
	S.clear();
	string filenameOne = "input" + to_string(t) + ".txt";
	string filenameTwo = "output" + to_string(t) + ".txt";
	freopen(filenameOne.c_str(), "r", stdin);
	scanf("%d %d", &N, &M);
	P.resize(N + 1);
	S.resize(N + 1);
	E.resize(M + 1);
	TS.resize(M + 1);
	for (int i = 1; i <= M; ++i)
		scanf("%d %d %d", &E[i].v, &E[i].u, &E[i].d);
	scanf("%d", &Q);
	T.resize(Q + 1);
	R.resize(Q + 1);
	for (int i = 1; i <= Q; ++i)
		scanf("%d %d", &T[i].first, &T[i].second);
	sort(E.begin() + 1, E.begin() + M + 1, compareEdges);
	for (int i = 1; i <= Q; ++i)
		R[i] = { 1, M };
	for (int i = 0; i < ceil((double)log2(M)); ++i) {
		for (int j = 1; j <= M; ++j)
			TS[j].clear();
		for (int j = 1; j <= Q; ++j) {
			auto [lo, hi] = R[j];
			if (lo < hi)
				TS[(lo + hi) / 2].push_back(j);
		}
		DSU();
		for (int j = 1; j <= M; ++j) {
			Unite(E[j].v, E[j].u);
			for (int k : TS[j]) {
				if (Find(T[k].first) == Find(T[k].second)) 
					R[k].second = j;
				else 
					R[k].first = j + 1;
			}
		}
	}
	vector<int> myAnswer(Q + 1);
	vector<int> correctAnswer(Q + 1);
	for (int i = 1; i <= Q; ++i)
		myAnswer[i] = E[R[i].first].d;
	freopen(filenameTwo.c_str(), "r", stdin);
	for (int i = 1; i <= Q; ++i)
		scanf("%d", &correctAnswer[i]);
	for (int i = 1; i <= Q; ++i) {
		if (myAnswer[i] != correctAnswer[i]) {
			printf("WA\n");
			return;
		}
	}
	printf("AC\n");
}

int main() {
	int numberOfTestCases = 20;
	for (int i = 1; i <= numberOfTestCases; ++i)
		SolveTestCase(i);
}