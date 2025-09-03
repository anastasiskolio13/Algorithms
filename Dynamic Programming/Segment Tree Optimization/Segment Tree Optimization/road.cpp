#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#define MAXN 100000
#define MAXK 50
using namespace std;

set<pair<int, int>> S;
vector<int> A(MAXN);
vector<int> P(MAXN);
vector<int> T(4 * MAXN);
vector<vector<int>> dp(MAXN, vector<int>(MAXK + 1));
int N;
int K;

void Update(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = dp[i];
		return;
	}
	int mid = (lo + hi) / 2;
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
		S.insert({ A[i], i });
	}
	int i = 0;
	for (pair<int, int> el : S)
		P[el.second] = i++;
	for (int i = N - 1; i >= 0; --i) { 
		for (int j = 0; j <= K; ++j) {

		}
	}
}