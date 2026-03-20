#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <array>
#define MAXN 800
#define INF 1000000
using namespace std;

queue<pair<int, int>> Qb;
queue<array<int, 3>> Qm;
vector<vector<char>> A(MAXN, vector<char>(MAXN));
vector<vector<int>> Db(MAXN, vector<int>(MAXN));
vector<vector<int>> Dm(MAXN, vector<int>(MAXN));
int N;
int S;
int Si;
int Sj;
int Ti;
int Tj;

void BeesGoTo(int i, int j, int D) {
	if (i >= 0 && i < N && j >= 0 && j < N && A[i][j] != 'T' && A[i][j] != 'D' && Db[i][j] == INF) {
		Db[i][j] = D + 1;
		Qb.push({ i, j });
	}
}

void BeesBreadthFirstSearch() {
	while (!Qb.empty()) {
		int i = Qb.front().first;
		int j = Qb.front().second;
		Qb.pop();
		BeesGoTo(i + 1, j, Db[i][j]);
		BeesGoTo(i - 1, j, Db[i][j]);
		BeesGoTo(i, j + 1, Db[i][j]);
		BeesGoTo(i, j - 1, Db[i][j]);
	}
}

void MechoGoTo(int i, int j, int s, int D) {
	if (i >= 0 && i < N && j >= 0 && j < N && A[i][j] != 'T' && A[i][j] != 'H' && Dm[i][j] == INF && D + !s < Db[i][j]) {
		Dm[i][j] = D + !s;
		Qm.push({ i, j, !s ? S : s - 1});
	}
}


bool MechoBreadthFirstSearch(int T) {
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			Dm[i][j] = INF;
	Dm[Si][Sj] = T;
	Qm.push({ Si, Sj, S });
	while (!Qm.empty()) {
		int i = Qm.front()[0];
		int j = Qm.front()[1];
		int s = Qm.front()[2];
		Qm.pop();
		MechoGoTo(i + 1, j, s, Dm[i][j]);
		MechoGoTo(i - 1, j, s, Dm[i][j]);
		MechoGoTo(i, j + 1, s, Dm[i][j]);
		MechoGoTo(i, j - 1, s, Dm[i][j]);
	}
	return Dm[Ti][Tj] != INF;
}

int main() {
	scanf("%d %d", &N, &S);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			Db[i][j] = INF;
			scanf(" %c", &A[i][j]);
			if (A[i][j] == 'H') {
				Db[i][j] = 0;
				Qb.push({ i, j });
			}
			else if (A[i][j] == 'M') {
				Si = i;
				Sj = j;
			}
			else if (A[i][j] == 'D') {
				Ti = i;
				Tj = j;
			}
		}
	}
	BeesBreadthFirstSearch();
	int lo = 0;
	int hi = N * N;
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
		if (MechoBreadthFirstSearch(mid))
			lo = mid;
		else
			hi = mid - 1;
	}
	printf("%d\n", MechoBreadthFirstSearch(lo) ? lo : -1);
}