#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1000
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