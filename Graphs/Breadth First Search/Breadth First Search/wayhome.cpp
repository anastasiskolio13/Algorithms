#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#define MAXN 700
#define MAXM 700
#define INF 1e9
using namespace std;

queue<pair<int, int>> YQ;
queue<pair<int, int>> PQ;
vector<vector<char>> A(MAXN, vector<char>(MAXM));
vector<vector<int>> YT(MAXN, vector<int>(MAXM));
vector<vector<int>> PT(MAXN, vector<int>(MAXM));
vector<vector<int>> PVT(MAXN, vector<int>(MAXM));
int T;
int N;
int M;
int Yi;
int Yj;
int Pi;
int Pj;
int Hi;
int Hj;


void YouGoTo(int i, int j, int T) {
	if (i >= 0 && i < N && j >= 0 && j < M && A[i][j] != '#' && YT[i][j] == INF && T + 1 < PVT[i][j]) {
		YT[i][j] = T + 1;
		YQ.push({ i, j });
	}
}

void YouBFS() {
	YT[Yi][Yj] = 0;
	YQ.push({ Yi, Yj });
	while (!YQ.empty()) {
		auto [i, j] = YQ.front();
		YQ.pop();
		if (i == Hi && j == Hj) {
			printf("YES\n");
			return;
		}
		YouGoTo(i - 1, j, YT[i][j]);
		YouGoTo(i + 1, j, YT[i][j]);
		YouGoTo(i, j - 1, YT[i][j]);
		YouGoTo(i, j + 1, YT[i][j]);
	}
	printf("NO\n");
}

void MarkVisibleCells(int i, int j) {
	// Above. 
	int tmpi = i - 1;
	while (tmpi >= 0 && A[tmpi][j] != '#' && PVT[tmpi][j] == INF)
		PVT[tmpi--][j] = PT[i][j];
	// Below. 
	tmpi = i + 1;
	while (tmpi < N && A[tmpi][j] != '#' && PVT[tmpi][j] == INF)
		PVT[tmpi++][j] = PT[i][j];
	// Left. 
	int tmpj = j - 1;
	while (tmpj >= 0 && A[i][tmpj] != '#' && PVT[i][tmpj] == INF)
		PVT[i][tmpj--] = PT[i][j];
	// Right.
	tmpj = j + 1;
	while (tmpj < M && A[i][tmpj] != '#' && PVT[i][tmpj] == INF)
		PVT[i][tmpj++] = PT[i][j];
}

void PolicemanGoTo(int i, int j, int T) {
	if (i >= 0 && i < N && j >= 0 && j < M && A[i][j] != '#' && PT[i][j] == INF) {
		PT[i][j] = T + 1;
		PQ.push({ i, j });
	}
}

void PolicemanBFS() {
	PT[Pi][Pj] = PVT[Pi][Pj] = 0;
	PQ.push({ Pi, Pj });
	while (!PQ.empty()) {
		auto [i, j] = PQ.front();
		PQ.pop();
		MarkVisibleCells(i, j);
		PolicemanGoTo(i - 1, j, PT[i][j]);
		PolicemanGoTo(i + 1, j, PT[i][j]);
		PolicemanGoTo(i, j - 1, PT[i][j]);
		PolicemanGoTo(i, j + 1, PT[i][j]);
	}
}

int main() {
	scanf("%d", &T);
	while (T--) {
		YQ = queue<pair<int, int>>();
		PQ = queue<pair<int, int>>();
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				YT[i][j] = PT[i][j] = PVT[i][j] = INF;
				scanf(" %c", &A[i][j]);
				switch (A[i][j])
				{
				case 'Y': Yi = i; Yj = j; break;
				case 'P': Pi = i; Pj = j; break;
				case 'H': Hi = i; Hj = j;
				}
			}
		}
		PolicemanBFS();
		YouBFS();
	}
}