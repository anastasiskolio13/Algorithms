#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 7
#define MAXM 5000
using namespace std;

struct query {
	int Si;
	int Sj;
	int Ti;
	int Tj;
	int idx;
};

vector<vector<int>> A(MAXN, vector<int>(MAXM));
int N;
int M;
int T;



void DivideAndConquer(int lo, int hi, vector<query> Q) {
	if (lo == hi) {

	}
	int mid = (lo + hi) / 2;

}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			scanf("%d", &A[i][j]);
	scanf("%d", &T);
	vector<query> Q(T);
	for (int i = 0; i < T; ++i) {
		scanf("%d %d %d %d", &Q[i].Si, &Q[i].Sj, &Q[i].Ti, &Q[i].Tj);
		Q[i].idx = i;
	}
}