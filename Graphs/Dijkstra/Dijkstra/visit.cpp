#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <array>
#define MAXN 60000
#define MAXK MAXN
using namespace std;

vector<vector<pair<int, int>>> Adj(MAXN);
vector<int> P(MAXK);
int N;
int M;
int A;
int B;
int T;
int K;

int main() {
	scanf("%d %d %d %d %d %d", &N, &M, &A, &B, &T, &K);
	scanf("%d", &P[0]);
	--P[0];
	for (int i = 1; i < K; ++i) {
		scanf("%d", &P[i]);
		--P[i];
	}
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[--v].push_back({ --u, w });
		Adj[u].push_back({ v, w });
	}

}