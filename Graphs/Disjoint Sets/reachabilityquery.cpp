#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 200000
using namespace std;

vector<bool> isBlack(MAXN);
vector<int> P(MAXN);
vector<int> S(MAXN);
vector<int> B(MAXN);
int N;
int Q;

void DSU() {
	for (int a = 0; a < N; ++a) {
		P[a] = a;
		S[a] = 1;
		B[a] = 0;
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
	B[a] += B[b];
}

int main() {
	scanf("%d %d", &N, &Q);
	for (int i = 0; i < N; ++i)
		isBlack[i] = false;
	DSU();
	while (Q--) {
		int a, b, c;
		scanf("%d %d", &a, &b);
		--b;
		switch (a)
		{
		case 1: scanf("%d", &c); Unite(Find(b), Find(--c)); break;
		case 2: isBlack[b] = !isBlack[b]; B[Find(b)] += isBlack[b] ? 1 : -1; break;
		default: printf(B[Find(b)] ? "Yes\n" : "No\n");
		}
	}
}